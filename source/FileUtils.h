#ifndef GAS_FileUtils_H
#define GAS_FileUtils_H

#include "Common.h"

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

		AutoRef<File> loadFile( const std::string& path );

		void cacheFile( const std::string& path );
		void uncacheFile( const std::string& path );

	private:

		std::map<std::string,File*> cached_files_;

	};

}

#endif //GAS_FileUtils_H