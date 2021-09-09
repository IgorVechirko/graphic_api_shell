#include "FileUtils.h"

#include <fstream>

#include "WorkingScope.h"

namespace GAS
{

	FileUtils::FileUtils()
	{
	}

	FileUtils::~FileUtils()
	{
	}

	AutoRef<File> FileUtils::getFile( const std::filesystem::path& path )
	{
		AutoRef<File> file{nullptr};
		
		if( path.empty() )
		{
			LOG_WARNING( "Specified path is empty." );
			return file;
		}

		auto absolute_path = path;

		if( !absolute_path.is_absolute() )
			absolute_path = std::filesystem::absolute(absolute_path);

		if( !std::filesystem::exists( absolute_path ) )
		{
			LOG_WARNING( "Specified file %s doesn't exist", absolute_path.generic_string().c_str() );
			return file;
		}

		file = getScope()->getCreator()->createAndInitObj<File>(&File::init, absolute_path);

		return file;
	}

	AutoRef<File> FileUtils::cacheFile( const std::filesystem::path& path )
	{
		std::unique_lock lock(cache_lock_);

		auto find_it = cached_files_.find( path );
		if( find_it != cached_files_.end() )
		{
			return find_it->second;
		}

		auto file = getFile( path );
		if ( !&file )
		{
			return nullptr;
		}

		cached_files_[ path ] = &file;
		file->retain();

		return file;
	}

	AutoRef<File> FileUtils::getCachedFile( const std::filesystem::path& path )
	{
		std::unique_lock lock(cache_lock_);

		AutoRef<File> file{nullptr};

		auto find_it = cached_files_.find( path );
		if( find_it != cached_files_.end() )
		{
			file.reset( find_it->second );
		}

		return file;
	}

	void FileUtils::uncacheFile( const std::filesystem::path& path )
	{
		std::unique_lock lock(cache_lock_);

		auto find_it = cached_files_.find( path );
		if( find_it != cached_files_.end() )
		{
			find_it->second->release();
			cached_files_.erase(find_it);
		}
	}
}