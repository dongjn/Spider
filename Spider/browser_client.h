#pragma once
#include <include/cef_client.h>
#include <include/cef_render_handler.h>
#include "browser_offscreen.h"
#include "browser_login.h"
namespace seraphim {
	class BrowserApp;
	class BrowserClient : public  virtual CefClient,CefRenderHandler,CefLifeSpanHandler,CefLoadHandler{
		IMPLEMENT_REFCOUNTING(BrowserClient);
		DISALLOW_COPY_AND_ASSIGN(BrowserClient);
	private:
		CefRefPtr<BrowserOffscreen>  mTopBrowser;
	public:
		friend class BrowserApp;
		BrowserClient() = default;
		virtual CefRefPtr<CefRenderHandler> GetRenderHandler() override;
		
		virtual void GetViewRect(CefRefPtr<CefBrowser> browser, CefRect& rect) override;


		virtual void OnPaint(CefRefPtr<CefBrowser> browser, PaintElementType type, const RectList& dirtyRects, const void* buffer, int width, int height) override;


		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) override;


		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() override;


		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() override;


	


		virtual void OnLoadingStateChange(CefRefPtr<CefBrowser> browser, bool isLoading, bool canGoBack, bool canGoForward) override;


		virtual void OnLoadStart(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, TransitionType transition_type) override;


		virtual void OnLoadEnd(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, int httpStatusCode) override;


		virtual void OnLoadError(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, ErrorCode errorCode, const CefString& errorText, const CefString& failedUrl) override;


		virtual bool OnBeforePopup(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, const CefString& target_url, const CefString& target_frame_name, WindowOpenDisposition target_disposition, bool user_gesture, const CefPopupFeatures& popupFeatures, CefWindowInfo& windowInfo, CefRefPtr<CefClient>& client, CefBrowserSettings& settings, CefRefPtr<CefDictionaryValue>& extra_info, bool* no_javascript_access) override;


		virtual bool DoClose(CefRefPtr<CefBrowser> browser) override;


		virtual bool OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message) override;

	public:

		
		void GetWindowInfo(CefWindowInfo& info);
		void GetBrowsettting(CefBrowserSettings& settings);

		bool CreateChild(int parent_id,int user_id);

		void BindBrowser(CefRefPtr<CefBrowser> browser, int user_id);

		//bool CreateChild(const CefString url);

	};
};