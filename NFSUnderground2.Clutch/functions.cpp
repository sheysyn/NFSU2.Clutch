#include "functions.h"
#include "config_loader_function.h"

//---------------------------------------------------------------------------

bool

memory_data_replace
(
	void
	* const
	address_to_patch
	//
	,

	void
	* const
	array_of_bytes_to_set
	//
	,

	size_t const

	array_of_bytes_size
	//
)
{
	DWORD

		old_protect
		//original type of protection
		;

	if (
		address_to_patch
		==
		nullptr
		||
		array_of_bytes_to_set
		==
		nullptr
		||
		array_of_bytes_size
		==
		0
		)
		//if address_to_patch or array address are invalid or size to set is 0
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Address_to_patch or array address are invalid or size to set is 0 in memory_data_replace.",
				NULL
			)
			//
			;
#endif

		return false
			//
			;
	}

	if (
		!VirtualProtect
		(
			address_to_patch,

			array_of_bytes_size,

			PAGE_EXECUTE_READWRITE,

			&old_protect
		)
		//change memory protection to read-write
		)
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Can't change protection in memory_data_replace.",
				NULL
			)
			//
			;
#endif

		return false
			//can't change protection
			;
	}

#ifdef DEBUGGER_CONSOLE
	debug_info<int>
		(
			"Value before = ",
			*(reinterpret_cast<uint8_t*>(address_to_patch))
		)
		//
		;
#endif

	memcpy
	(
		address_to_patch,

		array_of_bytes_to_set,

		array_of_bytes_size
	)
		//copies values from array_of_bytes_to_set from 0 index to array_of_bytes_size index
		;

#ifdef DEBUGGER_CONSOLE
	debug_info<int>
		(
			"Value after = ",
			*(reinterpret_cast<uint8_t*>(address_to_patch))
		)
		//
		;
#endif

	if (
		!FlushInstructionCache
		(
			process_handle,

			address_to_patch,

			array_of_bytes_size
		)
		//resets cached instructions
		)
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Can't flush instruction cache in memory_data_replace.",
				NULL
			)
			//
			;
#endif

		if (
			!VirtualProtect
			(
				address_to_patch,

				array_of_bytes_size,

				old_protect,

				&old_protect
			)
			//return memory protection to the old value (read-only)
			)
		{

#ifdef DEBUGGER_CONSOLE
			debug_info<int>
				(
					"Can't return memory protection to the old value in memory_data_replace.",
					NULL
				)
				//
				;
#endif

		}

		return false
			//
			;
	}

	if (
		!VirtualProtect
		(
			address_to_patch,

			array_of_bytes_size,

			old_protect,

			&old_protect
		)
		//return memory protection to the old value (read-only)
		)
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Can't return memory protection to the old value in memory_data_replace.",
				NULL
			)
			//
			;
#endif

		return false
			//
			;
	}

	return true
		//
		;
}

//---------------------------------------------------------------------------

bool

memory_data_replace_fast
(
	uint8_t
	* const
	address_to_patch
	//
	,

	uint8_t const

	value_to_set
	//
)
{
	if (
		address_to_patch
		==
		nullptr
		)
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Address_to_patch is nullptr in memory_data_replace_fast.",
				NULL
			)
			//
			;
#endif

		return false
			//
			;
	}

	static DWORD

		old_protect
		//just a plug
		;

	static SIZE_T

		size_of_type
		= sizeof(value_to_set) * 8
		//size for virual protect
		;

	if (
		!VirtualProtect
		(
			address_to_patch,

			size_of_type,

			PAGE_EXECUTE_READWRITE,

			&old_protect
		)
		//change memory protection to read-write
		)
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Can't change protection in memory_data_replace_fast.",
				NULL
			)
			//
			;
#endif

		//can't change protection
		return false
			//
			;
	}

#ifdef DEBUGGER_CONSOLE
	debug_info<int>
		(
			"Value before = ",
			*(address_to_patch)
		)
		//
		;
#endif

	* address_to_patch
		= value_to_set
		//
		;

#ifdef DEBUGGER_CONSOLE
	debug_info<int>
		(
			"Value after = ",
			*(address_to_patch)
		)
		//
		;
#endif

	if (
		FlushInstructionCache
		(
			process_handle,

			address_to_patch,

			size_of_type
		)
		//resets cached instructions
		)
	{
		return true
			//
			;
	}

