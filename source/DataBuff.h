#ifndef GAS_DataBuff_H
#define GAS_DataBuff_H

#include "Common.h"

#include "Ref.h"
#include "WorkingScopeProvider.h"

namespace GAS
{

	class DataBuff
		: public Ref
		, public WorkingScopeProvider
	{

	public:

		DataBuff();
		virtual ~DataBuff();

		void init( char* data, size_t data_size );

		char* getData() const;
		size_t getDataSize() const;

	private:

		char* data_;
		size_t data_size_;

	};

}


#endif //GAS_DataBuff_H