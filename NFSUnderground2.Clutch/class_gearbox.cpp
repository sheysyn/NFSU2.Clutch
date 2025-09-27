#include "class_gearbox.h"

//---------------------------------------------------------------------------

void

class_gearbox::go_to_neutral
()
{
	memory_data_replace_fast
	(
		game_var_d_ptr_gear,

		static_cast<uint8_t>(game_const_gear_val::_N)
	)
		//
		;
}

//---------------------------------------------------------------------------

void

class_gearbox::go_to_script
()
{
	memory_data_replace_fast
	(
		game_var_d_ptr_gear,

		script_gear
	)
		//
		;
}

//---------------------------------------------------------------------------

uint8_t
&
class_gearbox::clutch_logic
()
{
	switch (class_gearbox::clutch.get_key_state(hk_clutch))
	{
	case static_cast<uint8_t>(class_key_state::states::to_hold):

		clutch_state
			= static_cast<uint8_t>(clutch_states::_on)
			//
			;

		script_gear
			= *game_var_d_ptr_gear
			//
			;

		go_to_neutral
		()
			//
			;

		break
			//
			;

	case static_cast<uint8_t>(class_key_state::states::from_hold):

		clutch_state
			= static_cast<uint8_t>(clutch_states::_off)
			//
			;

		go_to_script
		()
			//
			;

		break
			//
			;
	}

	return clutch_state
		//
		;
}

//---------------------------------------------------------------------------

void

class_gearbox::operate
()
{
	if (
		clutch_logic()
		/*==
		static_cast<uint8_t>(clutch_states::_on)
		*/)
	{

#ifdef DEBUGGER_CONSOLE~
		debug_info<int>
			(
				"#class_gearbox::operate::shifting.",
				NULL
			)
			//
			;
#endif

		shifting
		()
			//
			;
	}
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void

class_sequential_type::shifting
()
{
	class_sequential_type::gear_decrease
	()
		//
		;

	class_sequential_type::gear_increase
	()
		//
		;
}

//---------------------------------------------------------------------------

void

class_sequential_type::gear_decrease
()
{
	if (
		script_gear
		<=
		static_cast<uint8_t>(game_const_gear_val::_N)
		)
	{
		return
			//
			;
	}

	if (
		shifting_flags.get_key_state
		(
			hk_gear_dec,

			static_cast<uint8_t>(holding_flag_bit_index::_dec)
		)
		==
		static_cast<uint8_t>(class_key_state::states::to_hold)
		)
	{
		--script_gear
			//
			;
	}
}

//---------------------------------------------------------------------------

void

class_sequential_type::gear_increase
()
{
	if (
		script_gear
		>
		*game_var_d_ptr_max_gear
		)
	{
		return
			//
			;
	}

	if (
		shifting_flags.get_key_state
		(
			hk_gear_inc,

			static_cast<uint8_t>(holding_flag_bit_index::_inc)
		)
		==
		static_cast<uint8_t>(class_key_state::states::to_hold)
		)
	{
		++script_gear
			//
			;
	}
}

//---------------------------------------------------------------------------

//---------------------------------------------------------------------------

void

class_H_pattern_type::shifting
()
{
	class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_N),

		hk_gear_N,

		static_cast<uint8_t>(game_const_gear_val::_N)
	)
		//
		;

	class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_1),

		hk_gear_1,

		static_cast<uint8_t>(game_const_gear_val::_1)
	)
		//
		;

	class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_2),

		hk_gear_2,

		static_cast<uint8_t>(game_const_gear_val::_2)
	)
		//
		;

	class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_3),

		hk_gear_3,

		static_cast<uint8_t>(game_const_gear_val::_3)
	)
		//
		;

	class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_4),

		hk_gear_4,

		static_cast<uint8_t>(game_const_gear_val::_4)
	)
		//
		;

	class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_5),

		hk_gear_5,

		static_cast<uint8_t>(game_const_gear_val::_5)
	)
		//
		;

	class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_6),

		hk_gear_6,

		static_cast<uint8_t>(game_const_gear_val::_6)
	)
		//
		;

	class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_7),

		hk_gear_7,

		static_cast<uint8_t>(game_const_gear_val::_7)
	)
		//
		;

	/*class_H_pattern_type::shift_to_n_gear
	(
		static_cast<uint8_t>(holding_flag_bit_index::_8),

		hk_gear_8,

		static_cast<uint8_t>(game_const_gear_val::_8)
	)
		//
		;*/
}

//---------------------------------------------------------------------------

void

class_H_pattern_type::shift_to_n_gear
(
	uint8_t

	index_to_check_and_set
	//
	,

	uint32_t

	hotkey_virtual_key
	//
	,

	uint8_t

	gear
	//
)
{
	if (
		shifting_flags.get_key_state
		(
			hotkey_virtual_key,

			index_to_check_and_set
		)
		==
		static_cast<uint8_t>(class_key_state::states::to_hold)
		)
	{
		if (
			gear
			>
			*game_var_d_ptr_max_gear + 1
			)
		{
			script_gear
				= *game_var_d_ptr_max_gear + 1
				//
				;
		}
		else
		{
			script_gear
				= gear
				//
				;
		}
	}
}

//---------------------------------------------------------------------------