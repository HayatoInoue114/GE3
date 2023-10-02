#pragma once
#include <Windows.h>
#include <cstdint>

//WindowsAPI
class WinApp
{
public:
	//ウィンドウサイズ
	const int kCliantWidth = 1280; // 横幅
	const int kCliantHeight = 720; // 縦幅

	//初期化
	void Initialize();
	//更新
	void Update();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);

	HWND GetHwnd() const { return hwnd; }
private:
	//ウインドウクラスの設定
	WNDCLASS wc{};

	//ウインドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc;

	HWND hwnd = nullptr;
};

