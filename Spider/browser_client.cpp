#include "browser_client.h"
#include "browser_app.h"
#include  "browser_login.h"
#include "log.h"
#include "common.h"
namespace seraphim {

	CefRefPtr<CefRenderHandler> BrowserClient::GetRenderHandler()
	{
		return this;
	}

	void BrowserClient::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect)
	{
		rect.x = 0;
		rect.y = 0;
		rect.width = 800;
		rect.height = 800;
	}

	void BrowserClient::OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height)
	{
		//throw std::logic_error("The method or operation is not implemented.");
	}





	CefRefPtr<CefLoadHandler> BrowserClient::GetLoadHandler()
	{
		return this;
	}


	void BrowserClient::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
	{
		auto url = browser->GetMainFrame()->GetURL();
		auto szUrl = url.ToWString();
		WLOG(10, TAG, L"OnLoadingStateChange url",szUrl);
	}

	void BrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type)
	{
		auto url = browser->GetMainFrame()->GetURL();
		auto szUrl = url.ToWString();
		WLOG(10, TAG, L"OnLoadStart  url", szUrl,L"browser id =",browser->GetIdentifier(),L"|frame id = ",browser->GetMainFrame()->GetIdentifier());

	}

	void BrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
	{
		auto url = browser->GetMainFrame()->GetURL();
		auto szUrl = url.ToWString();
		auto msg = CefProcessMessage::Create(VISIT_DOM_CMD);
		browser->GetMainFrame()->SendProcessMessage(CefProcessId::PID_RENDERER, msg);
		WLOG(10, TAG, L"OnLoadEnd  url", szUrl);

	}

	void BrowserClient::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
	{
		auto url = browser->GetMainFrame()->GetURL();
		auto szUrl = url.ToWString();
		WLOG(10, TAG, L"OnLoadError  url", szUrl);

	}

	CefRefPtr<CefLifeSpanHandler> BrowserClient::GetLifeSpanHandler()
	{

		return this;
		//throw std::logic_error("The method or operation is not implemented.");
	}

	bool BrowserClient::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access)
	{
		return true;
	}

	void BrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
	{
		//CefString  url(L"http://www.baidu.com");
		//browser->GetMainFrame()->LoadURL(url);
		//throw std::logic_error("The method or operation is not implemented.");
	}

	bool BrowserClient::DoClose(CefRefPtr<CefBrowser> browser)
	{
		return false;
	}

	void BrowserClient::OnBeforeClose(CefRefPtr<CefBrowser> browser)
	{
		
	}

	void BrowserClient::GetWindowInfo(CefWindowInfo& info)
	{
		info.SetAsWindowless(NULL);
		return;
	}

	void BrowserClient::GetBrowsettting(CefBrowserSettings& settings)
	{

	}

	void BrowserClient::CreateOffscennBrowser(const CefString url)
	{
		CefWindowInfo cwi;
		cwi.SetAsWindowless(NULL);
		CefString home(L"http://t66y.com/thread0806.php?fid=7");
		CefBrowserSettings  settings;
		CefRefPtr<CefRequestContext> requestContext = CefRequestContext::GetGlobalContext();
		auto cbrowser = CefBrowserHost::CreateBrowserSync(cwi, this, home, settings, nullptr, requestContext);
		auto browser = new BrowserOffscreen(cbrowser,kTopBrowserUserID++);
		auto id = browser->GetId();
		mOffscennBrowser[id] = browser;
	}

	void BrowserClient::CreateBaseBrowser()
	{
		auto browser = new BrowserLogin;
		auto id = browser->GetId();
		mBaseBrowser[id] = browser;
	}

};


