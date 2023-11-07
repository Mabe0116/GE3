#pragma once

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include <cstdint>

#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

class Input
{
public:
	
	void Initialize(HINSTANCE w, HWND hwnd);

	void Update();

	bool isPushKey(uint8_t key);

	bool isReleaseKey(uint8_t key);

	bool isPushKeyEnter(uint8_t key);

	bool isPushKeyExit(uint8_t key);

private:
	//DirectInputの初期化
	IDirectInput8* directInput = nullptr;

	//キーボードデバイスの生成
	IDirectInputDevice8* keyboard = nullptr;

	//全キーの入力状態を取得する
	BYTE key_[256] = {};
	BYTE PreKey_[256] = {};


};

