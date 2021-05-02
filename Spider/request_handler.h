#pragma once
#include <include/cef_request_handler.h>
#include <include/cef_resource_request_handler.h>
struct FilterStatus;
namespace seraphim {

	class RequestHandler : virtual public CefRequestHandler, CefResourceRequestHandler {
	private:
		class _Filter : public virtual CefResponseFilter {

			IMPLEMENT_REFCOUNTING(_Filter);
			DISALLOW_COPY_AND_ASSIGN(_Filter);
		public:
			virtual bool InitFilter() override;

			virtual FilterStatus Filter(void* data_in, size_t data_in_size, size_t& data_in_read, void* data_out, size_t data_out_size, size_t& data_out_written) override;

		};



		IMPLEMENT_REFCOUNTING(RequestHandler);
		DISALLOW_COPY_AND_ASSIGN(RequestHandler);
	public:
		RequestHandler() = default;
		virtual CefRefPtr<CefResourceRequestHandler> GetResourceRequestHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_navigation, bool is_download, const CefString& request_initiator, bool& disable_default_handling) override;


		virtual CefRefPtr<CefResponseFilter> GetResourceResponseFilter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response) override;


	};
};
