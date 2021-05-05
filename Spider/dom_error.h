#pragma once
#include <include/cef_dom.h>
#include <string>
#include <sstream>
namespace seraphim {
	using std::wstring;
	using std::wstringstream;
	struct DOMError {
		int   nodeDeep;
		const wstring msg;
		CefRefPtr<CefDOMNode>  node;
	};

	inline wstringstream& operator<<(wstringstream& os, const const DOMError& error) {
		os << L"[DomExtractorError]<" << error.nodeDeep << L"," << error.msg << L">";
		return os;
	}

}