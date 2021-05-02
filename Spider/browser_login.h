#pragma once
#include "common.h"
#include <include/cef_client.h>
#include "native_window.h"
namespace seraphim {
	class BrowserLogin : virtual public  CefClient, virtual public CefLoadHandler, virtual public CefLifeSpanHandler {
	public:

		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;

		virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) override;

		virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type) override;

		virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;

		virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;

		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;

		virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access) override;

		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;

		virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;

		virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) override;

	private:
		CefRefPtr<NativeWindow> mWindow;
		CefRefPtr<CefBrowser>  mBrowser;
	public:

		BrowserLogin(CefString url);
		int GetId() {
			if (mBrowser.get() == nullptr) {
				return 0;
			}
			return mBrowser->GetIdentifier();
		}
	private:
		IMPLEMENT_REFCOUNTING(BrowserLogin);
		DISALLOW_COPY_AND_ASSIGN(BrowserLogin);
	};
}