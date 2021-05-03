#include "visitor_base.h"

#include "common.h"
#include "cef_log_utility.h"
#include "log.h"
#include <sstream>
namespace seraphim {
	BaseVisitor::BaseVisitor(CefRefPtr<IDomExtractor> extractor) :mExtractor(extractor)
	{
	}

	void BaseVisitor::Visit(CefRefPtr<CefDOMDocument> document)
	{
		if (mExtractor.get() != nullptr) {
			auto url = document->GetHead()->GetName();
			auto note = document->GetBody();
			vector<DomInfo>  vInfos;
			try {
				mExtractor->Extraction(document, vInfos);
			}
			catch (DomExtractorError& e) {
				CefRefPtr<CefDOMNode>  pn = e.node;
				WLOG(10, TAG, L"extractor DOM error e = ", e,pn,L">");
			}
			for (auto pinfo : vInfos) {
				WLOG(10, TAG, L"value = ", pinfo.value.ToWString());
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