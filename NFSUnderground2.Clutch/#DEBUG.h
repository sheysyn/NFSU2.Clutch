#pragma once
#include <windows.h>

#include <cstdint>
#include <thread>
#include <chrono>
#include <atomic>

#define DEBUGGER_CONSOLE

#ifdef DEBUGGER_CONSOLE

//#define DEBUGGER_CONSOLE~

#include <string>
#include <sstream>
#include <fstream>

//---------------------------------------------------------------------------

inline char const
*
get_separator
(
	char

	separator_symbol
	= '-'
	//
	,

	size_t

	num_of_symbols
	= 100
	//
)
//returns the separator strip as a string of n x characters
{
	return std::string(num_of_symbols, separator_symbol).c_str()
		//
		;
}

//---------------------------------------------------------------------------

inline char const
*
get_current_time
()
//returns formatted time
{
	time_t

		now
		= time(nullptr)
		//
		;

	struct tm

		time_converted
		//
		;

	localtime_s
	(
		&time_converted,
		&now
	)
		//
		;

	char

		buffer[30]
		//
		;

	strftime
	(
		buffer,

		sizeof(buffer),

		"%Y-%m-%d %H:%M:%S",

		&time_converted
	)
		//
		;

	return buffer
		//
		;
}

//---------------------------------------------------------------------------

inline void

get_c_str_debug_info
(
	bool

	separator_use
	= true
	//
	,

	bool

	current_time_show
	= true
	//
)
{
	if (separator_use)
	{
		OutputDebugStringA
		("\n")
			//
			;

		OutputDebugStringA
		(get_separator())
			//
			;
	}

	if (current_time_show)
	{
		OutputDebugStringA
		("\n[")
			//
			;

		OutputDebugStringA
		(get_current_time())
			//
			;

		OutputDebugStringA
		("]")
			//
			;
	}

	OutputDebugStringA
	("\n")
		//
		;
}

//---------------------------------------------------------------------------

template <typename reinterpret_type, typename var_to_put_in>
inline void

debug_info
(
	char const
	*
	text_to_put
	//
	,

	var_to_put_in

	varible_after_text
	//
)
{

	OutputDebugStringA
	("\n")
		//
		;

	OutputDebugStringA
	(get_separator())
		//
		;

	OutputDebugStringA
	("\n[")
		//
		;

	OutputDebugStringA
	(get_current_time())
		//
		;

	OutputDebugStringA
	("]")
		//
		;

	OutputDebugStringA
	("\n")
		//
		;

	OutputDebugStringA
	(text_to_put)
		//
		;

	if (
		varible_after_text
		!=
		NULL
		)
	{
		std::ostringstream

			tmp
			//
			;

		tmp
			<< static_cast<reinterpret_type>(varible_after_text)
			//
			;

		OutputDebugStringA
		(tmp.str().c_str())
			//
			;
	}

	OutputDebugStringA
	("\n")
		//
		;

	OutputDebugStringA
	(get_separator())
		//
		;

	OutputDebugStringA
	("\n")
		//
		;
}

//---------------------------------------------------------------------------

#endif