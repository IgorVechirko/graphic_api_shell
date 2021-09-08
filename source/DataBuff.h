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

		void allocBuff( size_t data_size );
		void deallocBuff();

		char* getBuff( size_t offset = 0) const;
		size_t getBuffSize() const;

		void setDataSize(size_t data_size);
		size_t getDataSize() const;

	private:

		char* buffer_;
		size_t buffer_size_;
		size_t data_size_;

	};

}


#endif //GAS_DataBuff_H