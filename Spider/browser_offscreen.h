#pragma once
#include <include/cef_base.h>
#include <include/cef_browser.h>
#include <include/cef_render_handler.h>
#include <include/cef_response_filter.h>
#include <include/cef_response.h>
#include <vector>
#include "native_window.h"
#include "resource_store_factor_i.h"
#include "request_matcher.h"
namespace seraphim {
	class BrowserOffscreen : virtual public CefBaseRefCounted {
		IMPLEMENT_REFCOUNTING(BrowserOffscreen);
		DISALLOW_COPY_AND_ASSIGN(BrowserOffscreen);
	private:
		CefRefPtr<NativeWindow> mNativeWnd{ nullptr };
		CefRefPtr<CefBrowser>  mBrowser{};
		CefRefPtr<RequestMatcherBase> mRequestMatcher{nullptr};
		CefRefPtr<IResourceStoreFactor>   mResourceStoreFactor{nullptr};
		std::map<int, CefRefPtr<BrowserOffscreen>> mmChildren;
		
		int mUserID{ -1 };
		int mCefID{ -1 };
		bool  bWorking{ false };
	public:

		BrowserOffscreen(int user_id);
		BrowserOffscreen(CefRefPtr<CefBrowser> browser, int user_id);
		BrowserOffscreen(CefString url);
		int GetId() {
			if (mBrowser.get() == nullptr) {
				return 0;
			}
			return mBrowser->GetIdentifier();
		}
		CefRefPtr<BrowserOffscreen>  GetChildByUserID(int user_id);
		CefRefPtr<BrowserOffscreen>  GetChildByCefID(int cef_id);
		bool BindCefBrowserByUserID(CefRefPtr<CefBrowser> browser, int user_id);
		CefRefPtr<BrowserOffscreen> CreateChildByID(int parent_id, int user_id);
		bool DeleteChildByUserID(int user_id);
		int  GetUserIDByCefID(int cef_if);
		void SetFilterFactor(CefRefPtr<IResourceStoreFactor>  facotr) {
			mResourceStoreFactor = facotr;
		}
		void SetRequestMatcher(CefRefPtr<RequestMatcherBase> mathcher) {
			mRequestMatcher = mathcher;
		}

		CefRefPtr<CefResponseFilter> GetResponseFilter(CefRefPtr<CefFrame> frme, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response);

		virtual ~BrowserOffscreen();
	};
}