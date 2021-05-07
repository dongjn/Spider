#include "render_process_handler.h"
#include "common_log.h"
#include "common.h"
#include "common_tools.hpp"
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
			//div[2] / div[3] / table / tbody[2] / tr[13] / td[2]
			// /html/body/div[2]/div[3]/table/tbody[2]/tr[13]/td[2]/h3
			//CefRefPtr<DomIndicesExtractor>  exteractor = new DomIndicesExtractor({ 1,5,0,1 }, {}, false);
			auto op = [](shared_ptr<DOMNode> node) {
				WLOG(10, TAG, L"match node  = ", node);
			};
			shared_ptr<DOMNodeNameMatcher>  matcher = std::make_shared<DOMNodeNameMatcher>("DIV",1);// = new DOMNodeNameMatcher("DIV", 1);

			matcher->Append(std::make_shared<DOMNodeNameMatcher>("DIV",2));
			matcher->Append(std::make_shared<DOMNodeNameMatcher>("TABLE", 0));
			matcher->Append(std::make_shared<DOMNodeNameMatcher>("TBODY", 1));
			matcher->Append(std::make_shared<DOMNodeNameMatcher>("TR"));
			matcher->Append(std::make_shared<DOMNodeNameMatcher>("TD", 1));
			matcher->Append(std::make_shared<DOMNodeNameMatcher>("H3",-1));
			matcher->Append(std::make_shared<DOMNodeNameMatcher>("A", -1, [](shared_ptr<DOMNode> mnode) {
				auto node = mnode->GetNode();
				if (node->HasElementAttribute("HREF")) {
					auto href = node->GetElementAttribute("HREF");
					auto wszHref = href.ToWString();
					for (const auto& c : mnode->GetChildren()) {
						c->SetOperator([wszHref](shared_ptr<DOMNode> cnode) {
							auto ccnode = cnode->GetNode();
							auto value = ccnode->GetValue();
							WLOG(10, TAG, L"node", ccnode, L"|url", wszHref);
							});
					}
				}	
				}));
			matcher->Append(std::make_shared<DOMNodeNameMatcher>("FONT", -1));

			CefRefPtr<BaseVisitor>  visitor = new BaseVisitor(matcher);
			browser->GetMainFrame()->VisitDOM(visitor);
		}
		return TRUE;
	}

	void RenderProcessHandler::OnContextCreated(CefRefPtr<CefBrowser> browser, CefRefPtr<CefFrame> frame, CefRefPtr<CefV8Context> context)
	{
		auto url = frame->GetURL();
		char js[1024] = { 0 };
		memset(js, 0, 1024);
		sprintf(js, "alert(%d);", GetCurrentProcessId());
		frame->ExecuteJavaScript(js, url, 0);





	}
};