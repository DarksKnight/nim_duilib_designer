// basic.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "main.h"
#include "form/EditorForm.h"
#include "extern_ctrl/ExternCtrlManager.h"
#include <ShlObj_core.h>

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// 创建主线程
	MainThread thread;

	// 执行主线程循环
	thread.RunOnCurrentThreadWithLoop(nbase::MessageLoop::kUIMessageLoop);

	return 0;
}

void MainThread::Init()
{
	nbase::ThreadManager::RegisterThread(kThreadUI);
	nbase::ThreadManager::RegisterThread(kThreadGlobalMisc);
	nbase::ThreadManager::RegisterThread(kThreadGlobalXmlDiff);

	// 获取资源路径，初始化全局参数
	std::wstring theme_dir = nbase::win32::GetCurrentModuleDirectory();

	ui::GlobalManager::Startup(theme_dir + L"resources\\", ExternCtrlManager::CreateExternCtrl, false);

	ui::GlobalManager::EnableAutomation();

	TCHAR path[MAX_PATH] = { 0 };
	BOOL result = SHGetSpecialFolderPath(NULL, path, CSIDL_APPDATA, false);
	if (!result) {
		return;
	}
	GlobalData::APPDATA_ROMAING = path;
	GlobalData::APPDATA_ROMAING += L"\\NimDesigner\\";
	nbase::CreateDirectory(GlobalData::APPDATA_ROMAING);

	result = SHGetSpecialFolderPath(NULL, path, CSIDL_LOCAL_APPDATA, false);
	GlobalData::APPDATA_LOCAL = path;
	GlobalData::APPDATA_LOCAL += L"\\NimDesigner\\";
	nbase::CreateDirectory(GlobalData::APPDATA_LOCAL);

	// 创建一个默认带有阴影的居中窗口
	EditorForm* window = new EditorForm();
	window->Create(NULL, EditorForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowWindow();
}

void MainThread::Cleanup()
{
	ui::GlobalManager::Shutdown();
	SetThreadWasQuitProperly(true);
	nbase::ThreadManager::UnregisterThread();
}
