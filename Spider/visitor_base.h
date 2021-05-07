#pragma once
#include "dom_extractor_inteface.h"
#include <include/cef_dom.h>
#include "dom_matcher.h"
namespace seraphim {
	class BaseVisitor : public CefDOMVisitor {
	private:
		//CefRefPtr<IDomExtractor>  mExtractor{ nullptr };
		shared_ptr<DOMNodeMatcher>  mDOMNodeMatcher{nullptr};
	public:
		BaseVisitor() = default;
		//BaseVisitor(CefRefPtr<IDomExtractor> extractor);
		BaseVisitor(shared_ptr<DOMNodeMatcher> matcher) :mDOMNodeMatcher(matcher) {};
		virtual void Visit(CefRefPtr<CefDOMDocument> document) override;
		
		void ErgodicNode(CefRefPtr<CefDOMNode> node);

		~BaseVisitor();

		IMPLEMENT_REFCOUNTING(BaseVisitor);
		DISALLOW_COPY_AND_ASSIGN(BaseVisitor);
	};
}
