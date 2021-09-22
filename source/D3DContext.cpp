#include "D3DContext.h"

namespace
{

	//typedef LRESULT (CALLBACK* WNDPROC)(HWND, UINT, WPARAM, LPARAM);
	LRESULT WINAPI WindProtocol(HWND a, UINT b, WPARAM c, LPARAM d)
	{
		return DefWindowProcA( a, b, c, d );
	}

	std::string getErrorCodeDesc( DWORD error_code )
	{
		LPSTR messageBuffer = nullptr;

		//Ask Win32 to give us the string version of that message ID.
		//The parameters we pass in, tell Win32 to create the buffer that holds the message for us (because we don't yet know how long the message string will be).
		size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
									 NULL, error_code, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&messageBuffer, 0, NULL);
    
		std::string result(messageBuffer, size);
    
		LocalFree(messageBuffer);
            
		return result;
	}

	std::string getLastErrorCodeDesc()
	{
		return getErrorCodeDesc( GetLastError() );
	}

}

namespace GAS
{
	D3DContext::D3DContext()
		: wnd_class_options_{0}
		, wnd_class_{0}
		, wnd_handler_{nullptr}
		, wnd_name_{ "Graphic API Shell" }
	{
		//
		//window default options. Make it setupable in future
		//

		wnd_class_options_.lpfnWndProc = DefWindowProcA;
		wnd_class_options_.lpszClassName = "GASClass";
	}

	D3DContext::~D3DContext()
	{
	}

	bool D3DContext::init()
	{
		wnd_class_ = RegisterClass( &wnd_class_options_ );
		if( !wnd_class_ )
		{
			LOG_ERROR( "Can't create window classs. Error(%d): %s",
					  GetLastError(), 
					  getLastErrorCodeDesc().c_str() );

			return false;
		}

		wnd_handler_ = CreateWindow( wnd_class_options_.lpszClassName,
									 wnd_name_.c_str(),
									 WS_OVERLAPPEDWINDOW,
									 CW_USEDEFAULT,
									 CW_USEDEFAULT,
									 CW_USEDEFAULT,
									 CW_USEDEFAULT,
									 NULL,
									 NULL,
									 NULL,
									 this);
		if ( !wnd_handler_ )
		{
			LOG_ERROR( "Can't create window. Error(%d): %s",
					  GetLastError(), 
					  getLastErrorCodeDesc().c_str() );

			UnregisterClass( wnd_class_options_.lpszClassName, NULL );
			wnd_class_ = 0;

			return false;
		}

		ShowWindow( wnd_handler_, SW_SHOW );

		int i = 0;
		while( i++<10 )
		{
			Sleep(100);
			LOG_ERROR( "Window working" );
		}

		DestroyWindow( wnd_handler_ );
		UnregisterClass( wnd_class_options_.lpszClassName, NULL );

		return true;
	}

}