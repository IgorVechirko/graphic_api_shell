#include "DataBuff.h"

#include "WorkingScope.h"

namespace GAS
{

	DataBuff::DataBuff()
		: data_( nullptr )
		, data_size_( 0 )
	{
		deallocData();
	}

	DataBuff::~DataBuff()
	{
	}

	void DataBuff::allocData( size_t data_size )
	{
		if ( data_size < data_size_ )
		{
			if ( data_ )
			{
				deallocate(data_);
			}

			data_size_ = data_size;

			data_ = static_cast<char*>( allocate(data_size_) );
		}
	}

	void DataBuff::deallocData()
	{
		deallocate(data_);
		data_ = nullptr;
		data_size_ = 0;
	}

	char* DataBuff::getData( size_t offset ) const
	{
		if ( offset >= data_size_ )
		{
			LOG_ERROR( "Data size if less then %d", offset );
			return nullptr;	
		}

		return data_ + offset;
	}
	
	size_t DataBuff::getDataSize() const
	{
		return data_size_;
	}
}