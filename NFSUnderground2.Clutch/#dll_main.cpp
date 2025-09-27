#include "#dll_main.h"

//---------------------------------------------------------------------------

BOOL WINAPI DllMain
(
	HMODULE

	hModule
	//
	,

	uint32_t

	ul_reason_for_call
	//
	,

	void
	*
	lpReserved
	//
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:

		game_vars_and_cond_update
			= std::thread(f_game_vars_and_cond_update)
			//
			;

		gearbox_operating
			= std::thread(f_gearbox_operating)
			//
			;

		break
			//
			;

	case DLL_PROCESS_DETACH:

		running_flag
			= false
			//
			;

		if (
			game_vars_and_cond_update.joinable()
			)
		{
			game_vars_and_cond_update.join
			()
				//
				;
		}

		if (
			gearbox_operating.joinable()
			)
		{
			gearbox_operating.join
			()
				//
				;
		}

		break
			//
			;
	}
	return TRUE
		//
		;
}

//---------------------------------------------------------------------------