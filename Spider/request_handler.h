#pragma once
#include <include/cef_request_handler.h>
#include <include/cef_resource_request_handler.h>
struct FilterStatus;
namespace seraphim {
	class ResponsetHandler : virtual public CefRequestHandler, CefResourceRequestHandler {
		IMPLEMENT_REFCOUNTING(ResponsetHandler);
		DISALLOW_COPY_AND_ASSIGN(ResponsetHandler);
	public:
		ResponsetHandler() = default;
		virtual CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_navigation, bool is_download, const CefString& request_initiator, bool& disable_default_handling) override;

		virtual CefRefPtr<CefResponseFilter> GetResourceResponseFilter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response) override;
	};
};
