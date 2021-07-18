#include "SceneBase.h"

#include "WorkingScope.h"

namespace GAS
{

	SceneBase::SceneBase()
		: camera_(nullptr)
	{
	}

	SceneBase::~SceneBase()
	{
		if( camera_ )
			camera_->release();
	}

	bool SceneBase::init()
	{
		auto cameraRef = getScope()->getCreator()->createObject<Camera>();
		setCamera( &cameraRef );

		onInit();

		return true;
	}

	void SceneBase::setCamera( Camera* camera )
	{
		if( camera_ )
			camera_->release();

		camera_ = camera;

		if( camera_ )
			camera_->retain();
	}
	
	AutoRef<Camera> SceneBase::getCamera() const
	{
		return camera_;
	}

}