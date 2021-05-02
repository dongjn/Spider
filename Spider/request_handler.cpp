#include "request_handler.h"
#include "browser_app.h"
#include "browser_client.h"
namespace seraphim {
	static bool one = true;
	CefRefPtr<CefResourceRequestHandler> ResponsetHandler::GetResourceRequestHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_navigation, bool is_download, const CefString& request_initiator, bool& disable_default_handling)
	{
		return this;
	}

	CefRefPtr<CefResponseFilter> ResponsetHandler::GetResourceResponseFilter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response)
	{
		auto app = BrowserApp::Get();
		auto client = app->GetScreenOffClient();

		return client->GetResponseFilter(browser, frame, request, response);
	}
};