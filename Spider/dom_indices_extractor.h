#pragma once
#include <include/cef_dom.h>
#include "dom_extractor_inteface.h"
namespace seraphim {
	using std::vector;
	class DomIndicesExtractor : public IDomExtractor {
		IMPLEMENT_REFCOUNTING(DomIndicesExtractor);
		DISALLOW_COPY_AND_ASSIGN(DomIndicesExtractor);
	private:
		bool mISArray{ false };
		vector<int>  mIndeices;
		vector<CefString> mPropertyKeys;
		int deep{ 0 };
		CefRefPtr<CefDOMNode> ErgodicNode(CefRefPtr<CefDOMNode> node, int deep) throw(DomExtractorError);
	public:
		DomIndicesExtractor() = default;
		DomIndicesExtractor(const vector<int>& indices, const vector<CefString>& properties, bool isArray);

		virtual void Extraction(CefRefPtr<CefDOMNode> node, vector <DomInfo>& infos) throw(DomExtractorError)override;
	};
};