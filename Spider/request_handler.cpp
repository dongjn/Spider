#include "request_handler.h"

namespace seraphim {
	static bool one = true;
	CefRefPtr<CefResourceRequestHandler> RequestHandler::GetResourceRequestHandler(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, bool is_navigation, bool is_download, const CefString& request_initiator, bool& disable_default_handling)
	{
		return this;
	}

	CefRefPtr<CefResponseFilter> RequestHandler::GetResourceResponseFilter(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefRequest> request, CefRefPtr<CefResponse> response)
	{
		auto url = request->GetURL();
		CefURLParts  parts;
		auto ident = frame->GetIdentifier();
		return nullptr;
	}




	bool RequestHandler::_Filter::InitFilter()
	{
		return true;
	}

	CefResponseFilter::FilterStatus RequestHandler::_Filter::Filter(void* data_in, size_t data_in_size, size_t& data_in_read, void* data_out, size_t data_out_size, size_t& data_out_written)
	{
		return CefResponseFilter::FilterStatus::RESPONSE_FILTER_DONE;
	}

};
