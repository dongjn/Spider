#include "dom_visitor.h"
#include "log.h"
#include "common.h"
#include "cef_utility.h"
#include <sstream>
namespace seraphim {

	using std::wstring;
	using std::wstringstream;


	

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
			auto tagName = node->GetName();
			auto notType = node->GetType();
			if (node->HasElementAttribute(L"href")) {
				auto href = node->GetElementAttribute(L"href");
				wstring szHREF = href.ToWString();
				WLOG(10, TAG, L"href = ", szHREF);
			}
			auto szTagname = tagName.ToWString();
			//if (L"A" == szTagname) {
			//	auto value = node->GetValue();
			//	wstring szValue;
			//	if (href.empty()) {
			//		szValue = L"!!!!!EMPTY!!!!";
			//	}
			//	else {
			//		szValue = href.ToWString();
			//	}
			//	WLOG(10, TAG, L"tagName = ", tagName.ToWString(),L"|NotType",(DomNoteType)notType,L"|href=",szValue);

			//}
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


