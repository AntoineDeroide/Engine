#pragma once
#include "common.h"
#include <d3d11on12.h>
#include "CommandList.h"

//#include <wrl.h>
//#include <d2d1_1.h>
//#include <dwrite.h>

class Graphics
{
public:
	Graphics();
protected:
private:
	ID3D12Device* m_pDevice;
	IDXGIFactory* m_pFactory;

	CommandList* m_pCmdList;

	bool Init();

	void Release();

};