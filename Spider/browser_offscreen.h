#pragma once
#include <include/cef_base.h>
#include <include/cef_browser.h>
#include <include/cef_render_handler.h>
#include <vector>
namespace seraphim {
	class BrowserOffscreen : virtual public CefBaseRefCounted{
	public:
		bool  bWorking{ false };
		BrowserOffscreen(int user_id);
		BrowserOffscreen(CefRefPtr<CefBrowser> browser,int user_id);
		CefRefPtr<CefBrowser>  mBrowser{};
		std::vector<CefRefPtr<BrowserOffscreen>> mChildren;
		int mUserID{ -1 };
		int GetId() {
			if (mBrowser.get() == nullptr) {
				return 0;
			}
			return mBrowser->GetIdentifier();
		}

		CefRefPtr<BrowserOffscreen>  GetChildByUserID(int user_id);
		bool BindCefBrowserByUserID(CefRefPtr<CefBrowser> browser, int user_id);

		virtual ~BrowserOffscreen();

		IMPLEMENT_REFCOUNTING(BrowserOffscreen);
		DISALLOW_COPY_AND_ASSIGN(BrowserOffscreen);

	};
}