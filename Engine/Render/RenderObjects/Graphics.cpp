#include <iostream>

#include "Graphics.h"

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
		std::cout <<"[GRAPHICS::Init()] | Couldm't create DXGIFactory\n";
	}

	res = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_1_0_GENERIC, IID_PPV_ARGS(&m_pDevice));
	if (FAILED(res))
	{
		std::cout <<"[GRAPHICS::Init()] | Couldn't create D3D12Device !\n";
	}

	m_pCmdList = new CommandList(m_pDevice);

	return true;
}

void Graphics::Release()
{


	m_pFactory->Release();
}