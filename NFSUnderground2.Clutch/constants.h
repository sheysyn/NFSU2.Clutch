#pragma once
#include "macro.h"
#include "config_loader_function.h"

//for extended names look in "macro.h"

//---------------------------------------------------------------------------

HMODULE const

module_handle
= GetModuleHandle(NULL)
//handle of a module (the base address of the game main executive module)
;

HANDLE const

process_handle
= GetCurrentProcess()
//handle of a process
;

//---------------------------------------------------------------------------

uint8_t
* const
base_address
= reinterpret_cast<uint8_t*>(module_handle)
//same as handle but as a BYTE*
;

//---------------------------------------------------------------------------

//offsets arrays to:
constexpr uint32_t const

game_var_off_gear
[] =
{
	0x4659BC,

	0x1E4
}
//in-game gear
,


game_var_off_max_gear
[] =
{
	0x4659BC,

	0x2A8,

	0x20,

	0x1C8
}
//in-game max gear
,


game_var_off_gearbox_type_flag
[] =
{
	0x43AA79
}
//in-game gearbox type flag
,


game_var_off_cdown_falg
[] =
{
	0x42B8D4
}
//in-game countdown flag
,


game_var_off_pause_flag
[] =
{
	0x470788
}
//in-game pause flag
,


asm_code_instr_off_sh_del
[] =
{
	0x1A161E
}
//assembly code instuction with shifting delay
,


asm_code_instr_off_db_var_disp
[] =
{
	0xC6A6D
}
//assembly code instuction with dashboard variable display
;

//---------------------------------------------------------------------------

//the sizes of the corresponding offsets arrays to dynamic pointers only
constexpr size_t const

game_var_off_arr_size_gear
= sizeof(game_var_off_gear) / sizeof(*game_var_off_gear)
//
,


game_var_off_arr_size_max_gear
= sizeof(game_var_off_max_gear) / sizeof(*game_var_off_max_gear)
//
;

//---------------------------------------------------------------------------

//constant pointers
uint8_t
* const
game_var_f_ptr_gear
= base_address + *game_var_off_gear
//
,

* const
game_var_f_ptr_max_gear
= base_address + *game_var_off_max_gear
//
,

* const
asm_code_instr_s_ptr_sh_del
= base_address + *asm_code_instr_off_sh_del
//
,

* const
asm_code_instr_s_ptr_db_var_disp
= base_address + *asm_code_instr_off_db_var_disp
//
;

//---------------------------------------------------------------------------

//constant pointers
uint8_t const
* const
game_var_s_ptr_gearbox_type_flag
= base_address + *game_var_off_gearbox_type_flag
//
,

* const
game_var_s_ptr_cdown_falg
= base_address + *game_var_off_cdown_falg
//
,

* const
game_var_s_ptr_pause_flag
= base_address + *game_var_off_pause_flag
//
;

//---------------------------------------------------------------------------

//array with bytes for assembly code instruction to:
constexpr uint8_t const

asm_code_instr_og_b_sh_del
[] =
{
	0x02
}
//restore origina instruction with shifting delay
,


asm_code_instr_rp_b_sh_del
[] =
{
	0x03
}
//patch instruction with shifting delay
,


asm_code_instr_og_b_db_var_disp
[] =
{
	0x8B,

	0x8E,

	0x34,

	0x04,

	0x00,

	0x00
}
//restore origina instruction with dashboard variable display
;

//---------------------------------------------------------------------------

//the sizes of the corresponding byte arrays 
constexpr size_t const

asm_code_instr_b_arr_size_sh_del
= sizeof(asm_code_instr_og_b_sh_del) / sizeof(*asm_code_instr_og_b_sh_del)
//
,


asm_code_instr_b_arr_size_db_var_disp
= sizeof(asm_code_instr_og_b_db_var_disp) / sizeof(*asm_code_instr_og_b_db_var_disp)
//
;

//---------------------------------------------------------------------------

enum class timers : DWORD
{
	wait_for_permission = 100,

