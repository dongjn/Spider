#pragma once
#include <Windows.h>
#include <include/cef_app.h>
#include <include/cef_browser_process_handler.h>
//#include <include/cef_han>
#include <map>
#include "browser_client.h"
#include "native_window.h"
#include "browser_login.h"
namespace seraphim{
	class BrowserApp :  virtual public CefApp  , virtual public CefBrowserProcessHandler
	{


	private:
		static CefRefPtr<BrowserApp>  self_;
	public:
		static CefRefPtr<BrowserApp>  Get() {
			assert(self_.get() != nullptr);
			return self_;
		}
		static CefRefPtr<BrowserApp>  Make(HINSTANCE hInstance);
	private:
		HINSTANCE  mInstance;
		BrowserApp(HINSTANCE  hInstance);
		CefRefPtr<BrowserLogin> loginBrowser{nullptr};
		CefRefPtr<BrowserClient>  mClient{nullptr};
	public:

		virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override;

		virtual void OnContextInitialized() override;

	public:
		CefRefPtr<BrowserClient>  GetScreenOffClient() {
			return mClient;
		}
		
		HINSTANCE  GetInstance() {
			return mInstance;
		}
		void CreateBrowser();
		void Shutdown();
	private:
		IMPLEMENT_REFCOUNTING(BrowserApp);
		DISALLOW_COPY_AND_ASSIGN(BrowserApp);

	};



};