#ifdef DEBUGGER_CONSOLE
	debug_info<int>
		(
			"Can't flush instruction cache in memory_data_replace_fast.",
			NULL
		)
		//
		;
#endif

	return false
		//
		;
}

//---------------------------------------------------------------------------

uint8_t
*
pointer_chain_last_address
(
	uint8_t
	* const&
	first_pointer
	//
	,

	uint32_t const
	* const
	offsets_array
	//
	,

	size_t const

	offsets_array_size
	//
)
{
	//invalid arguments filter
	if (
		offsets_array
		==
		nullptr
		)
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Offsets array address is invalid in pointer_chain_last_address.",
				NULL
			)
			//
			;
#endif

		return nullptr
			//
			;
	}


	uint8_t
		*
		current_address
		= first_pointer
		//
		;

	for (
		size_t

		i = 1
		//because first offset is already applied
		;

		i < offsets_array_size
		//
		;

		++i
		//
		)
		//the chain starting from the second offset because the first one has already been added
	{
		if (
			current_address
			==
			nullptr
			||
			current_address
			>=
			top_address
			||
			current_address
			<=
			bottom_address
			)
		{

#ifdef DEBUGGER_CONSOLE~
			debug_info<int>
				(
					"Current address in the chain is invalid before reinterpret_cast in pointer_chain_last_address at iteration #",
					i
				)
				//
				;
#endif

			return nullptr
				//
				;
		}

		current_address
			= *(reinterpret_cast<uint8_t**>(current_address))
			//reinterpreting current address as a pointer to a pointer and reading it once.
			;

		//invalid temp address filter
		if (
			current_address
			==
			nullptr
			||
			current_address
			>=
			top_address
			||
			current_address
			<=
			bottom_address
			)
		{

#ifdef DEBUGGER_CONSOLE~
			debug_info<int>
				(
					"Current address in the chain is invalid after reinterpret_cast in pointer_chain_last_address at iteration #",
					i
				)
				//
				;
#endif

			return nullptr
				//
				;
		}

		current_address
			+= *(offsets_array + i)
			//adding the offset to the address and continue the loop
			;
	}

	return current_address
		//the result is the last address in the chain
		;
}

//---------------------------------------------------------------------------

void

global_vars_runtime_initialaze
()
{
	GetSystemInfo
	(&system_info)
		//
		;

	bottom_address
		= system_info.lpMinimumApplicationAddress
		//
		;

#ifdef DEBUGGER_CONSOLE
	debug_info<void*>
		(
			"#global_vars_runtime_initialaze bottom address is ",
			bottom_address
		)
		//
		;
#endif

	top_address
		= system_info.lpMaximumApplicationAddress
		//
		;

#ifdef DEBUGGER_CONSOLE
	debug_info<void*>
		(
			"#global_vars_runtime_initialaze top address is ",
			top_address
		)
		//
		;
#endif

}

//---------------------------------------------------------------------------

void

initialize_rp_b_db_var_disp
()
{
	for (
		size_t i

		= 1
		//because first is already filled
		;

		i < asm_code_instr_b_arr_size_db_var_disp
		//
		;

		++i
		//
		)
	{
		*(asm_code_instr_rp_b_db_var_disp + i)
			= (
				reinterpret_cast<uintptr_t>(&script_gear)
				>>
				((i - 1) * 8)
				) & 0xFF
			//
			;
	}
}

//---------------------------------------------------------------------------

void

redefine_flag_b_to_use_db_var_disp
()
{
	static uint8_t

		last_gearbox_type_flag
		= ~(*game_var_s_ptr_gearbox_type_flag)
		//
		;

	if (
		last_gearbox_type_flag
		!=
		*game_var_s_ptr_gearbox_type_flag
		)
	{
		last_gearbox_type_flag
			= *game_var_s_ptr_gearbox_type_flag
			//
			;
	}

	if (
		last_gearbox_type_flag
		==
		static_cast<uint8_t>(game_const_gearbox_type_flag::automatic)
		)
	{
		flag_b_to_use_db_var_disp
			= static_cast<uint8_t>(asm_code_instr_b_to_use::og)
			//
			;

		return
			//
			;
	}

	static class_key_state

		tmp
		//
		;

	if (
		GetAsyncKeyState(hk_mod_key)
		&&
		static_cast<uint16_t>(class_key_state::masks::hold)
		)
	{
		if (
			tmp.get_key_state(hk_sw_db_var_disp_b)
			==
			static_cast<uint8_t>(class_key_state::states::to_hold)
			)
		{
			if (
				flag_b_to_use_db_var_disp
				==
				static_cast<uint8_t>(asm_code_instr_b_to_use::og)
				)
			{
				flag_b_to_use_db_var_disp
					= static_cast<uint8_t>(asm_code_instr_b_to_use::rp)
					//
					;
			}
			else
			{
				flag_b_to_use_db_var_disp
					= static_cast<uint8_t>(asm_code_instr_b_to_use::og)
					//
					;
			}
		}
	}
}

