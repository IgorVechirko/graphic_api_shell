#ifndef GAS_Common_H
#define GAS_Common_H

#include <vector>
#include <map>
#include <queue>
#include <list>
#include <stack>
#include <deque>
#include <array>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <algorithm>
#include <memory>
#include <thread>
#include <future>
#include <atomic>
#include <mutex>
#include <shared_mutex>
#include <semaphore>
#include <assert.h>
#include <chrono>

//#define _ASSERT( __arg__ ) assert( __arg__ );

#define MAKE_UNCOPYABLE(__TYPE__)\
__TYPE__( const __TYPE__& ) = delete;\
__TYPE__( __TYPE__&& ) = delete;\
const __TYPE__& operator= ( const __TYPE__& ) = delete;\
const __TYPE__& operator= ( __TYPE__&& ) = delete;\

enum class LogLevel
{
	kFirst,
	kSecond,
	kThird
};

enum class LogMask
{
	kUniversal = 0x1 << 0
};

namespace GAS
{
	void setLogParams(LogLevel level, unsigned int masks );
	void log( LogLevel level, LogMask mask, const char* format, ... );

	class LogTrace
	{

	public:

		LogTrace( const std::string& trace_text, LogLevel log_level = LogLevel::kThird );
		virtual ~LogTrace();

	private:

		std::string trace_text_;
		LogLevel log_level_;

	};

}



#define LOG_ERROR( __FORMAT__, ... ) log( LogLevel::kFirst, LogMask::kUniversal, __FORMAT__, __VA_ARGS__ );
#define LOG_WARNING( __FORMAT__, ... ) log( LogLevel::kSecond, LogMask::kUniversal, __FORMAT__, __VA_ARGS__ );
#define LOG_DEBUG( __FORMAT__, ... ) log( LogLevel::kThird, LogMask::kUniversal, __FORMAT__, __VA_ARGS__ );

#define FUNC_TRACE_ERROR LogTrace trance_func( __FUNCTION__, LogLevel::kFirst );
#define FUNC_TRACE_WARNING LogTrace trance_func( __FUNCTION__, LogLevel::kSecond );
#define FUNC_TRACE_DEBUG LogTrace trance_func( __FUNCTION__, LogLevel::kThird );

#endif //GAS_Common_H