	game_variables_update = 30,

	gearbox_operating = 10
}
//timer values ​​in ms for Sleep() function in threads
;

enum class gearbox_type :uint8_t
{
	sequential = 0
	//sequential gearbox type
	,

	H_pattern = 1
	//H-pattern gearbox type
}
//for gearbox type swich
;

enum class game_const_gearbox_type_flag :uint8_t
{
	automatic = 0
	//in-game automatic gearbox type
	,

	manual = 1
	//in-game manual gearbox type
}
//for gearbox type swich
;

enum class asm_code_instr_b_to_use :uint8_t
{
	og = 0
	//original bytes
	,

	rp = 1
	//replacement bytes
}
//for shifting delay instruction bytes switch
;

enum class game_const_gear_val :uint8_t
{
	_R = 0,

	_N = 1,

	_1 = 2,

	_2 = 3,

	_3 = 4,

	_4 = 5,

	_5 = 6,

	_6 = 7,

	_7 = 8,

	_8 = 9
}
//enum witch in-game gear values
;

enum class game_const_pause_flag :uint8_t
{
	in = 1,

	out = 4
}
//pause flag values meaning
;

enum class game_const_cdown_flag :uint8_t
{
	in = 3,

	out = 4
}
//countdown flag values meaning
;

//---------------------------------------------------------------------------

//default states
uint16_t const

b_to_use_sh_del
= config_load_value<uint16_t>
(
	"main",

	"shifting_delay_patch",

	static_cast<int>(asm_code_instr_b_to_use::rp)
)
//
,


b_to_use_db_var_disp
= config_load_value<uint16_t>
(
	"main",

	"dashboard_patch",

	static_cast<int>(asm_code_instr_b_to_use::rp)
)
//
;

//---------------------------------------------------------------------------

//hotkey switches
uint16_t const

hk_clutch
= config_load_value<uint16_t>
(
	"main_hotkeys",

	"clutch_key",

	VK_DECIMAL
)
//
,


hk_mod_key
= config_load_value<uint16_t>
(
	"main_hotkeys",

	"modifier_key",

	VK_CONTROL
)
//
,


hk_sw_gbox_type
= config_load_value<uint16_t>
(
	"main_hotkeys",

	"gearbox_type_switch",

	VK_F8
)
//
,


hk_sw_sh_del_b
= config_load_value<uint16_t>
(
	"main_hotkeys",

	"shifting_delay_switch",

	VK_F9
)
//
,


hk_sw_db_var_disp_b
= config_load_value<uint16_t>
(
	"main_hotkeys",

	"dashboard_switch",

	VK_F10
)
//
;

//---------------------------------------------------------------------------

//hotkeys for sequential gearbox type
uint16_t const

hk_gear_dec
= config_load_value<uint16_t>
(
	"sequential_type",

	"gear_decrease",

	VK_NUMPAD1
)
//
,


hk_gear_inc
= config_load_value<uint16_t>
(
	"sequential_type",

	"gear_increase",

	VK_NUMPAD2
)
//
;

//---------------------------------------------------------------------------

//hotkeys for H-pattern gearbox type
uint16_t const

hk_gear_N
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_N",

	VK_NUMPAD0
)
//
,


hk_gear_1
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_1",

	VK_NUMPAD1
)
//
,


hk_gear_2
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_2",

	VK_NUMPAD2
)
//
,


hk_gear_3
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_3",

	VK_NUMPAD3
)
//
,


hk_gear_4
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_4",

	VK_NUMPAD4
)
//
,


hk_gear_5
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_5",

	VK_NUMPAD5
)
//
,


hk_gear_6
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_6",

	VK_NUMPAD6
)
//
,


hk_gear_7
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_7",

	VK_NUMPAD7
)
//
,


hk_gear_8
= config_load_value<uint16_t>
(
	"H_pattern_type",

	"gear_8",

	VK_NUMPAD8
)
//
;

//---------------------------------------------------------------------------