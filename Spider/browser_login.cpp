#include "browser_login.h"
#include "browser_app.h"
#include "common.h"
#include "log.h"
#include "cef_utility.h"
namespace seraphim {



	static int  kId{ 100 };
	CefRefPtr<CefLoadHandler> BrowserLogin::GetLoadHandler()
	{
		return this;
	}

	void BrowserLogin::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
	{
		CefString url =browser->GetMainFrame()->GetURL();
		//WLOG(10, TAG, L"OnLoadingStateChange  browser ",(void*)browser,L"|",url.ToWString());
	}

	void BrowserLogin::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type)
	{
		CefString url = browser->GetMainFrame()->GetURL();
		WLOG(10, TAG, L"OnLoadStart  browser ", (void*)browser,L"|id=",browser->GetIdentifier() ,L"|url=", url.ToWString());
	}

	void BrowserLogin::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
	{
		CefString url = browser->GetMainFrame()->GetURL();
		//WLOG(10, TAG, L"OnLoadEnd", url.ToWString());
	}

	void BrowserLogin::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
	{
		CefString url = browser->GetMainFrame()->GetURL();
		//WLOG(10, TAG, L"OnLoadError", url.ToWString());
	}

	CefRefPtr<CefLifeSpanHandler> BrowserLogin::GetLifeSpanHandler()
	{
		return this;
	}

	bool BrowserLogin::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access)
	{
		WLOG(10, TAG, L"OnBeforePopup");
		auto user_id= CefValue::Create();
		extra_info = CefDictionaryValue::Create();
		user_id->SetInt(kId++);
		extra_info->SetValue(kUserIdKey, user_id);
		return false;
	}

	void BrowserLogin::OnAfterCreated(CefRefPtr<CefBrowser> browser)
	{
		

		WLOG(10, TAG, L"OnAfterCreated");
		return ;
	}

	bool BrowserLogin::DoClose(CefRefPtr<CefBrowser> browser)
	{
		WLOG(10, TAG, L"DoClose");
		return false;
	}

	void BrowserLogin::OnBeforeClose(CefRefPtr<CefBrowser> browser)
	{
	}

	BrowserLogin::BrowserLogin()
	{
	
		auto app = BrowserApp::Get();

		mWindow = NativeWindow::Make(app->GetInstance());

		mWindow->RegisteMessageProcess(WM_CLOSE, [&](WPARAM wParam, LPARAM lParam) ->LRESULT {
			BrowserApp::Get()->Shutdown();
			return FALSE;
			});
		mWindow->RegisteMessageProcess(WM_SIZE, [&](WPARAM wParam, LPARAM lParam) ->LRESULT {
			auto width = LOWORD(lParam);
			auto height = LOWORD(lParam);
			auto h = mBrowser->GetHost()->GetWindowHandle();
			MoveWindow(h, 0, 0, width, height,TRUE);
			return FALSE;
			});
		CefWindowInfo cwi;
		RECT rect;
		auto parent = mWindow->GetHandle();
		GetClientRect(parent, &rect);
		cwi.SetAsChild(parent, rect);
		CefString home(L"http://t66y.com/thread0806.php?fid=7");
		CefBrowserSettings  settings;
		CefRefPtr<CefRequestContext> requestContext = CefRequestContext::GetGlobalContext();
		mBrowser  = CefBrowserHost::CreateBrowserSync(cwi, this, home, settings, nullptr, requestContext);
	}

}


