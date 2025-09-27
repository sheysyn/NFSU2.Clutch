#pragma once
#include "macro.h"
#include "constants.h"
#include "global_variables.h"

//---------------------------------------------------------------------------

bool

memory_data_replace
(
	void
	* const
	address_to_patch
	//place to patch
	,

	void
	* const
	array_of_bytes
	//array of bytes to replace
	,

	size_t const

	array_of_bytes_size
	//size of an array
)
//
,


memory_data_replace_fast
(
	uint8_t
	* const
	address_to_patch
	//place to patch
	,

	uint8_t const

	value_to_set
	//what to put in
)
//
;

//---------------------------------------------------------------------------

uint8_t
*
pointer_chain_last_address
(
	uint8_t
	* const&
	first_pointer
	//base address
	,

	uint32_t const
	* const
	offsets_array
	//array of offsets
	,

	size_t const

	offsets_array_size
	//offsets array size
)
//
;

//---------------------------------------------------------------------------

void

global_vars_runtime_initialaze
()
//
,


initialize_rp_b_db_var_disp
()
//
,


redefine_flag_b_to_use_db_var_disp
()
//
,


patch_db_var_disp
()
//
,


redefine_flag_b_to_use_sh_del
()
//
,


patch_sh_del
()
//
,


redefine_flag_gearbox_type
()
//
,


redefine_gearbox_type
()
//
,


update_dynamic_pointers
()
//
,


update_script_gear_value
()
//
;

//---------------------------------------------------------------------------

void

f_game_vars_and_cond_update
() noexcept
//
,

f_gearbox_operating
() noexcept
//
;

//---------------------------------------------------------------------------