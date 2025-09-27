#pragma once
#include "macro.h"

//---------------------------------------------------------------------------

class class_key_state
{
public:

	uint16_t

		hold_flag_array
		= 0
		//hold-flag (on or off) variable as a bit-array
		;

	uint8_t

		state
		= 0
		//contains code with key state
		;

	constexpr static uint8_t const

		max_index
		= sizeof(hold_flag_array) * 8
		//holds max index for safety
		;

	enum class states :uint8_t
	{
		no_hold = 0,

		to_hold = 1,

		hold = 2,

		from_hold = 3
	}
	//holds constatnt codes for states of key
	;

	enum class masks :uint16_t
	{
		//for start of holding (time sensitive)
		to_hold = 0b0000'0000'0000'0001,

		//for hold
		hold = 0b1000'0000'0000'0000,

		//for combined state (can detect very short inputs)
		combined = to_hold | hold
	}
	//holds names of masks to filter GetAsyncKeyState function
	;

	uint8_t
		&
		get_key_state
		(
			uint32_t const

			hotkey_virtual_key
			//virtual key code of key to check status
			,

			uint8_t

			index_to_check_and_set
			= 0
			//index of bit to check in flag (default 0 for bool)
			,

			uint16_t

			mask_filter
			= static_cast<uint16_t>(class_key_state::masks::hold)
			//mask to filter with
		)
		//method for manipulating the data fields of a structure
		;
}
//
;

//---------------------------------------------------------------------------