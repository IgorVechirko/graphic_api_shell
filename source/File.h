#ifndef GAS_File_H
#define GAS_File_H

#include "Common.h"

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

		void setData( DataBuff* buff );

		const DataBuff* getConstData() const;
		DataBuff* getData() const;

		void setPath( const std::string& path );
		const std::string& getPath() const;

	private:

		std::string path_;

		DataBuff* data_;

	};

}


#endif //GAS_File_H