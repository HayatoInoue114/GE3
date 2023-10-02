#pragma once
#include <Windows.h>
#include <cstdint>

//WindowsAPI
class WinApp
{
public:
	//初期化
	void Initialize();
	//更新
	void Update();

	static LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
private:
	//ウインドウクラスの設定
	WNDCLASS wc{};

	//ウインドウサイズを表す構造体にクライアント領域を入れる
	RECT wrc;

	HWND hwnd = {};
};

