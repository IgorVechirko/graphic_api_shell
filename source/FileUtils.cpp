#include "FileUtils.h"

#include "WorkingScope.h"

namespace GAS
{

	FileUtils::FileUtils()
	{
	}

	FileUtils::~FileUtils()
	{
	}

	AutoRef<File> FileUtils::loadFile( const std::string& path )
	{
		auto file = getScope()->getCreator()->createObject<File>();
		return file;
	}

	void FileUtils::cacheFile( const std::string& path )
	{
	}

	void FileUtils::uncacheFile( const std::string& path )
	{
	}

}