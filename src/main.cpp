namespace Hooks
{
	// PlayerControls::SprintHandler
	class hkSprintHandler :
		public REX::Singleton<hkSprintHandler>
	{
	private:
		static void SprintHandler(void* a_this, RE::ButtonEvent* a_event)
		{
			if (a_event->value > 0.0f &&
			    a_event->heldDownSecs == 0.0f)
			{
				auto PlayerCharacter = RE::PlayerCharacter::GetSingleton();
				auto flag = REX::ADJUST_POINTER<std::uint8_t>(PlayerCharacter, 0x1124);
				*flag &= 4;
			}
			else if (a_event->value == 0.0f &&
			         a_event->heldDownSecs > 0.0f)
			{
				auto PlayerCharacter = RE::PlayerCharacter::GetSingleton();
				auto flag = REX::ADJUST_POINTER<std::uint8_t>(PlayerCharacter, 0x1124);
				*flag &= ~4;
			}

			_Hook0(a_this, a_event);
		}

		inline static REL::HookVFT _Hook0{ RE::VTABLE::PlayerControls__SprintHandler[0], 0x08, SprintHandler };
	};
}

SFSEPluginLoad(const SFSE::LoadInterface* a_sfse)
{
	SFSE::Init(a_sfse);
	return true;
}
