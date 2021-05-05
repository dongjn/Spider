#pragma once
#include <include/cef_dom.h>
#include <vector>
#include <map>
#include "dom_error.h"
using  std::wstringstream;
using std::wstring;
namespace seraphim {
	using std::vector;
	using std::string;
	using std::wstring;

	struct  DomInfo {
		CefRect   rect;
		CefString value;
		std::map<CefString, CefString> properties;
	};

	class IDomExtractor : public CefBaseRefCounted {
	public:
		IDomExtractor() = default;
		virtual void  Extraction(CefRefPtr<CefDOMNode> node, vector <DomInfo>& infos) throw(DOMError) = 0;
		IMPLEMENT_REFCOUNTING(IDomExtractor);
		DISALLOW_COPY_AND_ASSIGN(IDomExtractor);
	};



};