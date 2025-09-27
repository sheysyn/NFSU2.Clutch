#include "class_key_state.h"

//---------------------------------------------------------------------------

uint8_t
&
class_key_state::get_key_state
(
	uint32_t const

	hotkey_virtual_key
	//
	,

	uint8_t

	index_to_check_and_set
	//
	,

	uint16_t

	mask_filter
	//
)
{
	if (
		index_to_check_and_set
		>=
		class_key_state::max_index
		)
		//plug for invalid index
	{
		return (*this).state
			= static_cast<uint8_t>(class_key_state::states::no_hold)
			//
			;
	}

	if (
		GetAsyncKeyState(hotkey_virtual_key)
		&
		mask_filter
		)
		//is key is pressed
	{
		if (
			(*this).hold_flag_array
			&
			(0b1 << index_to_check_and_set)
			)
		{
			return (*this).state
				= static_cast<uint8_t>(class_key_state::states::hold)
				//already pressed (bit in hold_flag_array is 1)
				;
		}
		else
		{
			(*this).hold_flag_array
				|= (uint16_t(0b1) << index_to_check_and_set)
				//sets bit to 1
				;

			return (*this).state
				= static_cast<uint8_t>(class_key_state::states::to_hold)
				//first impulse (bit in hold_flag_array is 0)
				;
		}
	}
	else
		if (
			(*this).hold_flag_array
			&
			(0b1 << index_to_check_and_set)
			)
			//was pressed but now don't
		{
			(*this).hold_flag_array
				&= ~(uint16_t(0b1) << index_to_check_and_set)
				//sets bit to 0
				;

			return (*this).state
				= static_cast<uint8_t>(states::from_hold)
				//
				;
		}

	return (*this).state
		= static_cast<uint8_t>(states::no_hold)
		//wasn't pressed and now isn't
		;
}

//---------------------------------------------------------------------------