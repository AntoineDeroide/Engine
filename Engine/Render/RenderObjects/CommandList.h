#pragma once

struct Fence
{
	__int64 current = 0; // Current fence value
	ID3D12Fence* pSelf = nullptr;

	Fence(ID3D12Device* pDevice)
	{
		HRESULT res = pDevice->CreateFence(0, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&pSelf));
		if (FAILED(res))
		{
			// Render::CommandList::Init "Failed to create Fence"
		}
	}
};

class CommandList
{
public:
	CommandList(ID3D12Device* pDevice);
	~CommandList();

	void Execute();
	void FlushCmdQueue();

protected:

private:
	void Init(); // Creates allocator and queue

	ID3D12Device* m_pDevice; // anchor

	ID3D12CommandQueue* m_pCmdQueue;
	ID3D12CommandAllocator* m_pCmdAlloc;
	ID3D12GraphicsCommandList* m_pCmdList;

	Fence* m_pFence;


};

