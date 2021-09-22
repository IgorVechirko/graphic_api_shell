#ifndef GAS_D3DContext_H
#define GAS_D3DContext_H

#include "Windows.h"

#include <d3d.h>

#include "Common.h"
#include "WorkingScopeProvider.h"
namespace GAS
{

	class D3DContext
		: public WorkingScopeProvider
	{

	public:

		D3DContext();
		MAKE_UNCOPYABLE(D3DContext);
		virtual ~D3DContext();

		bool init();
		bool run();
		bool destroy();

	private:

		//window context
		WNDCLASS wnd_class_options_;
		ATOM wnd_class_;
		HWND wnd_handler_;

		std::string wnd_name_;

	};

}


#endif //GAS_D3DContext_H