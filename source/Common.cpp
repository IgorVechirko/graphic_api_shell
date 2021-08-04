#include "Common.h"

#include <stdio.h>
#include <stdarg.h>
#ifdef _WIN32
#include <Windows.h>
#endif

namespace GAS
{
	static LogLevel log_level{ LogLevel::kThird };
	static unsigned int log_masks{ 0x0 };
	static std::mutex log_lock;

	enum class NixLogTextColour
	{
		kRed = 31,
		kGreen = 32,
		kYellow = 33,
		kWhite = 37
	};

	enum class WinLogTextColour
	{
		kRed = 12,
		kGreen = 10,
		kYellow = 14,
		kWhite = 7
	};

	static char kColourPattern[]{ "\x1B[%dm" };
	static char kColourReset[]{ "\033[0m" };
	#ifdef _WIN32
		static const HANDLE kHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	#endif
	std::map<LogLevel, NixLogTextColour> nix_level_to_colour{
		{LogLevel::kFirst, NixLogTextColour::kRed},
		{LogLevel::kSecond, NixLogTextColour::kYellow},
		{LogLevel::kThird, NixLogTextColour::kGreen},
	};

	std::map<LogLevel, WinLogTextColour> win_level_to_colour{
		{LogLevel::kFirst, WinLogTextColour::kRed},
		{LogLevel::kSecond, WinLogTextColour::kYellow},
		{LogLevel::kThird, WinLogTextColour::kGreen},
	};

	void setLogParams(LogLevel level, unsigned int masks )
	{
		log_level = level;
		log_masks = masks;
	}

	int getLevelColourCode(LogLevel level)
	{
	#ifdef _WIN32
		auto it = win_level_to_colour.find(level);
		WinLogTextColour colour_code = it != win_level_to_colour.end() ? it->second : WinLogTextColour::kWhite;
	#else
		auto it = nix_level_to_colour.find(level);
		NixLogTextColour colour_code = it != nix_level_to_colour.end() ? it->second : NixLogTextColour::kWhite;
	#endif
		return static_cast<int>(colour_code);
	}

	void setLogTextColour(LogLevel level)
	{
		int colour_code = getLevelColourCode(level);
	#ifdef _WIN32
		SetConsoleTextAttribute(kHandle, colour_code);
	#else
		printf(kColourPattern, colour_code);
	#endif
	}

	void resetLogTextColour()
	{
	#ifdef _WIN32
		SetConsoleTextAttribute(kHandle, static_cast<int>(WinLogTextColour::kWhite));
	#else
		printf(kColourReset);
	#endif
	}

	void log( LogLevel level, LogMask mask, const char* format, ... )
	{
		if( static_cast<int>(level) <= static_cast<int>(log_level) )
		{
			if ( (log_masks == 0x0) || (log_masks & static_cast<unsigned int>(mask)) )
			{
				va_list var_args;
				va_start(var_args, format);

				{
					std::lock_guard<std::mutex> lock_quard(log_lock);
					setLogTextColour(level);
					vprintf(format, var_args);
					resetLogTextColour();
					printf( "\n" );
				}

				va_end(var_args);
			}
		}
	}
}