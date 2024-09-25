class Hooks
{
public:
	static void Install()
	{
		// PlayerControls::SprintHandler
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
		// clang-format off
		struct ButtonEventImpl
		{
		public:
			std::byte pad00[0x48];  // 00
			float value;            // 48
			float heldDownSecs;     // 4C
			std::byte pad50[0x10];  // 50
		};
		static_assert(sizeof(ButtonEventImpl) == 0x60);
		// clang-format on

		static bool SprintHandler(ButtonEventImpl* a_event)
		{
			if (a_event->value > 0.0f && a_event->heldDownSecs == 0.0f)
			{
				return true;
			}
			else if (a_event->value == 0.0f && a_event->heldDownSecs > 0.0f)
			{
				static REL::Relocation<void**> PlayerCharacter{ REL::ID(865059) };
				auto flag = REL::stl::adjust_pointer<std::uint8_t>(*PlayerCharacter.get(), 0x1114);
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
		switch (a_msg->type)
		{
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

SFSEPluginLoad(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);

	SFSE::AllocTrampoline(1 << 4);
	SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);

	return true;
}
