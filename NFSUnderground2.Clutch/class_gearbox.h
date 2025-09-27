#pragma once
#include "macro.h"
#include "functions.h"
#include "class_key_state.h"
#include "global_variables.h"

//---------------------------------------------------------------------------

class class_gearbox
{
protected:

	void

		go_to_neutral
		()
		//
		;

	void

		go_to_script
		()
		//
		;

	class_key_state

		clutch
		//needed only first bit
		;

	uint8_t

		clutch_state
		= 0
		//
		;

	enum class clutch_states : uint8_t
	{
		_off = 0,

		_on = 1
	}
	//
	;

public:

	uint8_t
		&
		clutch_logic
		()
		//
		;

	virtual void

		shifting
		() = 0
		//
		;

	void

		operate
		()
		//
		;

	virtual

		~class_gearbox
		() = default
		//
		;
}
//
;

//---------------------------------------------------------------------------

class class_sequential_type : public class_gearbox
{
public:

	void

		shifting
		() override
		//
		;

	~class_sequential_type
	() override = default
		//
		;

private:

	class_key_state

		shifting_flags
		//needed only first two bits
		;

	enum class holding_flag_bit_index : uint8_t
	{
		_dec = 0,

		_inc = 1
	}
	//
	;

	void

		gear_decrease
		()
		//
		;

	void

		gear_increase
		()
		//
		;
}
//
;

//---------------------------------------------------------------------------

class class_H_pattern_type :public class_gearbox
{
public:

	void

		shifting
		() override
		//
		;

	~class_H_pattern_type
	() override = default
		//
		;

private:

	class_key_state

		shifting_flags
		//needed n gears bits
		;


	enum class holding_flag_bit_index :uint8_t
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
	//
	;

	void

		shift_to_n_gear
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
		//
		;
}
//
;

//---------------------------------------------------------------------------

extern class_gearbox
*
gearbox
//pointer to gearbox class object (for polymorphism)
;

//---------------------------------------------------------------------------