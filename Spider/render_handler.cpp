#include "render_handler.h"
#include "log.h"
#include "common.h"
#include "dom_visitor.h"
namespace seraphim {


	void seraphim::RenderProcessHandler::OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info)
	{
		int userID = -1;
		auto frame = browser->GetMainFrame();
		auto value = extra_info->GetValue(kUserIdKey);
		if (value.get() != nullptr)
			userID = value->GetInt();
		WLOG(10, TAG, L"OnBrowserCreated userID = ",userID);
		if (frame.get()) {
			auto url = frame->GetURL();
			auto szUrl = url.ToWString();
			frame->VisitDOM(new DomVisitor());
			WLOG(10, TAG, L"BrowserCreate url = ", szUrl);
		}
	}


	void seraphim::RenderProcessHandler::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
	{
		WLOG(10, TAG, L"OnBrowserDestroyed");
	}

	
	bool RenderProcessHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
	{

		auto cmd = message->GetName().ToWString();
		if (cmd == VISIT_DOM_CMD) {
			browser->GetMainFrame()->VisitDOM(new DomVisitor);

		}
		return TRUE;
	}

};
