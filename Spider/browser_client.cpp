#include "browser_client.h"
#include "browser_app.h"
#include  "browser_login.h"
#include "common_log.h"
#include "common.h"
#include "common_tools.hpp"
#include  "file_store_facotr.h"
#include "cef_utility.h"
namespace seraphim {
	BrowserClient::BrowserClient()
	{
		mResourceHandelr = new ResponsetHandler();
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
	}

	void BrowserClient::OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward)
	{
		auto url = browser->GetMainFrame()->GetURL();
		auto szUrl = url.ToWString();
		WLOG(10, TAG, L"OnLoadingStateChange url", szUrl);
	}

	void BrowserClient::OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type)
	{
		auto url = browser->GetMainFrame()->GetURL();
		auto szUrl = url.ToWString();
		WLOG(10, TAG, L"OnLoadStart  url", szUrl, L"browser id =", browser->GetIdentifier(), L"|frame id = ", browser->GetMainFrame()->GetIdentifier());
	}

	void BrowserClient::OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode)
	{
		auto url = browser->GetMainFrame()->GetURL();
		auto szUrl = url.ToWString();
		auto msg = CefProcessMessage::Create(kCmdVisitDom);
		browser->GetMainFrame()->SendProcessMessage(CefProcessId::PID_RENDERER, msg);
		auto szJs = Tools::ReadFile(R"(C:\Users\seraph\source\Spider\init.js)");
		frame->ExecuteJavaScript(szJs.c_str(), url, 0);

		WLOG(10, TAG, L"OnLoadEnd  url", szUrl);
	}

	void BrowserClient::OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl)
	{
		auto url = browser->GetMainFrame()->GetURL();
		auto szUrl = url.ToWString();
		WLOG(10, TAG, L"OnLoadError  url", szUrl);
	}

	bool BrowserClient::OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access)
	{
		auto bid = browser->GetIdentifier();
		int parentID = 0;
		if (bid != 1)
			parentID = mTopBrowser->GetUserIDByCefID(bid);
		extra_info = CefDictionaryValue::Create();
		auto vUserID = CefValue::Create();
		int userId = kDataId++;
		vUserID->SetInt(userId);

		auto vParentID = CefValue::Create();
		vParentID->SetInt(parentID);
		extra_info->SetValue(kKeyUserID, vUserID);
		extra_info->SetValue(kKeyParentID, vParentID);
		auto b = mTopBrowser->CreateChildByID(parentID, userId);
		//Debug
		auto [path, name] = CefUtility::UrlToPath(target_url);
		auto matcher = new ResourceTypeMatcher(CefRequest::ResourceType::RT_IMAGE);
		auto factor = new FileStoreFactor(path.c_str(), "base", ".jpg");
		b->SetFilterFactor(factor);
		b->SetRequestMatcher(matcher);

		return false;
	}

	void BrowserClient::OnAfterCreated(CefRefPtr<CefBrowser> browser)
	{
	}

	struct QuitTask : CefTask {
		IMPLEMENT_REFCOUNTING(QuitTask);
		DISALLOW_COPY_AND_ASSIGN(QuitTask);
	public:
		CefRefPtr<BrowserOffscreen> browser;

		QuitTask(CefRefPtr<BrowserOffscreen> b) :browser(b) {
		}
		virtual void Execute() override
		{
			browser = nullptr;
			BrowserApp::Get()->Shutdown();
		}
	};

	//************************************
	// Method:    DoClose
	// FullName:  seraphim::BrowserClient::DoClose
	// Access:    virtual public
	// Returns:   bool   false ??????????????
	// Qualifier:
	// Parameter: CefRefPtr<CefBrowser> browser
	//************************************
	bool BrowserClient::DoClose(CefRefPtr<CefBrowser> browser)
	{
		bool rst = true;
		auto id = browser->GetIdentifier();
		do {
			if (id == mTopBrowser->GetId()) {
				CefRefPtr<QuitTask>  task = new QuitTask(mTopBrowser);
				CefPostDelayedTask(CefThreadId::TID_UI, task, 100);
				mTopBrowser = nullptr;
				rst = false;
				break;
			}
			auto user_id = mTopBrowser->GetUserIDByCefID(id);
			if (user_id <= 0)
				break;
			bool bRst = mTopBrowser->DeleteChildByUserID(user_id);
			assert(bRst);
		} while (false);

		return false;
	}

	bool BrowserClient::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
	{
		auto msg = message->GetName().ToWString();
		if (msg == kMessageBrowserCreated) {
			auto id = browser->GetIdentifier();
			auto user_id = message->GetArgumentList()->GetInt(kIndexUserID);
			auto parent_id = message->GetArgumentList()->GetInt(kIndexParentID);
			mTopBrowser->BindCefBrowserByUserID(browser, user_id);
		}
		return false;
	}

	void BrowserClient::GetWindowInfo(CefWindowInfo& info)
	{
		info.SetAsWindowless(NULL);
		return;
	}

	void BrowserClient::GetBrowsettting(CefBrowserSettings& settings)
	{
	}

	bool  BrowserClient::CreateChild(int parent_id, int user_id)
	{
		return  mTopBrowser->CreateChildByID(parent_id, user_id);
	}

	void BrowserClient::BindBrowser(CefRefPtr<CefBrowser> browser, int user_id)
	{
		if (user_id == 0) {
			assert(false);
		}
		else {
			mTopBrowser->BindCefBrowserByUserID(browser, user_id);
		}
	}

	CefRefPtr<CefResponseFilter> BrowserClient::GetResponseFilter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response)
	{
		CefRefPtr<CefResponseFilter> filter{ nullptr };
		do {
			auto cid = browser->GetIdentifier();
			if (cid == mTopBrowser->GetId()) break;
			auto mb = mTopBrowser->GetChildByCefID(cid);
			if (mb.get() == nullptr) break;
			return mb->GetResponseFilter(frame, request, response);
		} while (false);
		return filter;
	}
};