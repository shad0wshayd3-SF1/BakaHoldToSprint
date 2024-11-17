namespace Hooks
{
	// PlayerControls::SprintHandler
	namespace hkSprintHandler
	{
		static bool SprintHandler(RE::ButtonEvent* a_event)
		{
			if (a_event->value > 0.0f &&
			    a_event->heldDownSecs == 0.0f)
			{
				return true;
			}
			else if (a_event->value == 0.0f &&
			         a_event->heldDownSecs > 0.0f)
			{
				auto PlayerCharacter = RE::PlayerCharacter::GetSingleton();
				auto flag = REL::stl::adjust_pointer<std::uint8_t>(PlayerCharacter, 0x1124);
				*flag &= ~4;
			}

			return false;
		}

		static void Install()
		{
			static REL::Relocation target{ REL::ID(129187), 0x0C };
			target.write_call<5>(SprintHandler);
		}
	}

	static void Install()
	{
		hkSprintHandler::Install();
	}
}

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

	SFSE::AllocTrampoline(16);
	SFSE::GetMessagingInterface()->RegisterListener(MessageCallback);

	return true;
}
