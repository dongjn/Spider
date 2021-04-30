#include "browser_app.h"
#include "browser_client.h"
namespace seraphim{

	CefRefPtr<BrowserApp> BrowserApp::self_{nullptr};

	CefRefPtr<BrowserApp> BrowserApp::Make(HINSTANCE hInstance, bool isScreen, bool neetLogin, const string& url, const string& loginurl)
	{
		if (self_.get() == nullptr) {
			self_ = new BrowserApp(hInstance);
			self_ -> bIsScreenOff = isScreen;
			self_->bNeetLogin = neetLogin;
			self_->rootUrl.FromString(url.c_str());
			if (neetLogin)
				self_->loginUrl.FromString(loginurl.c_str());

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
		if(bNeetLogin)
			loginBrowser = new BrowserLogin(loginUrl);
		else {
			mClient->mTopBrowser = new BrowserOffscreen(rootUrl);
		}
	
	}

	
	void BrowserApp::CreateBrowser()
	{
		
	}


	void BrowserApp::Shutdown()
	{
		CefShutdown();
		self_ = nullptr;
	}

	BrowserApp::~BrowserApp()
	{
		
	}

};

