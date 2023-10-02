#include "WinApp.h"

LRESULT CALLBACK WinApp::WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam) {
	//if (ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam)) {
	//	return true;
	//}
	//メッセージに応じてゲーム固有の処理を行う
	switch (msg)
	{
		//ウインドウが破棄された
	case WM_DESTROY:
		//OSに対して、アプリの終了を伝える
		PostQuitMessage(0);
		return 0;
	}

	//標準のメッセージ処理を行う
	return DefWindowProc(hwnd, msg, wparam, lparam);
}

void WinApp::Initialize() {

	//ウィンドウサイズ
	const int kCliantWidth = 1280; // 横幅
	const int kCliantHeight = 720; // 縦幅


	//ウインドウプロシージャ	
	wc.lpfnWndProc = (WNDPROC)WindowProc;
	//ウインドウクラス名（なんでもいい）
	wc.lpszClassName = L"メンバ変数";
	//インスタンスハンドル
	wc.hInstance = GetModuleHandle(nullptr);
	//カーソル
	wc.hCursor = LoadCursor(nullptr, IDC_ARROW);

	//ウインドウクラスを登録する
	RegisterClass(&wc);

	//ウィンドウサイズ
	wrc = { 0,0,kCliantWidth,kCliantHeight };
	//自動でサイズを補正する
	AdjustWindowRect(&wrc, WS_OVERLAPPEDWINDOW, false);

	//ウインドウの生成
	hwnd = CreateWindow(
		wc.lpszClassName,		//利用するクラス名
		L"メンバ変数",			//タイトルバーの文字
		WS_OVERLAPPEDWINDOW,	//よく見るウインドウスタイル
		CW_USEDEFAULT,			//表示X座標（Windowsに任せる）
		CW_USEDEFAULT,			//表示Y座標（Windowsに任せる）
		wrc.right - wrc.left,	//ウインドウ横幅
		wrc.bottom - wrc.top,	//ウインドウ縦幅
		nullptr,				//ウインドウハンドル
		nullptr,				//メニューハンドル
		wc.hInstance,			//インスタンスハンドル
		nullptr
	);

	/*directX12->DebugLayer();*/

	ShowWindow(hwnd, SW_SHOW);
}

void WinApp::Update() {

}