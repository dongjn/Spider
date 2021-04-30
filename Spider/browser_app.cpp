#include "browser_app.h"
#include "browser_client.h"
namespace seraphim{

	CefRefPtr<BrowserApp> BrowserApp::self_{nullptr};

	CefRefPtr<BrowserApp> BrowserApp::Make(HINSTANCE hInstance)
	{
		if (self_.get() == nullptr) {
			self_ = new BrowserApp(hInstance);
		}
		return self_;
	}

	BrowserApp::BrowserApp(HINSTANCE hInstance):mInstance(hInstance)
	{
		mClient = new BrowserClient;
	}

	CefRefPtr<CefBrowserProcessHandler> BrowserApp::GetBrowserProcessHandler()
	{
		return this;
	}


	void BrowserApp::OnContextInitialized()
	{
		loginBrowser = new BrowserLogin;
	}

	
	void BrowserApp::CreateBrowser()
	{
		
	}


	void BrowserApp::Shutdown()
	{

		mClient->mBaseBrowser.empty();
		mClient->mOffscennBrowser.empty();
		CefShutdown();

	}

};

