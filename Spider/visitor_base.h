#pragma once
#include <include/cef_dom.h>
namespace seraphim {
	class BaseVisitor : public CefDOMVisitor {
	public:
		BaseVisitor() = default;
		virtual void Visit(CefRefPtr<CefDOMDocument> document) override;

		void ErgodicNode(CefRefPtr<CefDOMNode> node);

		~BaseVisitor();

		IMPLEMENT_REFCOUNTING(BaseVisitor);
		DISALLOW_COPY_AND_ASSIGN(BaseVisitor);
	};
}
