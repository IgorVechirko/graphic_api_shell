#ifndef GAS_File_H
#define GAS_File_H

#include "Common.h"

#include <filesystem>
#include <stdio.h>

#include "Ref.h"
#include "DataBuff.h"

namespace GAS
{

	class File
		: public Ref
	{

	public:

		File();
		virtual ~File();

		bool init( const std::filesystem::path& path );

		bool open();
		void close();
		bool isOpen();

		size_t read( char* buff, size_t read_size );
		size_t readToInnerBuff();

		const DataBuff* getInnerBuff() const;
		std::shared_ptr<DataBuff> stealInnerBuff();

		const std::filesystem::path& getPath() const;

	private:

		std::filesystem::path path_;

		std::unique_ptr<DataBuff> buffer_;

		FILE* filesystem_file_;
	};

}


#endif //GAS_File_H