#include "Input.h"
#include <assert.h>
#include <memory>

void Input::Initialize(HINSTANCE w ,HWND hwnd) {
	//DirectInputの初期化
	HRESULT result = DirectInput8Create(
		w, DIRECTINPUT_VERSION, IID_IDirectInput8,
		(void**)&directInput, nullptr);
	assert(SUCCEEDED(result));

	//キーボードデバイスの生成
	result = directInput->CreateDevice(GUID_SysKeyboard, &keyboard, NULL);
	assert(SUCCEEDED(result));
	//入力データ形式のセット
	result = keyboard->SetDataFormat(&c_dfDIKeyboard);
	assert(SUCCEEDED(result));
	//排他制御レベルのセット
	result = keyboard->SetCooperativeLevel(
		hwnd, DISCL_FOREGROUND | DISCL_NONEXCLUSIVE | DISCL_NOWINKEY);
	assert(SUCCEEDED(result));
}

void Input::Update() {

	std::memcpy(PreKey_, key_, 256);

	//キーボード情報の取得開始
	keyboard->Acquire();

	//全キーの入力状態を取得する
	keyboard->GetDeviceState(sizeof(key_), key_);
}
bool Input::isPushKey(uint8_t key) {
	if (key_[key] == 0x80) {
		return true;
	}
	return false;
}
bool Input::isReleaseKey(uint8_t key) {
	if (key_[key] == 0x00) {
		return true;
	}
	return false;
}
bool Input::isPushKeyEnter(uint8_t key) {
	if (key_[key] == 0x80 && PreKey_[key] == 0x00) {
		return true;
	}
	return false;
}
bool Input::isPushKeyExit(uint8_t key) {
	if (key_[key] == 0x00 && PreKey_[key] == 0x80) {
		return true;
	}
	return false;
}