#pragma once
#undef min
#undef max
#include <array>
#include <headcode/url/url.hpp>
#include <include/cef_stream.h>
#include <include/cef_dom.h>
//#include <include/cef_do>
using std::string;
using std::pair;
//using std::array;
namespace seraphim {
	struct CefUtility {
		static pair<string, string> UrlToPath(const string& szUrl) {
			string szPath;
			string szName;
			std::string_view view(szUrl);
			headcode::url::URL u(szUrl);
			do {
				if (u.GetError() != headcode::url::ParseError::kNoError)
					break;
				auto vSegments = u.GetSegments();
				auto cSegment = vSegments.size();
				szName = vSegments[cSegment - 1];
				for (int i = 0; i < cSegment; i++) {
					szPath += vSegments[i];
					szPath.append("/");
				}
			} while (0);
			return std::make_pair(szPath, szName);
		}
	};
}
