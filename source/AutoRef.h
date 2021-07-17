#ifndef GAS_AutoRef_H
#define GAS_AutoRef_H

#include <type_traits>

#include "Ref.h"

namespace GAS
{

	template< typename GuardObjType >
	class AutoRef
	{

	public: 

		AutoRef( GuardObjType* obj )
		{
			guard_obj_ = obj;

			if ( std::is_base_of<Ref,GuardObjType>() && guard_obj_ )
				((Ref*)guard_obj_)->retain();
		}

		AutoRef( const AutoRef& ref )
		{
			guard_obj_ = ref.guard_obj_;

			if ( std::is_base_of<Ref,GuardObjType>() && guard_obj_ )
				((Ref*)guard_obj_)->retain();
		}

		AutoRef( AutoRef&& ref )
		{
			guard_obj_ = ref.guard_obj_;
			ref.guard_obj_ = nullptr;
		}

		AutoRef& operator=( const AutoRef& ref )
		{
			guard_obj_ = ref.guard_obj_;

			if ( std::is_base_of<Ref,GuardObjType>() && guard_obj_ )
				((Ref*)guard_obj_)->retain();

			return *this;
		}

		AutoRef& operator=( AutoRef&& ref )
		{
			guard_obj_ = ref.guard_obj_;
			ref.guard_obj_ = nullptr;

			return *this;
		}

		GuardObjType* operator->()
		{
			return guard_obj_;
		}

		GuardObjType* operator&()
		{
			return guard_obj_;
		}

		virtual ~AutoRef()
		{
			if ( std::is_base_of<Ref,GuardObjType>() && guard_obj_ )
				((Ref*)guard_obj_)->release();
		}

		void reset( GuardObjType* guard_obj )
		{
			if ( std::is_base_of<Ref,GuardObjType>() && guard_obj_ )
				((Ref*)guard_obj_)->release();

			guard_obj_ = guard_obj;

			if ( std::is_base_of<Ref,GuardObjType>() && guard_obj_ )
				((Ref*)guard_obj_)->retain();
		}

	private:

		void* operator new( size_t size )
		{
			return nullptr;
		}
		
	private:

		GuardObjType* guard_obj_;

	};


}

#endif //GAS_AutoRef_H