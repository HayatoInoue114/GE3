#include "DirectXCommon.h"
#include <cassert>
#include <vector>
#include <string>

#pragma comment(lib,"d3d12.lib")
#pragma comment(lib,"dxgi.lib")

using namespace Microsoft::WRL;

void DirectXCommon::Initialize() {
	device = nullptr;
	dxgiFactory = nullptr;
	swapChain = nullptr;
	commandAllocator = nullptr;
	commandList = nullptr;
	commandQueue = nullptr;
	rtvHeap = nullptr;
}

void DirectXCommon::InitializeDevice() {
	HRESULT result;
	//DXGIファクトリ（デバイス生成後は解放されてよい）
	ComPtr<IDXGIFactory7> dxgiFactory;
	
	#ifdef _DEBUG
	ID3D12Debug1* debugControllar = nullptr;
	if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugControllar)))) {
		//デバッグレイヤーを有効化する
		debugControllar->EnableDebugLayer();
		//さらにGPU側でもチェックを行うようにする
		debugControllar->SetEnableGPUBasedValidation(TRUE);
	}
	#endif // _DEBUG


	//DXGIファクトリーの生成
	dxgiFactory = nullptr;

	result = CreateDXGIFactory(IID_PPV_ARGS(&dxgiFactory));
	assert(SUCCEEDED(result));


	useAdapter = nullptr;
	//良い順にアダプタを頼む
	for (UINT i = 0; dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&useAdapter)) != DXGI_ERROR_NOT_FOUND; ++i) {
		//アダプター情報を取得する
		adapterDesc = {};
		HRESULT hr = useAdapter->GetDesc3(&adapterDesc);
		assert(SUCCEEDED(hr));//取得できないのは一大事
		//ソフトウェアアダプタでなければ採用!
		if (!(adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)) {
			//採用したアダプタの情報をログに出力。wstringの方なので注意
			Log(ConvertString(std::format(L"Use Adapter:{}\n", adapterDesc.Description)));
			break;
		}
		useAdapter = nullptr;//ソフトウェアアダプタの場合は見なかったことにする
	}

	//適切なアダプタが見つからなかったので起動できない
	assert(useAdapter != nullptr);


}

void DirectXCommon::InitializeCommand() {

}