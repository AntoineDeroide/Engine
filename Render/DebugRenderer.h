#ifdef _DEBUG

#ifndef RENDER_DEBUGRENDERER_H_INCLUDED
#define RENDER_DEBUGRENDERER_H_INCLUDED

#include "Core/define.h"
#include "d3dx12.h"
#include "Structs.h"

#include <vector>

constexpr int16 MAX_LINES = 400;

#define RED    { 255.0f,   0.0f,    0.0f, 255.0f }
#define GREEN  { 0.0f,   255.0f,    0.0f, 255.0f }
#define BLUE   { 0.0f,     0.0f,  255.0f, 255.0f }
#define PINK   { 255.0f,   0.0f,  255.0f, 255.0f }
#define CYAN   { 0.0f,   255.0f,  255.0f, 255.0f }
#define YELLOW { 255.0f, 255.0f,    0.0f, 255.0f }

namespace gce 
{

class D12PipelineObject;
class DynamicBuffer;
class Geometry;
class RenderCamera;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief DebugRenderer is a Singleton used to debug 3D render. 
/// @note To use DebugRenderer correctly, wrap all calls of the instance between "#ifdef _DEBUG" and "#endif" preprocessor directives.
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class DebugRenderer
{
public:
	// Prevent use of copy or move constructor
	DebugRenderer(DebugRenderer const& other) = delete;
	DebugRenderer(DebugRenderer&& other) = delete;

	// Prevent use of copy or move operator
	DebugRenderer& operator=(DebugRenderer const& other) = delete;
	DebugRenderer& operator=(DebugRenderer&& other) = delete;

	DebugRenderer(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList);
	DebugRenderer() = default;
	~DebugRenderer();

	static DebugRenderer& Instance();
	
	// 3D
	static DebugBox*     CreateDebugBox(Vector3f32 scale, Vector3f32 rot, Vector3f32 pos, Vector4 color = RED);
	static DebugSphere*  CreateDebugSphere(Vector3f32 center, float32 radius, Vector4 color);
	static DebugFrustum* CreateDebugFrustum(RenderCamera& cam, Vector4 color);

	// 2D 
	static DebugLine& AddDebugLine(DebugLine line, Vector4 color = RED);
	static DebugLine& AddDebugLine(Vector3f32 from, Vector3f32 to, Vector4 color = RED);
	static DebugLine& AddDebugLine(Vector3f32 from, Vector3f32 dir, float32 length, Vector4 color = RED);
	static DebugLine& AddDebugLine(Vertex from, Vertex to, Vector4 color = RED);

	static DebugArrow*  CreateDebugArrow(Vector3f32 from, Vector3f32 dir, float32 length, Vector4 color = RED);
	static DebugCircle* CreateDebugCircle(Vector3f32 center, Vector3f32 normal, float32 radius, Vector4 color = RED);
	static DebugQuad*   CreateDebugSquare(Vector3f32 center, Vector3f32 normal, float32 size, Vector4 color = RED);
	static DebugQuad*   CreateDebugRectangle(Vector3f32 center, Vector3f32 normal, float32 width, float32 height, Vector4 color = RED);

	void BeginDebugDraw(ID3D12GraphicsCommandList* pCmdList, RenderCamera* cam);
	void EndDebugDraw();

private:
	void Init(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList);
	bool PushLine(DebugLine& line);

	void ClearLines();
	
	ID3D12Device* m_pDevice;
	ID3D12GraphicsCommandList* m_pCmdList;
	D12PipelineObject* m_pPSO;

	D3D12_VERTEX_BUFFER_VIEW m_vertices;
	std::vector<Vertex> m_vertexVector;

	friend class RenderContext;
};

}
#endif

#endif
