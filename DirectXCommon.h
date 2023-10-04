#pragma once
#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl.h>
#include "FormatString.h"
#include "WinApp.h"

class DirectXCommon
{
public: //メンバ関数
	//初期化
	void Initialize(WinApp* winApp);

	void InitializeDevice();

	void InitializeCommand();

	void InitializeSwapchain();

	void InitializeRenderTargetView();

	ID3D12DescriptorHeap* CreateDescriptorHeap(ID3D12Device* Device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, UINT numDescriptors, bool shaderVisible);
private:
	//DirectX12デバイス
	Microsoft::WRL::ComPtr<ID3D12Device> device;
	//DXGIファクトリ
	Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
	IDXGISwapChain4* swapChain;
	Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator;
	Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList;
	Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue;
	Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> rtvDescriptorHeap;
	Microsoft::WRL::ComPtr<ID3D12Fence> fence;
	//使用するアダプタ用の変数。最初にnullptrを入れておく
	Microsoft::WRL::ComPtr<IDXGIAdapter4> useAdapter;

	DXGI_ADAPTER_DESC3 adapterDesc = {};
	D3D12_COMMAND_QUEUE_DESC commandQueueDesc = {};
	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = {};
	D3D12_DESCRIPTOR_HEAP_DESC rtvDescriptorHeapDesc = {};

	//バックバッファ
	UINT backBufferIndex = {};

	ID3D12Resource* swapChainResource[2] = {};

	//RTVの設定
	D3D12_RENDER_TARGET_VIEW_DESC rtvDesc = {};

	//ディスクリプタの先頭を取得する
	D3D12_CPU_DESCRIPTOR_HANDLE rtvStartHandle = {};

	//RTVを２つ作るのでディスクリプタ２つ用意
	D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle[2] = {};

	//初期値0でFenceを作る
	uint64_t fenceValue = {};

	std::vector<Microsoft::WRL::ComPtr<IDXGIAdapter4>> backbuffers;

	//WindowsAPI
	WinApp* winApp_ = nullptr;
};

