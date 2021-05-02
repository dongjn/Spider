#include "native_window.h"
#include "log.h"
#include "common.h"
#include<Windows.h>
#include <WinUser.h>
#include <assert.h>
#include <include/cef_app.h>
#include <include/wrapper/cef_helpers.h>

namespace seraphim {
	using seraphim::WLOG;
	LPCTSTR szWindowClass = TEXT("GameSharedRoot");

	//Debug
	const HMENU ID_ShowClient = HMENU(1);
	const HMENU ID_HideClientBtn = HMENU(2);
	const HMENU ID_LonginBtn = HMENU(3);
	const HMENU ID_BTN_TR = HMENU(4);
	const HMENU ID_QUIT_CLIENT = HMENU(5);

	WNDPROC a = nullptr;
	inline ATOM RegisterClass(HINSTANCE hInstance)
	{
		WNDCLASSEXW wcex;
		wcex.cbSize = sizeof(WNDCLASSEX);
		wcex.style = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc = &NativeWindow::WndProc;
		wcex.cbClsExtra = 0;
		wcex.cbWndExtra = 0;
		wcex.hInstance = hInstance;
		wcex.hIcon = NULL;// LoadIcon(hInstance, MAKEINTRESOURCE(IDI_GAMESHARED));
		wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName = NULL;;// MAKEINTRESOURCEW(IDC_GAMESHARED);
		wcex.lpszClassName = szWindowClass;
		wcex.hIconSm = NULL;// LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
		return RegisterClassExW(&wcex);
	}

	inline BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
	}

	void NativeWindow::Init()
	{
		//RegisterClass(mInstance);
		InitInstance(mInstance, SW_SHOW);
		InitMessageProcess();
		//mTimer = SetTimer(mWnd,0, 100, nullptr);
	}

	void NativeWindow::InitMessageProcess()
	{
		using  namespace std::placeholders;
		//mmMsgProcess.insert(std::make_pair(WM_CREATE, std::bind(&NativeWindow::OnCreate, this, _1, _2)));
		//mmMsgProcess.insert(std::make_pair(WM_DESTROY,std::bind(&NativeWindow::OnDestory,this,_1,_2)));
		//mmMsgProcess.insert(std::make_pair(WM_SIZE, std::bind(&NativeWindow::OnSize, this, _1, _2)));
	}

	BOOL NativeWindow::InitInstance(HINSTANCE hInstance, int nCmdShow)
	{
		auto hInst = hInstance; // 将实例句柄存储在全局变量中

		int cx = GetSystemMetrics(SM_CXFULLSCREEN);
		int cy = GetSystemMetrics(SM_CYFULLSCREEN);

		mWnd = CreateWindow(szWindowClass, TEXT(""), WS_OVERLAPPEDWINDOW,
			0, 0, 1024, 768, nullptr, nullptr, hInstance, nullptr);
		SetWindowLongPtr(mWnd, GWLP_USERDATA, (LONG_PTR)this);
		int code = GetLastError();
		if (!mWnd)
		{
			return FALSE;
		}

		ShowWindow(mWnd, nCmdShow);
		UpdateWindow(mWnd);
		return TRUE;
	}

	LRESULT NativeWindow::WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
	{
		do {
			//危险
			CefRefPtr<NativeWindow>  self_ = (NativeWindow*)GetWindowLongPtrW(hWnd, GWLP_USERDATA);
			if (self_.get() == nullptr) {
				break;
			}

			if (WM_NCHITTEST == msg) {
				auto x = LOWORD(lParam);
				auto y = HIWORD(lParam);
				RECT rect;
				GetWindowRect(hWnd, &rect);
				auto maxY = rect.top + 40;
				auto minY = rect.top;
			}

			if (hWnd != self_->mWnd) {
				break;
			}
			if (self_->mWnd != hWnd) {
				break;
			}

			auto itr = self_->mmMsgProcess.equal_range(msg);

			if (itr.first == itr.second) {
				break;
			}

			for (auto i = itr.first; i != itr.second; i++) {
				std::function<LRESULT(WPARAM, LPARAM)> f = i->second;
				i->second(wParam, lParam);
				break;
			}
		} while (0);
		return ::DefWindowProc(hWnd, msg, wParam, lParam);
	}

	bool NativeWindow::kbRegistr{ false };

	void NativeWindow::RegisteMessageProcess(UINT msg, std::function<LRESULT(WPARAM, LPARAM)> process)
	{
		mLookMutex.lock();
		mmMsgProcess.insert(std::make_pair(msg, process));
		mLookMutex.unlock();
	}

	void NativeWindow::UnRegisteMessageProcess(UINT msg, std::function<LRESULT(WPARAM, LPARAM)> fptr) {
		mLookMutex.lock();
		for (auto itr = mmMsgProcess.begin(); itr != mmMsgProcess.end(); itr++) {
			if (itr->first == msg) {
				string fn0 = itr->second.target_type().name();
				string fn1 = fptr.target_type().name();
				if (fn0 == fn1) {
					mmMsgProcess.erase(itr);
					break;
				}
			}
		}
		mLookMutex.unlock();
	}

	LRESULT NativeWindow::OnCreate(WPARAM wParam, LPARAM lParam) {
		//startup GDI+
		BOOL bRst = FALSE;
		return bRst;
	}

	LRESULT NativeWindow::OnSize(WPARAM wParam, LPARAM lParam) {
		BOOL bRst = FALSE;

		return bRst;
	}

	LRESULT NativeWindow::OnDestory(WPARAM wParam, LPARAM lParam)
	{
		return FALSE;
	}

	void NativeWindow::Close() {
		CloseWindow(mWnd);
	}

	void NativeWindow::Destory()
	{
	}

	NativeWindow::NativeWindow(HINSTANCE hInstance) :mInstance(hInstance), mTimer(0) {
	}
	CefRefPtr<NativeWindow> NativeWindow::Make(HINSTANCE hInstance) {
		if (!kbRegistr) {
			kbRegistr = true;
			RegisterClass(hInstance);
		}

		CefRefPtr<NativeWindow> wnd = new NativeWindow(hInstance);
		wnd->Init();
		return wnd;
	}
};