#include "pch.h"
#include "CommandList.h"

HRESULT res;

/// <summary>
/// Marks all commands up to the calling point.
/// </summary>
void CommandList::FlushCmdQueue()
{
	m_pFence->current++;

	m_pCmdQueue->Signal(m_pFence->pSelf, m_pFence->current);

	if (m_pFence->pSelf->GetCompletedValue() < m_pFence->current)
	{
		HANDLE eventHandle = CreateEventEx(nullptr, 0, false, EVENT_ALL_ACCESS);

		m_pFence->pSelf->SetEventOnCompletion(m_pFence->current, eventHandle);

		WaitForSingleObject(eventHandle, INFINITE);
		CloseHandle(eventHandle);
	}
}

void CommandList::Init()
{
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;

	res = m_pDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_pCmdQueue));
	if (FAILED(res))
	{
		// Render::CommandList::Init "Failed to create Command Queue"
	}

	res = m_pDevice->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_pCmdAlloc));
	if (FAILED(res))
	{
		// Render::CommandList::Init "Failed to create Command Allocator"
	}


	res = m_pDevice->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_pCmdAlloc, nullptr, IID_PPV_ARGS(&m_pCmdList));
	if (FAILED(res))
	{
		// Render::CommandList::Init "Failed to create CommandList"
	}

	m_pCmdList->Close();
	
	FlushCmdQueue();
}

CommandList::CommandList(ID3D12Device* pDevice) : 
	m_pCmdAlloc(nullptr), 
	m_pCmdList(nullptr), 
	m_pCmdQueue(nullptr), 
	m_pDevice(pDevice)
{
	Init();

	m_pFence = new Fence(pDevice);
}

CommandList::~CommandList()
{
	m_pCmdAlloc->Release();
	m_pCmdList->Release();
	m_pCmdQueue->Release();
	m_pFence->pSelf->Release();
}
