#ifndef GAS_DataBuff_H
#define GAS_DataBuff_H

#include "Common.h"

#include "Allocator.h"


namespace GAS
{

	class DataBuff
		: protected Allocator
	{

	public:

		DataBuff();
		virtual ~DataBuff();

		void allocData( size_t data_size );
		void deallocData();

		char* getData( size_t offset = 0) const;
		size_t getDataSize() const;

	private:

		char* data_;
		size_t data_size_;

	};

}


#endif //GAS_DataBuff_H