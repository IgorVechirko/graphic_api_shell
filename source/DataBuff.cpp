#include "DataBuff.h"

#include "WorkingScope.h"

namespace GAS
{

	DataBuff::DataBuff()
		: data_( nullptr )
		, data_size_( 0 )
	{
	}

	DataBuff::~DataBuff()
	{
		getScope()->getCreator()->deallocate(data_);
	}

	void DataBuff::init( char* data, size_t data_size )
	{
		data_ = data;
		data_size_ = data_size;
	}

	char* DataBuff::getData()
	{
		return data_;
	}
	
	size_t DataBuff::getDataSize()
	{
		return data_size_;
	}
}