//---------------------------------------------------------------------------

void

patch_db_var_disp
()
{

#ifdef DEBUGGER_CONSOLE
	debug_info<int>
		(
			"#patch_db_var_disp.",
			NULL
		)
		//
		;
#endif

	if (
		b_to_use_db_var_disp
		==
		static_cast<uint16_t>(asm_code_instr_b_to_use::og)
		)
	{
		return
			//
			;
	}

	static uint8_t

		last_flag_b_to_use_db_var_disp
		= ~flag_b_to_use_db_var_disp
		//
		;

	if (
		last_flag_b_to_use_db_var_disp
		==
		flag_b_to_use_db_var_disp
		)
	{
		return
			//
			;
	}

	switch (flag_b_to_use_db_var_disp)
	{
	case static_cast<uint8_t>(asm_code_instr_b_to_use::og):

		memory_data_replace
		(
			reinterpret_cast<void* const>(asm_code_instr_s_ptr_db_var_disp),

			reinterpret_cast<void* const>(const_cast<uint8_t* const>(asm_code_instr_og_b_db_var_disp)),

			asm_code_instr_b_arr_size_db_var_disp
		)
			//
			;

		last_flag_b_to_use_db_var_disp
			= static_cast<uint8_t>(asm_code_instr_b_to_use::og)
			//
			;

		break
			//
			;

	case static_cast<uint8_t>(asm_code_instr_b_to_use::rp):

		memory_data_replace
		(
			reinterpret_cast<void* const>(asm_code_instr_s_ptr_db_var_disp),

			reinterpret_cast<void* const>(asm_code_instr_rp_b_db_var_disp),

			asm_code_instr_b_arr_size_db_var_disp
		)
			//
			;

		last_flag_b_to_use_db_var_disp
			= static_cast<uint8_t>(asm_code_instr_b_to_use::rp)
			//
			;

		break
			//
			;
	}
}

//---------------------------------------------------------------------------

void

redefine_flag_b_to_use_sh_del
()
{
	static class_key_state

		tmp
		//
		;

	if (
		GetAsyncKeyState(hk_mod_key)
		&&
		static_cast<uint16_t>(class_key_state::masks::hold)
		)
	{
		if (
			tmp.get_key_state(hk_sw_sh_del_b)
			==
			static_cast<uint8_t>(class_key_state::states::to_hold)
			)
		{
			if (
				flag_b_to_use_sh_del
				==
				static_cast<uint8_t>(asm_code_instr_b_to_use::og)
				)
			{
				flag_b_to_use_sh_del
					= static_cast<uint8_t>(asm_code_instr_b_to_use::rp)
					//
					;
			}
			else
			{
				flag_b_to_use_sh_del
					= static_cast<uint8_t>(asm_code_instr_b_to_use::og)
					//
					;
			}
		}
	}
}

//---------------------------------------------------------------------------

void

patch_sh_del
()
{
	if (
		b_to_use_sh_del
		==
		static_cast<int>(asm_code_instr_b_to_use::og)
		)
	{
		return
			//
			;
	}

	static uint8_t

		last_flag_b_to_use_sh_del
		= ~flag_b_to_use_sh_del
		//
		;

	if (
		last_flag_b_to_use_sh_del
		==
		flag_b_to_use_sh_del
		)
	{
		return
			//
			;
	}

	switch (flag_b_to_use_sh_del)
	{
	case static_cast<uint8_t>(asm_code_instr_b_to_use::og):

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Switched patch_sh_del to original bytes.",
				NULL
			)
			//
			;
#endif

		memory_data_replace
		(
			reinterpret_cast<void* const>(asm_code_instr_s_ptr_sh_del),

			reinterpret_cast<void* const>(const_cast<uint8_t*>(asm_code_instr_og_b_sh_del)),

			asm_code_instr_b_arr_size_sh_del
		)
			//
			;

		last_flag_b_to_use_sh_del
			= static_cast<uint8_t>(asm_code_instr_b_to_use::og)
			//
			;

		break
			//
			;

	case static_cast<uint8_t>(asm_code_instr_b_to_use::rp):

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Switched patch_sh_del to replace bytes.",
				NULL
			)
			//
			;
