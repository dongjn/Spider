#pragma once
#include <include/cef_dom.h>
namespace seraphim {
	class IMatcher 
	{
	
	public:
		virtual bool match(CefRefPtr<CefDOMNode> node) = 0;
	};

};

