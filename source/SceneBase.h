#ifndef GAS_SceneBase_H
#define GAS_SceneBase_H

#include "Common.h"

#include "Ref.h"
#include "Camera.h"
#include "WorkingScopeProvider.h"
#include "AutoRef.h"

namespace GAS
{

	class SceneBase
		: public Ref
		, public WorkingScopeProvider
	{

	public:

		SceneBase();
		virtual ~SceneBase();

		bool init();

		void setCamera( Camera* camera );
		AutoRef<Camera> getCamera() const;
		
	protected:

		virtual void onInit(){};

	private:

		Camera* camera_;

	};

}


#endif //GAS_SceneBase_H