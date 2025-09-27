#pragma once
#include "macro.h"

//---------------------------------------------------------------------------

char const

_config_file_path
[] =
{
	".\\NFSUnderground2.Clutch.ini"
}
//config file path
;

//---------------------------------------------------------------------------

template <typename return_number_type>
inline return_number_type

config_load_value
(
	char const
	* const
	section_name
	//section to check
	,

	char const
	* const
	key_name
	//key to the desired result
	,

	int

	default_value_int
	//default value to return, if config value is empty
	,

	char const
	*
	config_file_path
	= _config_file_path
	//config file path
)
{
	static size_t const

		temp_buffer_size
		= 50
		//
		;

	static char

		temp_buffer
		[temp_buffer_size]
		//
		,

		default_value
		[6]
		//
		;

	_itoa
	(
		default_value_int,

		default_value,

		10
	)
		//
		;

	GetPrivateProfileStringA
	(
		section_name,

		key_name,

		default_value,

		temp_buffer,

		temp_buffer_size,

		config_file_path
	)
		//
		;

	return static_cast<return_number_type>(atoi(temp_buffer))
		//
		;
}

//---------------------------------------------------------------------------

#ifdef DEBUGGER_CONSOLE

inline void

get_config_check
()
{
	std::ifstream

		configFile
		//
		;

	configFile.open
	(_config_file_path)
		//
		;

	if (
		!configFile.is_open()
		)
	{
		OutputDebugStringA
		("config file isn't fine.")
			//
			;
	}
	else
	{
		configFile.close
		()
			//
			;

		OutputDebugStringA
		("config file is fine.")
			//
			;
	}
}

#endif

//---------------------------------------------------------------------------