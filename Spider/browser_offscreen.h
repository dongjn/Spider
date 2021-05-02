#pragma once
#include <include/cef_base.h>
#include <include/cef_browser.h>
#include <include/cef_render_handler.h>
#include <vector>
#include "native_window.h"
namespace seraphim {
	class BrowserOffscreen : virtual public CefBaseRefCounted {
	private:

		CefRefPtr<NativeWindow> mNativeWnd{ nullptr };
		CefRefPtr<CefBrowser>  mBrowser{};
		std::map<int, CefRefPtr<BrowserOffscreen>> mmChildren;
		int mUserID{ -1 };
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
		bool BindCefBrowserByUserID(CefRefPtr<CefBrowser> browser, int user_id);
		bool CreateChildByID(int parent_id, int user_id);
		bool DeleteChildByUserID(int user_id);
		int  GetUserIDByCefID(int cef_if);
		virtual ~BrowserOffscreen();

		IMPLEMENT_REFCOUNTING(BrowserOffscreen);
		DISALLOW_COPY_AND_ASSIGN(BrowserOffscreen);

	};
}