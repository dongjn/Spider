#include "render_handler.h"
#include "log.h"
#include "common.h"
#include "visitor_base.h"
#include "dom_indices_extractor.h"
namespace seraphim {
	static const  string kInitJavaScript = "alert(\"bid = %d pid =%d\");";

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
			auto mainFrame = browser->GetMainFrame();
			if (mainFrame.get() == nullptr) {
				WLOG(10, TAG, L"MainFrame IS NULL!");
				return TRUE;
			}
			CefRefPtr<DomIndicesExtractor>  exteractor = new DomIndicesExtractor({ 1,5,0,1 }, {}, false);

			CefRefPtr<BaseVisitor>  visitor = new BaseVisitor(exteractor);
			browser->GetMainFrame()->VisitDOM(visitor);
			//CefRefPtr<DomIndicesExtractor>  exteractor = new DomIndicesExtractor({ 1,2,0,1,0,1,0,0 }, {}, false);
			//for (int i = 0; i < 5; i++) {
			//	CefRefPtr<DomIndicesExtractor>  exteractor = new DomIndicesExtractor({ 1,i}, {}, false);

			//	CefRefPtr<BaseVisitor>  visitor = new BaseVisitor(exteractor);
			//	WLOG(10, TAG, L"---------------------------", i, L"----------------------------");
			//	browser->GetMainFrame()->VisitDOM(visitor);
			//	WLOG(10, TAG, L"---------------------------", i, L"--------------------------------------------------------------------------------------END");

			//}
		}
		return TRUE;
	}

	void RenderProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
	{
		auto url = frame->GetURL();
		char js[1024] = { 0 };
		sprintf(js, kInitJavaScript.c_str(), browser->GetIdentifier(), GetCurrentProcessId());
		frame->ExecuteJavaScript(js, url, 0);
	}
};