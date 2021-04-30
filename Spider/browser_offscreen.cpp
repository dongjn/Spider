#include "browser_offscreen.h"
#include "browser_app.h"
#include <algorithm>
namespace seraphim {

	BrowserOffscreen::BrowserOffscreen(CefRefPtr<CefBrowser> browser,int user_id):mBrowser(browser),mUserID(user_id)
	{

	}

	BrowserOffscreen::BrowserOffscreen(int user_id):mUserID(user_id)
	{

	}

	CefRefPtr<BrowserOffscreen> BrowserOffscreen::GetChildByUserID(int user_id)
	{
		CefRefPtr<BrowserOffscreen> rst;
		for (auto& child : mChildren) {
			if (user_id == child->mUserID) {
				rst = child;
				break;
			}
			rst = child->GetChildByUserID(user_id);
			if (rst.get() != nullptr)
				break;
		}
		return rst;
	}

	bool BrowserOffscreen::BindCefBrowserByUserID(CefRefPtr<CefBrowser> browser, int user_id)
	{
		bool rst{ false };
		for (auto& child : mChildren) {
			if (user_id == child->mUserID) {
				child->mBrowser = browser;
				rst = true;
				break;
			}
			rst = child->BindCefBrowserByUserID(browser, user_id);
			if (rst)
				break;
		}
		return rst;
	}

	BrowserOffscreen::~BrowserOffscreen()
	{
		mChildren.empty();
		if (mBrowser.get()) {
			mBrowser->GetHost()->CloseBrowser(true);
		}
	}

}


