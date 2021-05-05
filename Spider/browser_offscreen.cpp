#include "browser_offscreen.h"
#include "browser_app.h"
#include <algorithm>
#include "common.h"
#include "common_log.h"
#include "cef_log_utility.h"
namespace seraphim {
	BrowserOffscreen::BrowserOffscreen(CefRefPtr<CefBrowser> browser, int user_id) :mBrowser(browser), mUserID(user_id)
	{
		mCefID = browser->GetIdentifier();
	}

	BrowserOffscreen::BrowserOffscreen(int user_id) : mUserID(user_id)
	{
	}

	BrowserOffscreen::BrowserOffscreen(CefString url)
	{
		mUserID = 0;
		auto app = BrowserApp::Get();
		CefWindowInfo cwi;
		CefBrowserSettings  settings;
		if (app->IsScreenOff()) {
			RECT rect;
			(void)rect;
		}
		else {
			RECT rect;
			mNativeWnd = NativeWindow::Make(app->GetInstance());
			mNativeWnd->RegisteMessageProcess(WM_CLOSE, [&](WPARAM wParam, LPARAM lParam)->LRESULT {
				if (mBrowser.get()) {
					mBrowser->GetHost()->CloseBrowser(true);
				}
				return FALSE;
				});

			auto parent = mNativeWnd->GetHandle();
			GetClientRect(parent, &rect);
			cwi.SetAsChild(parent, rect);
		}
		auto ext = CefDictionaryValue::Create();
		auto value = CefValue::Create();
		value->SetInt(0);
		ext->SetValue(kKeyUserID, value);
		CefRefPtr<CefRequestContext> requestContext = CefRequestContext::GetGlobalContext();
		mBrowser = CefBrowserHost::CreateBrowserSync(cwi, app->GetScreenOffClient(), url, settings, ext, requestContext);
		mCefID = mBrowser->GetIdentifier();
	}

	CefRefPtr<BrowserOffscreen> BrowserOffscreen::GetChildByUserID(int user_id)
	{
		auto itr = mmChildren.find(user_id);
		if (itr != mmChildren.end()) {
			return itr->second;
		}
		CefRefPtr<BrowserOffscreen> rst{ nullptr };
		for (auto child : mmChildren) {
			rst = child.second->GetChildByUserID(user_id);
			if (rst.get()) break;
		}
		return rst;
	}

	CefRefPtr<BrowserOffscreen> BrowserOffscreen::GetChildByCefID(int cef_id)
	{
		CefRefPtr<BrowserOffscreen>  rst = nullptr;
		if (cef_id == mCefID) {
			return this;
		}
		for (auto& child : mmChildren) {
			rst = child.second->GetChildByCefID(cef_id);
			if (rst.get() != nullptr)
				break;
		}
		return rst;
	}

	bool BrowserOffscreen::BindCefBrowserByUserID(CefRefPtr<CefBrowser> browser, int user_id)
	{
		bool rst{ false };
		auto itr = mmChildren.find(user_id);
		if (itr != mmChildren.end()) {
			itr->second->mBrowser = browser;
			itr->second->mCefID = browser->GetIdentifier();
			return true;
		}
		for (auto& child : mmChildren) {
			rst = child.second->BindCefBrowserByUserID(browser, user_id);
			if (rst)break;
		}
		return rst;
	}

	CefRefPtr<BrowserOffscreen> BrowserOffscreen::CreateChildByID(int parent_id, int user_id)
	{
		CefRefPtr<BrowserOffscreen> rst{ nullptr };
		if (mUserID == parent_id) {
			CefRefPtr<BrowserOffscreen>  browser = new BrowserOffscreen(user_id);
			mmChildren.insert(std::make_pair(user_id, browser));
			return browser;
		}

		for (auto child : mmChildren) {
			rst = child.second->CreateChildByID(parent_id, user_id);
			if (rst.get() != nullptr)  break;
		}
		return rst;
	}

	bool BrowserOffscreen::DeleteChildByUserID(int user_id)
	{
		bool rst = false;
		auto itr = mmChildren.find(user_id);
		if (itr != mmChildren.end()) {
			mmChildren.erase(itr);
			return true;
		}

		for (auto& child : mmChildren) {
			rst = child.second->DeleteChildByUserID(user_id);
			if (rst) break;
		}
		return rst;
	}

	int BrowserOffscreen::GetUserIDByCefID(int cef_id)
	{
		int id = -1;
		if (cef_id == GetId()) {
			return mUserID;
		}
		for (auto child : mmChildren) {
			id = child.second->GetUserIDByCefID(cef_id);
			if (id >= 0) break;
		}
		return id;
	}

	CefRefPtr<CefResponseFilter> BrowserOffscreen::GetResponseFilter(CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response)
	{
		CefRefPtr<CefResponseFilter> filter{ nullptr };
		do {
			if (mRequestMatcher.get() == nullptr)
				break;

			if (!mRequestMatcher->Matching(mBrowser, frame, request, response))
				break;
			if (mResourceStoreFactor.get() == nullptr)
				break;
			filter = mResourceStoreFactor->MakeFilter();
		} while (false);
		return filter;
	}

	BrowserOffscreen::~BrowserOffscreen()
	{
		mmChildren.clear();
		if (mBrowser.get()) {
			mBrowser->GetHost()->CloseBrowser(true);
		}
		if (mNativeWnd.get()) {
			::CloseWindow(mNativeWnd->GetHandle());
		}
	}
}