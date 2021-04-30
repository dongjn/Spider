#include "render_handler.h"
#include "log.h"
#include "common.h"
#include "dom_visitor.h"
namespace seraphim {


	void seraphim::RenderProcessHandler::OnBrowserCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefDictionaryValue> extra_info)
	{
		int userID = -1;
		do {
			auto frame = browser->GetMainFrame();
			auto vUserID = extra_info->GetValue(kKeyUserID);
			if (vUserID.get() == nullptr)
				break;
			auto vParentID = extra_info->GetValue(kKeyParentID);
			if (vParentID.get() == nullptr)
				break;
			auto msg = CefProcessMessage::Create(kMessageBrowserCreated);
			msg->GetArgumentList()->SetValue(kIndexUserID, vUserID);
			msg->GetArgumentList()->SetValue(kIndexParentID, vParentID);
			browser->GetMainFrame()->SendProcessMessage(CefProcessId::PID_BROWSER, msg);

		} while (0);
	}


	void seraphim::RenderProcessHandler::OnBrowserDestroyed(CefRefPtr<CefBrowser> browser)
	{
		WLOG(10, TAG, L"OnBrowserDestroyed");
	}

	
	bool RenderProcessHandler::OnProcessMessageReceived(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefProcessId source_process, CefRefPtr<CefProcessMessage> message)
	{

		auto cmd = message->GetName().ToWString();
		if (cmd == kCmdVisitDom) {
			browser->GetMainFrame()->VisitDOM(new DomVisitor);

		}
		return TRUE;
	}

};
