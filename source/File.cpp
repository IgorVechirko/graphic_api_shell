#include "File.h"

namespace GAS
{

	File::File()
		: data_(nullptr)
	{
	}

	File::~File()
	{
	}

	void File::setData( DataBuff* buff )
	{
		data_ = buff;
	}

	const DataBuff* File::getConstData() const
	{
		return data_;
	}

	DataBuff* File::getData() const
	{
		return data_;
	}

	void File::setPath( const std::string& path )
	{
		path_ = path;
	}

	const std::string& File::getPath() const
	{
		return path_;
	}

}