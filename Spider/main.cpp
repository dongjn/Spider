// Spider.cpp : 定义应用程序的入口点。
//
#pragma warning(disable : 4819)
#include "framework.h"
#include "main.h"
#include "common.h"
#include<include/cef_base.h>
#include <include/cef_app.h>
#include "browser_app.h"
#include "render_handler.h"

#undef max
#undef min

#include<sstream>
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/array.hpp>

#include <headcode/url/url.hpp>

using std::wstringstream;

void test_monog() {
	using bsoncxx::builder::stream::close_array;
	using bsoncxx::builder::stream::close_document;
	using bsoncxx::builder::stream::document;
	using bsoncxx::builder::stream::finalize;
	using bsoncxx::builder::stream::open_array;
	using bsoncxx::builder::stream::open_document;
	mongocxx::instance instance{}; // This should be done only once.
	mongocxx::uri uri("mongodb://localhost:27017");
	mongocxx::client client(uri);
	mongocxx::database db = client["mydb"];
}

using namespace seraphim;

const char kProcessType[] = "type";
const char kRendererProcess[] = "renderer";

inline CefRefPtr<CefApp> ChooseAppType(CefRefPtr<CefCommandLine> commandLine, HINSTANCE  hInstance) {
	CefRefPtr<CefApp> rst{ nullptr };
	do {
		if (!commandLine->HasSwitch(kProcessType)) {
			rst = BrowserApp::Make(hInstance, false, false, "http://t66y.com/thread0806.php?fid=16", "");
			break;
		}
		const string& szAppType = commandLine->GetSwitchValue(kProcessType);
		if (szAppType == kRendererProcess) {
			wstringstream  wss;
			wss << GetCurrentProcessId();
			auto msg = wss.str();
			MessageBox(NULL, NULL, msg.c_str(), MB_OK);
			rst = new RenderProcessHandler;
			break;
		}
		//rst = new OtherApp;
	} while (false);
	return rst;
}


void test_url() {
	headcode::url::URL  url("https://www.google.com/search?q=%E7%9A%84&oq=%E7%9A%84&aqs=chrome..69i57j69i61l3j69i65l2.1782j0j4&sourceid=chrome&ie=UTF-8");
	auto host = url.GetHost();
	auto path = url.GetPath();
	auto port= url.GetPort();
	auto a = url.GetScheme();
	auto b = url.GetAuthority();
	auto c = url.GetSegments();
	auto d = url.GetQuery();
	auto e = url.GetUserInfo();

}
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	test_url();
	CefEnableHighDPISupport();
	void* sandbox_info = nullptr;
	CefMainArgs main_args(hInstance);
	CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
	command_line->InitFromString(::GetCommandLineW());
	auto app = ChooseAppType(command_line, hInstance);
	int exit_code = CefExecuteProcess(main_args, app, sandbox_info);
	if (exit_code >= 0)
	{
	}

	CefSettings settings{};
	settings.multi_threaded_message_loop = false;
	settings.windowless_rendering_enabled = true;
	if (command_line->HasSwitch("enable-chrome-runtime")) {
		settings.chrome_runtime = true;
	}
	command_line->AppendSwitchWithValue("--force-device-scale-factor", "1");
	command_line->AppendSwitchWithValue("--device-scale-factor", "1.0");
	auto bRst = CefInitialize(main_args, settings, app, sandbox_info);
	CefRunMessageLoop();
	Sleep(1000);
	return 0;
}