#include "Common.h"

#include <stdio.h>
#include <stdarg.h>

namespace GAS
{
	static LogLevel log_level{ LogLevel::kThird };
	static unsigned int log_masks{ 0x0 };
	static std::mutex log_lock;

	static char kColourPattern[]{ "\x1B[%dm" };
	static char kColourReset[]{ "\033[0m" };
	std::map<LogLevel, LogTextColour> level_to_colour{
		{LogLevel::kFirst, LogTextColour::kRed},
		{LogLevel::kSecond, LogTextColour::kYellow},
		{LogLevel::kThird, LogTextColour::kGreen},
	};

	void setLogParams(LogLevel level, unsigned int masks )
	{
		log_level = level;
		log_masks = masks;
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
					auto it = level_to_colour.find(level);
					LogTextColour colour_code = it != level_to_colour.end() ? it->second : LogTextColour::kWhite;
					printf(kColourPattern, static_cast<int>(colour_code));
					vprintf(format, var_args);
					printf(kColourReset);
					printf( "\n" );
				}

				va_end(var_args);
			}
		}
	}
}