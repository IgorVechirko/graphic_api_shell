#include "Common.h"

#include <stdio.h>
#include <stdarg.h>

namespace GAS
{
	static LogLevel log_level{ LogLevel::kThird };
	static unsigned int log_masks{ 0x0 };
	static std::mutex log_lock;

	char colour_pattern[]{ "\x1B[%dm" };
	std::map<LogLevel, short> level_to_colour{
		{LogLevel::kFirst, 31}, // red
		{LogLevel::kSecond, 33}, // yellow
		{LogLevel::kThird, 32}, // green
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
					short colour_code = it != level_to_colour.end() ? it->second : 37; // default white
					printf(colour_pattern, colour_code);
					vprintf(format, var_args);
					printf( "\033[0m" ); // reset text colour
					printf( "\n" );
				}

				va_end(var_args);
			}
		}
	}
}