#include "DataBuff.h"

#include "WorkingScope.h"

namespace GAS
{

	DataBuff::DataBuff()
		: buffer_{ nullptr }
		, buffer_size_{ 0 }
		, data_size_{ 0 }
	{
	}

	DataBuff::~DataBuff()
	{
		deallocBuff();
	}

	void DataBuff::allocBuff( size_t buffer_size )
	{
		if ( buffer_size && (buffer_size > buffer_size_) )
		{
			if ( buffer_ )
			{
				deallocate(buffer_);
			}

			buffer_size_ = buffer_size;

			buffer_ = static_cast<char*>( allocate(buffer_size_) );
		}
	}

	void DataBuff::deallocBuff()
	{
		deallocate(buffer_);
		buffer_ = nullptr;
		buffer_size_ = 0;
		data_size_ = 0;
	}

	char* DataBuff::getBuff( size_t offset ) const
	{
		if ( offset >= buffer_size_ )
		{
			LOG_ERROR( "Buffer size if less then %d", offset );
			return nullptr;	
		}

		return buffer_ + offset;
	}
	
	size_t DataBuff::getBuffSize() const
	{
		return buffer_size_;
	}

	void DataBuff::setDataSize(size_t data_size)
	{
		if ( data_size > buffer_size_ )
		{
			LOG_ERROR( "Data size(%d) can't be more then buffer size(%d)", data_size, buffer_size_);
			return;
		}

		data_size_ = data_size;
	}

	size_t DataBuff::getDataSize() const
	{
		return data_size_;
	}
}