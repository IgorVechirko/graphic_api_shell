#include "Common.h"

#include <stdio.h>
#include <stdarg.h>

namespace GAS
{
	static LogLevel log_level{ LogLevel::kFirst };
	static unsigned int log_masks{ 0x0 };
	static std::mutex log_lock;

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
					vprintf(format, var_args);
					printf( "\n" );
				}

				va_end(var_args);
			}
		}
	}
}