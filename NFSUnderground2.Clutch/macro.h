#pragma once

//---------------------------------------------------------------------------

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _CRT_SECURE_NO_WARNINGS

//---------------------------------------------------------------------------

#include <windows.h>

#include <cstdint>
#include <thread>
#include <chrono>
#include <atomic>

//#include "#DEBUG.h"

//---------------------------------------------------------------------------

#define sleep_for_msec(x) std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<uint16_t>(x)))

#define sleep_for_sec(x) std::this_thread::sleep_for(std::chrono::seconds(static_cast<uint16_t>(x)))

//custom_names

/*
#ifdef custom_names

#define custom_names

//global vars

//sorted by type

//offsets is a constant array of int64_t data (int64_t const*)
//pointer is a pointer to uint8_t data (uint8_t*)
//original bytes and replacement bytes is a constant array of a uint8_t data (uint8_t const*)



//enums with named constants for different states

//
#define game_const_gear_val game_constant_gear_value

//
#define game_const_cdown_flag game_constant_countdown_flag

//
#define game_const_pause_flag game_constant_pause_flag

//
#define game_const_gearbox_type_flag game_constant_gearbox_type_flag



//offsets array

//
#define game_var_off_gear game_variable_offsets_gear

//
#define game_var_off_max_gear game_variable_offsets_max_gear

//
#define game_variable_offsets_countdown_flag

//
#define game_var_off_pause_flag game_variable_offsets_pause_flag

//
#define asm_code_instr_off_sh_del assembly_code_instruction_offsets_shifting_delay

//
#define asm_code_instr_off_db_var_disp assembly_code_instruction_offsets_dashboard_variable_display



//array sizes for dynamic pointers

//
#define game_var_off_arr_size_gear game_variable_offsets_array_size_gear

//
#define game_var_off_arr_size_max_gear game_variable_offsets_array_size_max_gear



//dynamic pointers

//
#define game_var_d_ptr_gear game_variable_dynamic_pointer_gear

//
#define game_var_d_ptr_max_gear game_variable_dynamic_pointer_max_gear



//constatnt pointers

//
#define game_var_f_ptr_gear game_variable_first_pointer_gear

//
#define game_var_f_ptr_max_gear game_variable_first_pointer_max_gear

//
#define game_var_s_ptr_cdown_falg game_variable_static_pointer_countdown_flag

//
#define game_var_s_ptr_pause_flag game_variable_static_pointer_pause_flag

//
#define asm_code_instr_s_ptr_sh_del assembly_code_instruction_static_pointer_shifting_delay

//
#define asm_code_instr_s_ptr_db_var_disp assembly_code_instruction_static_pointer_dashboard_variable_display



//byte arrays

//
#define asm_code_instr_og_b_sh_del assembly_code_instruction_original_bytes_shifting_delay

//
#define asm_code_instr_rp_b_sh_del assembly_code_instruction_replacement_bytes_shifting_delay

//
#define asm_code_instr_og_b_db_var_disp assembly_code_instruction_original_bytes_dashboard_variable_display

//this one isn't a constant because it will be filled later with bytes with address to script gear
#define asm_code_instr_rp_b_db_var_disp assembly_code_instruction_replacement_bytes_dashboard_variable_display



//byte arrays size

//
#define asm_code_instr_b_arr_size_sh_del assembly_code_instruction_bytes_array_size_shifting_delay

//
#define asm_code_instr_b_arr_size_db_var_disp assembly_code_instruction_bytes_array_size_dashboard_variable_display

//config vars

//flags to switch

//
#define flag_gearboxbox_type flag_gearbox_type

//
#define flag_b_to_use_sh_del flag_bytes_to_use_shifting_delay



//init constants

//
#define b_to_use_sh_del bytes_to_use_shifting_delay

//
#define b_to_use_db_var_disp bytes_to_use_dashboard_variable_display



//hotkeys

//
#define hk_clutch hotkey_clutch

//
#define hk_sw_gbox_type hotkey_switch_gearbox_type

//
#define hk_mod_key hotkey_modifier_key

//
#define hk_sw_sh_del_b hotkey_switch_shifting_delay_bytes



//hotkeys for sequential gearbox type

//
#define hk_gear_dec hotkey_gear_decrease

//
#define hk_gear_inc hotkey_gear_increase



//hotkeys for H-pattern gearbox type

//
#define hk_gear_N hotkey_gear_Neutral

//
#define hk_gear_1 hotkey_gear_First

//
#define hk_gear_2 hotkey_gear_Second

//
#define hk_gear_3 hotkey_gear_Third

//
#define hk_gear_4 hotkey_gear_Fourth

//
#define hk_gear_5 hotkey_gear_Fifth

//
#define hk_gear_6 hotkey_gear_Sixth

#endif
*/