/* 
 * https://github.com/Starfield-Reverse-Engineering/CommonLibSF
 * This plugin template links against CommonLibSF
 */

#include "DKUtil/Hook.hpp"

class Hooks
{
public:
	static void Install()
	{
		hkSprintHandler::Install();
	}

private:
	class hkSprintHandler
	{
	public:
		static void Install()
		{
			static REL::Relocation<std::uintptr_t> target{ REL::ID(129187), 0x0C };
			auto& trampoline = SFSE::GetTrampoline();
			trampoline.write_call<5>(target.address(), SprintHandler);
		}

	private:
		struct ButtonEventImpl
		{
		public:
			std::byte pad00[0x48];   // 00
			float     value;         // 48
			float     heldDownSecs;  // 4C
			std::byte pad50[0x10];   // 50
		};
		static_assert(sizeof(ButtonEventImpl) == 0x60);

		static bool SprintHandler(ButtonEventImpl* a_event)
		{
			if (a_event->value > 0.0f && a_event->heldDownSecs == 0.0f)
			{
				return true;
			}
			else if (a_event->value == 0.0f && a_event->heldDownSecs > 0.0f)
			{
				static REL::Relocation<void**> PlayerCharacter{ REL::ID(865059) };
				auto flag = REL::stl::adjust_pointer<std::uint8_t>(*PlayerCharacter.get(), 0x110C);
				(*flag) = (*flag) & ~4;
			}

			return false;
		}
	};
};

namespace
{
	void MessageCallback(SFSE::MessagingInterface::Message* a_msg) noexcept
	{
		switch (a_msg->type) {
		case SFSE::MessagingInterface::kPostLoad:
			{
				Hooks::Install();
				break;
			}
		default:
			break;
		}
	}
}

DLLEXPORT bool SFSEAPI SFSEPlugin_Load(const SFSE::LoadInterface* a_sfse)
{
#ifndef NDEBUG
	MessageBoxA(NULL, "Loaded. You can now attach the debugger or continue execution.", Plugin::NAME.data(), NULL);
#endif

	SFSE::Init(a_sfse, false);
	DKUtil::Logger::Init(Plugin::NAME, std::to_string(Plugin::Version));
	INFO("{} v{} loaded", Plugin::NAME, Plugin::Version);

	SFSE::AllocTrampoline(1 << 4);
	SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);

	return true;
}
