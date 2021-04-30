#include "dom_visitor.h"
#include "log.h"
#include "common.h"
namespace seraphim {
	void DomVisitor::Visit(CefRefPtr<CefDOMDocument> document)
	{
		auto url =  document->GetHead()->GetName();
		auto note  =document->GetDocument()->GetFirstChild();
		auto last = document->GetDocument()->GetLastChild();
		ErgodicNode(note);
		auto  szUrl = url.ToWString();
		WLOG(10, TAG, L"url ", szUrl);

	}

	void DomVisitor::ErgodicNode(CefRefPtr<CefDOMNode> node)
	{
		while (node) {
			auto tagName = node->GetValue();
			WLOG(10, TAG, L"tagName = ", tagName.ToWString());
			if (node->HasChildren()) {
				auto child = node->GetFirstChild();
				node->GetType();
				auto last = node->GetLastChild();
				ErgodicNode(child);
			}
			node = node->GetNextSibling();
		}
	
	}

	DomVisitor::~DomVisitor()
	{
		WLOG(10, TAG, L"Destory DomVisitor");
	}

};


