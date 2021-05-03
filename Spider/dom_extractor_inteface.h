#pragma once
#include <include/cef_dom.h>
#include <vector>
#include <map>
using  std::wstringstream;
using std::wstring;
namespace seraphim {
	using std::vector;
	using std::string;
	using std::wstring;
	class DomExtractorError;

	struct  DomInfo {
		CefRect   rect;
		CefString value;
		std::map<CefString, CefString> properties;
	};

	class IDomExtractor : public CefBaseRefCounted {
	public:
		IDomExtractor() = default;
		virtual void  Extraction(CefRefPtr<CefDOMNode> node, vector <DomInfo>& infos) throw(DomExtractorError) = 0;
		IMPLEMENT_REFCOUNTING(IDomExtractor);
		DISALLOW_COPY_AND_ASSIGN(IDomExtractor);
	};

	struct DomExtractorError {
		int   nodeDeep;
		const wstring msg;
		CefRefPtr<CefDOMNode>  node;
	};
	inline wstringstream& operator<<(wstringstream& os, const const DomExtractorError& error) {
		os << L"[DomExtractorError]<"<<error.nodeDeep<<L","<<error.msg<<L">";
		return os;
	}

};