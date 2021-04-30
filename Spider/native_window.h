#pragma once
#include<include/views/cef_window_delegate.h>
#include<include/views/cef_window.h>
#include<include/views/cef_view.h>
#include<include/cef_base.h>
#include <functional>
#include<map>
#include<mutex>
//#include"../base/window_size.h"
namespace seraphim {
	class BrowserClient;

	class NativeWindow : public CefBaseRefCounted {
	private:
		
		NativeWindow(HINSTANCE hInstance);
	private:
		HWND mWnd{ NULL };
		HINSTANCE mInstance;
		
	public:
		static CefRefPtr<NativeWindow> Make(HINSTANCE hInstance);
		static LRESULT CALLBACK  WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
		static bool  kbRegistr;
	public:
		UINT_PTR mTimer;

		void RegisteMessageProcess(UINT msg, std::function<LRESULT(WPARAM, LPARAM)>  process);
		void UnRegisteMessageProcess(UINT msg, std::function<LRESULT(WPARAM, LPARAM)> fptr);
		HWND GetHandle() const {
			return mWnd;
		}
		HINSTANCE GetInstance() const {
			return mInstance;
		}
		void Init();
		void Close();
		void Destory();
	private:
		std::multimap<DWORD,std::function<LRESULT(WPARAM, LPARAM)>> mmMsgProcess;
		std::mutex  mLookMutex{};
		void InitMessageProcess();
		BOOL InitInstance(HINSTANCE hInstance, int nCmdShow);
		LRESULT  OnCreate(WPARAM wParam, LPARAM lParam);
		LRESULT  OnSize(WPARAM wParam, LPARAM lParam);
		LRESULT  OnDestory(WPARAM wParam, LPARAM lParam);
		
		IMPLEMENT_REFCOUNTING(NativeWindow);
		DISALLOW_COPY_AND_ASSIGN(NativeWindow);
	};

};
