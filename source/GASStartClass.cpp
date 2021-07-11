#include "GASStartClass.h"

#include "Allocator.h"
#include "ObjectsCreator.h"


namespace GAS
{

	GASStartClass::GASStartClass()
	{
	}

	GASStartClass::~GASStartClass()
	{
	}

	void GASStartClass::run()
	{
		LOG_ERROR( "Hello Graphic API Shell" );
	}

}