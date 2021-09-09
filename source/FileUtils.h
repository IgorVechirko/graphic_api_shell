#ifndef GAS_FileUtils_H
#define GAS_FileUtils_H

#include "Common.h"

#include <filesystem>

#include "WorkingScopeProvider.h"
#include "File.h"
#include "AutoRef.h"

namespace GAS
{

	class FileUtils
		: public WorkingScopeProvider
	{

	public:

		FileUtils();
		MAKE_UNCOPYABLE(FileUtils);
		virtual ~FileUtils();

		AutoRef<File> getFile( const std::filesystem::path& path );

		AutoRef<File> cacheFile( const std::filesystem::path& path );
		AutoRef<File> getCachedFile( const std::filesystem::path& path );
		void uncacheFile( const std::filesystem::path& path );

	private:

		std::map<std::filesystem::path,File*> cached_files_;
		std::mutex cache_lock_;

	};

}

#endif //GAS_FileUtils_H