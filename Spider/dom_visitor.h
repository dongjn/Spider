#pragma once
#include <include/cef_dom.h>
namespace seraphim {
	class DomVisitor : public CefDOMVisitor {
	public:
		DomVisitor() = default;
		virtual void Visit(CefRefPtr<CefDOMDocument> document) override;


		void ErgodicNode(CefRefPtr<CefDOMNode> node);

		~DomVisitor();

		IMPLEMENT_REFCOUNTING(DomVisitor);
		DISALLOW_COPY_AND_ASSIGN(DomVisitor);

	};

}
