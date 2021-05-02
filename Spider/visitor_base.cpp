#include "visitor_base.h"

#include "common.h"
#include "cef_utility.h"
#include "log.h"
#include <sstream>
namespace seraphim {



	

	void BaseVisitor::Visit(CefRefPtr<CefDOMDocument> document)
	{
		auto url =  document->GetHead()->GetName();
		//auto note  =document->GetDocument()->GetFirstChild();
		auto note = document->GetBody();
		auto last = document->GetDocument()->GetLastChild();
		ErgodicNode(note);

		
		auto  szUrl = url.ToWString();
		WLOG(10, TAG, L"url ", szUrl);

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
				
				WLOG(10, TAG, L"href = ", szHREF,L"rect",bound);
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


