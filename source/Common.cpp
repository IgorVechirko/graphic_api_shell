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

	static char kColourPattern[]{ "\x1B[%dm" };
	static char kColourReset[]{ "\033[0m" };

#ifdef _WIN32

	static const HANDLE kHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	enum class LogTextColour
	{
		kRed = 12,
		kGreen = 10,
		kYellow = 14,
		kWhite = 7
	};

#else

	enum class LogTextColour
	{
		kRed = 31,
		kGreen = 32,
		kYellow = 33,
		kWhite = 37
	};

#endif


	std::map<LogLevel, LogTextColour> log_level_to_colour{
		{LogLevel::kFirst, LogTextColour::kRed},
		{LogLevel::kSecond, LogTextColour::kYellow},
		{LogLevel::kThird, LogTextColour::kGreen},
	};

	void setLogParams(LogLevel level, unsigned int masks )
	{
		log_level = level;
		log_masks = masks;
	}

	int getLevelColourCode(LogLevel level)
	{
		auto findIt = log_level_to_colour.find(level);
		LogTextColour colour_code = findIt != log_level_to_colour.end() ? findIt->second : LogTextColour::kWhite;

		return static_cast<int>(colour_code);
	}

	void setLogTextColour(LogLevel level)
	{
		auto colour_code = getLevelColourCode(level);
	#ifdef _WIN32
		SetConsoleTextAttribute(kHandle, colour_code);
	#else
		printf(kColourPattern, colour_code);
	#endif
	}

	void resetLogTextColour()
	{
	#ifdef _WIN32
		SetConsoleTextAttribute(kHandle, static_cast<int>(LogTextColour::kWhite));
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


	//class LogTrace
	LogTrace::LogTrace( const std::string& trace_text, LogLevel log_level )
		: log_level_( log_level )
		, trace_text_( trace_text )
	{
		log( log_level_, LogMask::kUniversal, ">>> %s", trace_text_.c_str() );
	}
	LogTrace::~LogTrace()
	{
		log( log_level_, LogMask::kUniversal, "<<< %s", trace_text_.c_str() );
	}
}