#endif

		memory_data_replace
		(
			reinterpret_cast<void* const>(asm_code_instr_s_ptr_sh_del),

			reinterpret_cast<void* const>(const_cast<uint8_t*>(asm_code_instr_rp_b_sh_del)),

			asm_code_instr_b_arr_size_sh_del
		)
			//
			;

		last_flag_b_to_use_sh_del
			= static_cast<uint8_t>(asm_code_instr_b_to_use::rp)
			//
			;

		break
			//
			;
	}
}

//---------------------------------------------------------------------------

void

redefine_flag_gearbox_type
()
{
	static class_key_state

		tmp
		//
		;

	if (
		GetAsyncKeyState(hk_mod_key)
		&&
		static_cast<uint16_t>(class_key_state::masks::hold)
		)
	{
		if (
			tmp.get_key_state(hk_sw_gbox_type)
			==
			static_cast<uint8_t>(class_key_state::states::to_hold)
			)
		{
			if (
				flag_gearboxbox_type
				==
				static_cast<uint8_t>(gearbox_type::sequential)
				)
			{
				flag_gearboxbox_type
					= static_cast<uint8_t>(gearbox_type::H_pattern)
					//
					;
			}
			else
			{
				flag_gearboxbox_type
					= static_cast<uint8_t>(gearbox_type::sequential)
					//
					;
			}
		}
	}
}

//---------------------------------------------------------------------------

void

redefine_gearbox_type
()
{
	static uint16_t

		last_flag_gbox_type
		= ~flag_gearboxbox_type
		//
		;

	if (
		last_flag_gbox_type
		==
		flag_gearboxbox_type
		)
	{
		return
			//
			;
	}
	else
		if (
			gearbox
			!=
			nullptr
			)
		{

#ifdef DEBUGGER_CONSOLE
			debug_info<int>
				(
					"gearbox ptr is deleted.",
					NULL
				)
				//
				;
#endif

			delete gearbox
				//
				;
		}

	switch (flag_gearboxbox_type)
	{
	case static_cast<uint8_t>(gearbox_type::sequential):

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Switched gearbox_type to sequential.",
				NULL
			)
			//
			;
#endif

		gearbox
			= new class_sequential_type
			//
			;

		last_flag_gbox_type
			= static_cast<uint8_t>(gearbox_type::sequential)
			//
			;

		break
			//
			;

	case static_cast<uint8_t>(gearbox_type::H_pattern):

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Switched gearbox_type to H_pattern.",
				NULL
			)
			//
			;
#endif

		gearbox
			= new class_H_pattern_type
			//
			;

		last_flag_gbox_type
			= static_cast<uint8_t>(gearbox_type::H_pattern)
			//
			;

		break
			//
			;
	}
}

//---------------------------------------------------------------------------

void

update_dynamic_pointers
()
{
	game_var_d_ptr_gear
		= pointer_chain_last_address
		(
			game_var_f_ptr_gear,

			game_var_off_gear,

			game_var_off_arr_size_gear
		)
		//
		;

	game_var_d_ptr_max_gear
		= pointer_chain_last_address
		(
			game_var_f_ptr_max_gear,

			game_var_off_max_gear,

			game_var_off_arr_size_max_gear
		)
		//
		;
}

//---------------------------------------------------------------------------

void

update_script_gear_value
()
{
	static uint32_t last_script_gear
		= ~script_gear
		//
		;

	if (
		game_var_d_ptr_gear
		==
		nullptr
		||
		*game_var_d_ptr_gear
		==
		static_cast<uint8_t>(game_const_gear_val::_N)
		||
		last_script_gear
		==
		script_gear
		)
	{

#ifdef DEBUGGER_CONSOLE~
		debug_info<int>
			(
				"Trying to read nullptr or last state is already written or it's just neutral in update_script_gear_value.",
				NULL
			)
			//
			;
#endif

		return
			//
			;
	}

	script_gear
		= *game_var_d_ptr_gear
		//
		;
}

