#pragma once
#include "dom_extractor_inteface.h"
namespace seraphim {
	class DomExtractor : public IDomExtractor {
		IMPLEMENT_REFCOUNTING(DomExtractor);
		DISALLOW_COPY_AND_ASSIGN(DomExtractor);
	public:
		DomExtractor() = default;

		virtual void Extraction(CefRefPtr<CefDOMNode> node, vector<DOMNode>& infos) throw(DOMError)override;

	};
};