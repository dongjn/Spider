#pragma once
#include "dom_extractor_inteface.h"
#include <include/cef_dom.h>
namespace seraphim {
	class BaseVisitor : public CefDOMVisitor {
	private:
		CefRefPtr<IDomExtractor>  mExtractor{ nullptr };
	public:
		BaseVisitor() = default;
		BaseVisitor(CefRefPtr<IDomExtractor> extractor);
		virtual void Visit(CefRefPtr<CefDOMDocument> document) override;

		void ErgodicNode(CefRefPtr<CefDOMNode> node);

		~BaseVisitor();

		IMPLEMENT_REFCOUNTING(BaseVisitor);
		DISALLOW_COPY_AND_ASSIGN(BaseVisitor);
	};
}
