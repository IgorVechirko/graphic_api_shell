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
#include <atomic>
#include <mutex>
#include <assert.h>

#define _ASSERT( __arg__ ) assert( __arg__ );

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
}



#define LOG_ERROR( __FORMAT__, ... ) log( LogLevel::kFirst, LogMask::kUniversal, __FORMAT__, __VA_ARGS__ );
#define LOG_WARNING( __FORMAT__, ... ) log( LogLevel::kSecond, LogMask::kUniversal, __FORMAT__, __VA_ARGS__ );
#define LOG_DEBUG( __FORMAT__, ... ) log( LogLevel::kThird, LogMask::kUniversal, __FORMAT__, __VA_ARGS__ );

#endif //GAS_Common_H