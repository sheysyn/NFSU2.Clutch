#include "global_variables.h"

//---------------------------------------------------------------------------

SYSTEM_INFO

system_info
//
;

//---------------------------------------------------------------------------

std::atomic<bool>

running_flag
= true
//
,


permission_for_main
= false
//
;

//---------------------------------------------------------------------------

std::thread

game_vars_and_cond_update
//
,


gearbox_operating
//
;

//---------------------------------------------------------------------------

uint32_t

script_gear
= static_cast<uint8_t>(game_const_gear_val::_N)
//
;

uint8_t
*
game_var_d_ptr_gear
= nullptr
//
;

//---------------------------------------------------------------------------

uint8_t const
*
game_var_d_ptr_max_gear
= nullptr
//
;

//---------------------------------------------------------------------------

class_gearbox
*
gearbox
= nullptr
//
;

//---------------------------------------------------------------------------

uint8_t

asm_code_instr_rp_b_db_var_disp
[] =
{
	//assembly pointer to value without adding any register values
	0x0D,

	0x90,

	0x90,

	0x90,

	0x90
}
//
;

//---------------------------------------------------------------------------

uint16_t

flag_gearboxbox_type
=
config_load_value<uint16_t>
(
	"main_flags",

	"gearbox_type",

	static_cast<int>(gearbox_type::sequential)
)
//
,


flag_b_to_use_sh_del
=
config_load_value<uint16_t>
(
	"main_flags",

	"shifting_delay",

	static_cast<int>(asm_code_instr_b_to_use::og)
)
//
,


flag_b_to_use_db_var_disp
=
config_load_value<uint16_t>
(
	"main_flags",

	"dashboard",

	static_cast<int>(asm_code_instr_b_to_use::og)
)
//
;

//---------------------------------------------------------------------------

void
*
bottom_address
= nullptr
//
,

*
top_address
= nullptr
//
;

//---------------------------------------------------------------------------