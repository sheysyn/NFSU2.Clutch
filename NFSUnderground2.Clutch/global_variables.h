#pragma once
#include "macro.h"
#include "class_gearbox.h"
#include "config_loader_function.h"
#include "constants.h"

//for extended names look in "macro.h"

//---------------------------------------------------------------------------

extern SYSTEM_INFO

system_info
//system info for page size in operating system
;

//---------------------------------------------------------------------------

extern std::atomic<bool>

running_flag
//flag for running loops in threads
,


permission_for_main
//determines whether the main thread is running or not
;

//---------------------------------------------------------------------------

extern std::thread

game_vars_and_cond_update
//thread with updating values of in-game variables and checking the conditions for the gearbox_operating thread to work
,


gearbox_operating
//the main thread in wich gearbox operates
;

//---------------------------------------------------------------------------

extern uint32_t

script_gear
//32-bit address in app memory space
;

extern uint8_t
*
game_var_d_ptr_gear
//dynamic pointer to in-game gear var
;

//---------------------------------------------------------------------------

extern uint8_t const
*
game_var_d_ptr_max_gear
//dynamic pointer to in-game max gear const
;


//---------------------------------------------------------------------------

//array with bytes for assembly code instruction to:
extern uint8_t

asm_code_instr_rp_b_db_var_disp
[]
//patch instruction with dashboard variable display
;

//---------------------------------------------------------------------------

//flags to switch
extern uint16_t

flag_gearboxbox_type
//
,


flag_b_to_use_sh_del
//
,


flag_b_to_use_db_var_disp
//
;

//---------------------------------------------------------------------------

extern void
*
bottom_address
//
,

*
top_address
//
;

//---------------------------------------------------------------------------