//---------------------------------------------------------------------------

void

f_game_vars_and_cond_update
() noexcept
{
	try
	{
		global_vars_runtime_initialaze
		()
			//
			;

		initialize_rp_b_db_var_disp
		()
			//
			;

		patch_db_var_disp
		()
			//
			;


		patch_sh_del
		()
			//
			;
	}
	catch (std::exception& ex)
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				(std::string("Exception in f_game_vars_and_cond_update thread (before cycle part), ") + ex.what()).c_str(),
				NULL
			)
			//
			;
#endif

	}
	catch (...)
	{

#ifdef DEBUGGER_CONSOLE
		debug_info<int>
			(
				"Something other than exceptions is wrong in f_game_vars_and_cond_update thread (before cycle part).",
				NULL
			)
			//
			;
#endif

	}

	while (running_flag)
	{
		try
		{

			update_dynamic_pointers
			()
				//
				;

			if (
				*game_var_s_ptr_gearbox_type_flag
				!=
				static_cast<uint8_t>(game_const_gearbox_type_flag::manual)
				||
				*game_var_s_ptr_pause_flag
				!=
				static_cast<uint8_t>(game_const_pause_flag::out)
				||
				*game_var_s_ptr_cdown_falg
				!=
				static_cast<uint8_t>(game_const_cdown_flag::out)
				||
				gearbox
				==
				nullptr
				||
				game_var_d_ptr_gear
				==
				nullptr
				||
				game_var_d_ptr_max_gear
				==
				nullptr
				)
			{
				if (
					permission_for_main
					)
				{
					permission_for_main
						= false
						//
						;

					script_gear
						= static_cast<uint8_t>(game_const_gear_val::_N)
						//
						;
				}

				redefine_flag_b_to_use_db_var_disp
				()
					//
					;

				patch_db_var_disp
				()
					//
					;

				redefine_flag_b_to_use_sh_del
				()
					//
					;

				patch_sh_del
				()
					//
					;

				redefine_flag_gearbox_type
				()
					//
					;

				redefine_gearbox_type
				()
					//
					;
			}
			else
				if (
					*game_var_s_ptr_pause_flag
					==
					static_cast<uint8_t>(game_const_pause_flag::out)
					&&
					*game_var_s_ptr_cdown_falg
					==
					static_cast<uint8_t>(game_const_cdown_flag::out)
					)
				{
					if (!permission_for_main)
					{
						permission_for_main
							= true
							//
							;
					}

					update_script_gear_value
					()
						//
						;
				}

			sleep_for_msec(custom_timers::game_variables_update)
				//
				;
		}
		catch (std::exception const& ex)
		{

#ifdef DEBUGGER_CONSOLE
			debug_info<int>
				(
					(std::string("Exception in f_game_vars_and_cond_update thread (cycle part), ") + ex.what()).c_str(),
					NULL
				)
				//
				;
#endif

		}
		catch (...)
		{

#ifdef DEBUGGER_CONSOLE
			debug_info<int>
				(
					"Something other than exceptions is wrong in f_game_vars_and_cond_update thread (cycle part).",
					NULL
				)
				//
				;
#endif

		}
	}
}

//---------------------------------------------------------------------------

void

f_gearbox_operating
() noexcept
{
	while (running_flag)
	{
		try
		{
			if (
				!permission_for_main
				)
			{
				sleep_for_msec((custom_timers::wait_for_permission))
					//
					;

				continue
					//
					;
			}

			(*gearbox).operate
			()
				//
				;

			sleep_for_msec(custom_timers::gearbox_operating)
				//
				;
		}
		catch (std::exception const& ex)
		{

#ifdef DEBUGGER_CONSOLE
			debug_info<int>
				(
					(std::string("Exception in f_gearbox_operating thread (cycle part), ") + ex.what()).c_str(),
					NULL
				)
				//
				;
#endif

		}
		catch (...)
		{

#ifdef DEBUGGER_CONSOLE
			debug_info<int>
				(
					"Something other than exceptions is wrong in f_gearbox_operating thread (cycle part).",
					NULL
				)
				//
				;
#endif

		}
	}
}

//---------------------------------------------------------------------------