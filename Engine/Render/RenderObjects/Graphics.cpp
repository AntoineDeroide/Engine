#include "Graphics.h"
#include "../Core/ExceptionHandler.h"

Graphics::Graphics() : 
	m_pCmdList(nullptr),
	m_pDevice(nullptr),
	m_pFactory(nullptr)
{
	Init();
}

bool Graphics::Init()
{
	HRESULT res = CreateDXGIFactory(IID_PPV_ARGS(&m_pFactory));
	if (FAILED(res))
	{
		ExceptionHandler::Instance().Shout("[GRAPHICS::Init()] | Couldm't create DXGIFactory");
	}

	res = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_1_0_GENERIC, IID_PPV_ARGS(&m_pDevice));
	if (FAILED(res))
	{
		ExceptionHandler::Instance().Shout("[GRAPHICS::Init()] | Couldn't create D3D12Device !");
	}

	m_pCmdList = new CommandList(m_pDevice);

	return true;
}

void Graphics::Release()
{


	m_pFactory->Release();
}