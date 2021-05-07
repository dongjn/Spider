#include "visitor_base.h"

#include "common.h"
#include "cef_log_utility.h"
#include "common_log.h"
#include <sstream>
#include "dom_node.h"
namespace seraphim {
	void BaseVisitor::Visit(CefRefPtr<CefDOMDocument> document)
	{
		
		if (mDOMNodeMatcher) {
			auto url = document->GetHead()->GetName();
			auto body = document->GetBody();
			shared_ptr<DOMNode> node = std::make_shared<DOMNode>(body);// = new DOMNode(document->GetBody());
			try {
				vector<shared_ptr<DOMNode>>  vNode{ node };
				mDOMNodeMatcher->Match(vNode);
				for (auto& node : vNode) {
					node->Process();
				}
			}
			catch (DOMError& e) {
				CefRefPtr<CefDOMNode>  pn = e.node;
				WLOG(10, TAG, L"extractor DOM error e = ", e, pn, L">");
			}
		}
	}

	void BaseVisitor::ErgodicNode(CefRefPtr<CefDOMNode> node)
	{
		while (node) {
			auto tagName = node->GetName();
			auto notType = node->GetType();
			if (notType == DOM_NODE_TYPE_ELEMENT && node->HasElementAttribute(L"href")) {
				CefRect bound = node->GetElementBounds();
				auto href = node->GetElementAttribute(L"href");
				wstring szHREF = href.ToWString();

				WLOG(10, TAG, L"href = ", szHREF, L"rect", bound);
			}
			auto szTagname = tagName.ToWString();
			if (node->HasChildren()) {
				auto child = node->GetFirstChild();
				node->GetType();
				auto last = node->GetLastChild();
				ErgodicNode(child);
			}
			node = node->GetNextSibling();
		}
	}

	BaseVisitor::~BaseVisitor()
	{
		WLOG(10, TAG, L"Destory DomVisitor");
	}
};