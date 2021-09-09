#include "File.h"

const size_t kStorageBlockSize = 512;

namespace GAS
{

	File::File()
		: buffer_(nullptr)
		, filesystem_file_{nullptr}
	{
	}

	File::~File()
	{
		close();
	}

	bool File::init( const std::filesystem::path& path )
	{
		path_ = path;

		return true;
	}

	bool File::open()
	{
		if( !filesystem_file_ )
		{
			filesystem_file_ = fopen( path_.generic_string().c_str(), "r" );

			if(!filesystem_file_)
			{
				LOG_ERROR( "Can't open file %s", path_.generic_string().c_str() );
				return false;
			}
		}
		else
		{
			LOG_WARNING( "File %s already opened (%p)", path_.generic_string().c_str(), this );
			return false;
		}

		return true;
	}

	void File::close()
	{
		if( filesystem_file_ )
		{
			fclose(filesystem_file_);
			filesystem_file_ = nullptr;
		}
		else
		{
			LOG_WARNING( "File %s not opened (%p)", path_.generic_string().c_str(), this );
		}
	}
	
	bool File::isOpen()
	{
		return filesystem_file_;
	}

	size_t File::read( char* buff, size_t read_size )
	{
		if ( !filesystem_file_ )
		{
			LOG_ERROR( "Can't read from not open file %s", path_.generic_string().c_str() );
			return 0;
		}

		return fread( buff, 1, read_size, filesystem_file_ );
	}
		
	size_t File::readToInnerBuff()
	{
		if ( !filesystem_file_ )
		{
			LOG_ERROR( "Can't read from not open file %s", path_.generic_string().c_str() );
			return 0;
		}

		auto file_size = std::filesystem::file_size(path_);

		if( !buffer_ )
		{
			buffer_.reset( new DataBuff() );
		}

		buffer_->allocBuff(file_size);

		size_t readed_chars_count = 0;
		size_t buffers_free_size = kStorageBlockSize < buffer_->getBuffSize() - buffer_->getDataSize()  ?
			kStorageBlockSize : buffer_->getBuffSize() - buffer_->getDataSize();

		while( readed_chars_count = fread( buffer_->getBuff(buffer_->getDataSize()), 1, buffers_free_size, filesystem_file_) )
		{
			buffer_->setDataSize( buffer_->getDataSize() + readed_chars_count );
		}

		return buffer_->getBuffSize();
	}

	const DataBuff* File::getInnerBuff() const
	{
		return buffer_.get();
	}

	std::shared_ptr<DataBuff> File::stealInnerBuff()
	{
		return std::shared_ptr<DataBuff>( buffer_.release() );
	}

	const std::filesystem::path& File::getPath() const
	{
		return path_;
	}

}