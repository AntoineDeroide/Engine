#include "pch.h"

#ifdef _DEBUG

#include "DebugRenderer.h"
#include "FrameResources.h"
#include "RenderCamera.h"
#include "Shader.h"
#include "D12PipelineObject.h"
#include "Structs.h"

using namespace DirectX;

namespace Utils
{
	// Credits : Amelie Heinrich
	// Github : https://github.com/AmelieHeinrich/Seraph/blob/main/Source/DemoApp/Renderer/Passes/Debug.cpp
	gce::Vector3f32 GetNormalizedPerpendicular(gce::Vector3f32 base)
	{
		if (abs(base.x) > abs(base.y)) 
		{
			float32 len = sqrt(base.x * base.x + base.y * base.y);
			return gce::Vector3f32(base.z, 0.0f, -base.x) / len;
		}
		else 
		{
			float32 len = sqrt(base.y * base.y + base.z * base.z);
			return gce::Vector3f32(0.0f, base.z, -base.y) / len;
		}
	}

	float32 Length(gce::Vector3f32 toNormalize) 
	{
		return sqrt(toNormalize.x * toNormalize.x + toNormalize.y * toNormalize.y + toNormalize.z * toNormalize.z);
	}
}

namespace gce
{
/////////////////////////////////////////////////////////////
/// @brief Only valid builder. Calls the Instance's Init.
/////////////////////////////////////////////////////////////
DebugRenderer::DebugRenderer(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList) :
	m_pDevice(pDevice),
	m_pCmdList(pCmdList),
	m_pPSO(nullptr),
	m_vertices(),
	m_vertexVector()
{
	Init(m_pDevice, m_pCmdList);
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Initializes DebugRenderer instance.
/// @param pDevice A pointer to the current used ID3D12Device.
/// @param pCmdList A pointer to the current used ID3D12GraphicsCommandList.
////////////////////////////////////////////////////////////////////////////////
void DebugRenderer::Init(ID3D12Device* pDevice, ID3D12GraphicsCommandList* pCmdList)
{
	m_pDevice = pDevice;
	m_pCmdList = pCmdList;

	Shader VS("res/Render/Shaders/DebugRenderer.vs.cso");
	Shader PS("res/Render/Shaders/DebugRenderer.ps.cso");
	Shader RS("res/Render/Shaders/DebugRenderer.rs.cso");

	PSODescriptor psoDesc = {};
	psoDesc.type = DescriptorType::LINE;
	m_pPSO = new D12PipelineObject(VS, PS, RS, psoDesc);

	m_vertices.BufferLocation = FrameResourcesManager::GetCurrentFrameResource()->m_pDebugLinesCB->GetGPUAddress();
	m_vertices.StrideInBytes = sizeof(gce::Vertex);
	m_vertices.SizeInBytes = MAX_LINES * sizeof(DebugLine);
}

/////////////////////////////////////
/// @brief Destroys the instance.
/////////////////////////////////////
DebugRenderer::~DebugRenderer()
{
	m_pDevice = nullptr;
	m_pCmdList = nullptr;
	m_pPSO = nullptr;

	delete m_pDevice;
	delete m_pCmdList;
	delete m_pPSO;
}

/////////////////////////////////////////////////////////////////////
/// @brief Method used to get the current DebugRenderer instance.
/// @return Returns a DebugRenderer object.
/////////////////////////////////////////////////////////////////////
DebugRenderer& DebugRenderer::Instance()
{
	static DebugRenderer debugRenderer;
	return debugRenderer;
};

//////////////////////////////////////////////////////////////
/// @brief Method used to Add a DebugLine to the instance.
/// @param line The DebugLine object to add.
/// @return Returns a DebugLine object.
//////////////////////////////////////////////////////////////
DebugLine& DebugRenderer::AddDebugLine(DebugLine line, Vector4 color)
{
	line.from.color = color;
	line.to.color = color;

	Instance().PushLine(line);

	return line;
}

//////////////////////////////////////////////////////////////
/// @brief Method used to Add a DebugLine to the instance.
/// @param from The position from which the line starts.
/// @param to The position to which the line ends.
/// @return Returns a DebugLine object.
//////////////////////////////////////////////////////////////
DebugLine& DebugRenderer::AddDebugLine(Vector3f32 from, Vector3f32 to, Vector4 color)
{
	DebugLine line = {};
	line.from = { from, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };
	line.to = { to, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };

	DebugRenderer::Instance().PushLine(line);

	return line;
}

////////////////////////////////////////////////////////////////////
/// @brief Method used to Add a DebugLine to the instance.
/// @param from The vertex from which the line starts.
/// @param dir The direction which the DebugLine points towards.
/// @param length The length of the DebugLine.
/// @return Returns a DebugLine object.
////////////////////////////////////////////////////////////////////
DebugLine& DebugRenderer::AddDebugLine(Vector3f32 from, Vector3f32 dir, float32 length, Vector4 color)
{
	Vector3f32 to = { dir.x * length, dir.y * length, dir.z * length };

	DebugLine line = {};
	line.from = { from, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };	
	line.to = { to, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f, 0.0f }, { 0.0f, 0.0f }, color };
	
	DebugRenderer::Instance().PushLine(line);

	return line;
}

//////////////////////////////////////////////////////////////
/// @brief Method used to Add a DebugLine to the instance.
/// @param from The vertex from which the line starts.
/// @param to The vertex to which the line ends.
/// @return Returns a DebugLine object.
//////////////////////////////////////////////////////////////
DebugLine& DebugRenderer::AddDebugLine(Vertex from, Vertex to, Vector4 color)
{
	DebugLine line = {};
	line.from = { from.pos, from.normal, from.tangent, from.uv, color };
	line.to = { to.pos, to.normal, to.tangent, to.uv, color };

	DebugRenderer::Instance().PushLine(line);

	return line;
}

///////////////////////////////////////////////////////
/// @brief Method used to create a DebugBox object.
/// @param scale The scale of the box.
/// @param rot The rotation applied to the box.
/// @param pos The world position of the box.
/// @return A pointer to the DebugBox created.
///////////////////////////////////////////////////////
DebugBox* DebugRenderer::CreateDebugBox(Vector3f32 scale, Vector3f32 rot, Vector3f32 pos, Vector4 color)
{
	DebugBox* box = new DebugBox();
	
	// Local
	box->vertices[0] = { {-0.5, -0.5f, -0.5}, {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } };
	box->vertices[1] = { {0.5, -0.5f, -0.5},  {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } };
	box->vertices[2] = { {0.5, -0.5f, 0.5},   {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } };
	box->vertices[3] = { {-0.5, -0.5f, 0.5},  {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } };
	box->vertices[4] = { {-0.5, 0.5f, -0.5},  {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } };
	box->vertices[5] = { {0.5, 0.5f, -0.5},   {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } };
	box->vertices[6] = { {0.5, 0.5f, 0.5},    {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } };
	box->vertices[7] = { {-0.5, 0.5f, 0.5},   {0.0f, 0.0f, 0.0f}, {0.0f, 0.0f, 0.0f}, { 0.0f, 0.0f } };

	XMMATRIX S = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMMATRIX R = XMMatrixRotationRollPitchYaw(XMConvertToRadians(rot.x), XMConvertToRadians(rot.y), XMConvertToRadians(rot.z));
	XMMATRIX T = XMMatrixTranslation(pos.x, pos.y, pos.z);
	XMMATRIX world = S * R * T;

	for (uint8 i = 0; i < 8; i++)
	{
		XMVECTOR tempVector = XMVectorSet(box->vertices[i].pos.x, box->vertices[i].pos.y, box->vertices[i].pos.z, 1.0f);
		tempVector = XMVector3Transform(tempVector, world);
		XMFLOAT3 tempFloat;
		XMStoreFloat3(&tempFloat, tempVector);

		box->vertices[i].pos = { tempFloat.x * scale.x, tempFloat.y * scale.y, tempFloat.z * scale.z };
	}

	// [1]
	box->lines[0] = DebugRenderer::AddDebugLine(box->vertices[0], box->vertices[1], color);
	box->lines[1] = DebugRenderer::AddDebugLine(box->vertices[1], box->vertices[2], color);
	box->lines[2] = DebugRenderer::AddDebugLine(box->vertices[2], box->vertices[3], color);
	box->lines[3] = DebugRenderer::AddDebugLine(box->vertices[3], box->vertices[0], color);
	// [2]
	box->lines[4] = DebugRenderer::AddDebugLine(box->vertices[4], box->vertices[5], color);
	box->lines[5] = DebugRenderer::AddDebugLine(box->vertices[5], box->vertices[6], color);
	box->lines[6] = DebugRenderer::AddDebugLine(box->vertices[6], box->vertices[7], color);
	box->lines[7] = DebugRenderer::AddDebugLine(box->vertices[7], box->vertices[4], color);
	// [3]
	box->lines[8] = DebugRenderer::AddDebugLine(box->vertices[0], box->vertices[4], color);
	box->lines[9] = DebugRenderer::AddDebugLine(box->vertices[1], box->vertices[5], color);
	box->lines[10] = DebugRenderer::AddDebugLine(box->vertices[2], box->vertices[6], color);
	box->lines[11] = DebugRenderer::AddDebugLine(box->vertices[3], box->vertices[7], color);

	return box;
}

////////////////////////////////////////////////////////////////////
/// @brief This method creates a DebugSphere object.
/// @param center The center of the sphere.
/// @param radius The radius of the sphere.
/// @param color The color of the sphere.
/// @return Returns a pointer to the DebugSphere object created.
////////////////////////////////////////////////////////////////////
DebugSphere* DebugRenderer::CreateDebugSphere(Vector3f32 center, float32 radius, Vector4 color)
{
	DebugSphere* sphere = new DebugSphere();

	sphere->circles[0] = CreateDebugCircle(center, Vector3f32(1.0f, 0.0f, 0.0f), radius, color);
	sphere->circles[1] = CreateDebugCircle(center, Vector3f32(0.0f, 1.0f, 0.0f), radius, color);
	sphere->circles[2] = CreateDebugCircle(center, Vector3f32(0.0f, 0.0f, 1.0f), radius, color);

	return sphere;
}

DebugFrustum* DebugRenderer::CreateDebugFrustum(RenderCamera& cam, Vector4 color)
{
	DebugFrustum* frustum = new DebugFrustum();

	Vector3f32 camPos = { cam.GetWMatrix().GetValue(3,0), cam.GetWMatrix().GetValue(3,1), cam.GetWMatrix().GetValue(3,2) };
	
	// Local vertex pos
	Vertex corners[8] = {}; 
	
	corners[0].pos = {-1.0f, -1.0f, 0.0f};
	corners[1].pos = {-1.0f,  1.0f, 0.0f};
	corners[2].pos = {1.0f,   1.0f, 0.0f};
	corners[3].pos = {1.0f,  -1.0f, 0.0f};

	corners[4].pos = {-1.0f, -1.0f, 1.0f};
	corners[5].pos = {-1.0f,  1.0f, 1.0f};
	corners[6].pos = {1.0f,   1.0f, 1.0f};
	corners[7].pos = {1.0f,  -1.0f, 1.0f};

	gce::Matrix projView = cam.GetVPMatrix();
	projView.Transpose();
	projView.Inverse();

	XMMATRIX temp(
		projView.GetValue(0,0), projView.GetValue(0, 1), projView.GetValue(0, 2), projView.GetValue(0, 3),
		projView.GetValue(1,0), projView.GetValue(1, 1), projView.GetValue(1, 2), projView.GetValue(1, 3),
		projView.GetValue(2,0), projView.GetValue(2, 1), projView.GetValue(2, 2), projView.GetValue(2, 3),
		projView.GetValue(3,0), projView.GetValue(3, 1), projView.GetValue(3, 2), projView.GetValue(3, 3)
	);

	for (char8 i = 0; i < 8; i++) {
		XMVECTOR cornerPos = { corners[i].pos.x, corners[i].pos.y, corners[i].pos.z, 1.0f };
	
		XMFLOAT4 divider;
		XMStoreFloat4(&divider, XMVector4Transform(cornerPos, temp));
		divider.x /= divider.w;
		divider.y /= divider.w;
		divider.z /= divider.w;

		corners[i].pos = { divider.x, divider.y, divider.z };

		frustum->vertices[i] = corners[i];
	}

	// sides
	frustum->lines[0] = DebugRenderer::AddDebugLine(corners[0], corners[4], color);
	frustum->lines[1] = DebugRenderer::AddDebugLine(corners[1], corners[5], color);
	frustum->lines[2] = DebugRenderer::AddDebugLine(corners[2], corners[6], color);
	frustum->lines[3] = DebugRenderer::AddDebugLine(corners[3], corners[7], color);

	// "near" plane
	frustum->lines[4] = DebugRenderer::AddDebugLine(corners[0], corners[1], color);
	frustum->lines[5] = DebugRenderer::AddDebugLine(corners[1], corners[2], color);
	frustum->lines[6] = DebugRenderer::AddDebugLine(corners[2], corners[3], color);
	frustum->lines[7] = DebugRenderer::AddDebugLine(corners[3], corners[0], color);

	// "far" plane
	frustum->lines[8] = DebugRenderer::AddDebugLine(corners[4], corners[5], color);
	frustum->lines[9] = DebugRenderer::AddDebugLine(corners[5], corners[6], color);
	frustum->lines[10] = DebugRenderer::AddDebugLine(corners[6], corners[7], color);
	frustum->lines[11] = DebugRenderer::AddDebugLine(corners[7], corners[4], color);

	return frustum;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
/// @brief This method creates a DebugArrow. Useful to show force applications, or object's facing.
/// @param from The position from which the arrow comes.
/// @param dir The direction the arrow points towards.
/// @param length The length of the arrow.
/// @return A pointer to the DebugArrow object created.
///////////////////////////////////////////////////////////////////////////////////////////////////////
DebugArrow* DebugRenderer::CreateDebugArrow(Vector3f32 from, Vector3f32 dir, float32 length, Vector4 color)
{
	DebugArrow* arrow = new DebugArrow();

	DebugLine mainLine = DebugRenderer::Instance().AddDebugLine(from, dir, length, color);

	arrow->vertices[0].pos = mainLine.from.pos;
	arrow->vertices[1].pos = mainLine.to.pos;

	Vector3f32 to = { from.x + dir.x * length, from.y + dir.y * length, from.z + dir.z * length };
	Vector3f32 perp = Utils::GetNormalizedPerpendicular(dir);

	DebugLine arrow1 = AddDebugLine(to - dir + perp, mainLine.to.pos, color);
	DebugLine arrow2 = AddDebugLine(to - dir - perp, mainLine.to.pos, color);

	arrow->vertices[2].pos = arrow1.to.pos;
	arrow->vertices[3].pos = arrow2.to.pos;

	arrow->lines[0] = mainLine;
	arrow->lines[1] = arrow1;
	arrow->lines[2] = arrow2;

	return arrow;
}

////////////////////////////////////////////////////////////
/// @brief This method creates a DebugCircle.
/// @param center The center of the circle.
/// @param normal The normal of the circle.
/// @param radius The radius of the circle.
/// @return A pointer to the DebugCircle object created.
////////////////////////////////////////////////////////////
DebugCircle* DebugRenderer::CreateDebugCircle(Vector3f32 center, Vector3f32 normal, float32 radius, Vector4 color)
{
	DebugCircle* circle = new DebugCircle();

	float32 angle = 2 * XM_PI / 32.0f;
	Vertex previous = {};
	Vertex current = {};
	Vector3f32 tangent = {};
	Vector3f32 bitangent = {};

	if (abs(normal.y) > 0.99f)
		tangent = Vector3f32(1.0f, 0.0f, 0.0f);
	else
		tangent = (normal.CrossProduct(Vector3f32(0.0f, 1.0f, 0.0f))).Normalize();
	
	bitangent = (normal.CrossProduct(tangent)).Normalize();

	for (int8 i = 0; i <= 32; i++)
	{
		float32 currentAngle = angle * i;
		current.pos = center + (tangent * cos(currentAngle) + bitangent * sin(currentAngle)) * radius;
		circle->vertices[i].pos = current.pos;
		
		if (i != 0)
			circle->lines[i - 1] = DebugRenderer::Instance().AddDebugLine(previous, current, color);

		previous = current;
	}

	return circle;
}

///////////////////////////////////////////////////////////////////////
/// @brief This method creates a Rectangle outline.
/// @param center The center of the rectangle.
/// @param normal The direction the rectangle is facing.
/// @param width The width of the rectangle.
/// @param height The height of the rectangle.
/// @param color The color of the rectangle. Set to red by default.
/// @return Returns a pointer to the DebugQuad struct created.
///////////////////////////////////////////////////////////////////////
DebugQuad* DebugRenderer::CreateDebugRectangle(Vector3f32 center, Vector3f32 normal, float32 width, float32 height, Vector4 color)
{
	DebugQuad* rect = new DebugQuad();

	Vector3f32 tangent = {};
	Vector3f32 bitangent = {};

	if (abs(normal.y) > 0.99f)
		tangent = Vector3f32(1.0f, 0.0f, 0.0f);
	else
		tangent = (normal.CrossProduct(Vector3f32(0.0f, 1.0f, 0.0f))).Normalize();

	bitangent = (normal.CrossProduct(tangent)).Normalize();

	rect->vertices[0].pos = center + (tangent * -(width / 2)) + (bitangent * -(height / 2));
	rect->vertices[1].pos = center + (tangent * (width / 2)) + (bitangent * -(height / 2));
	rect->vertices[2].pos = center + (tangent * (width / 2)) + (bitangent * (height / 2));
	rect->vertices[3].pos = center + (tangent * -(width / 2)) + (bitangent * (height / 2));
	
	rect->lines[0] = DebugRenderer::AddDebugLine(rect->vertices[0], rect->vertices[1], color);
	rect->lines[1] = DebugRenderer::AddDebugLine(rect->vertices[1], rect->vertices[2], color);
	rect->lines[2] = DebugRenderer::AddDebugLine(rect->vertices[2], rect->vertices[3], color);
	rect->lines[3] = DebugRenderer::AddDebugLine(rect->vertices[3], rect->vertices[0], color);

	return rect;
}

////////////////////////////////////////////////////////////////////
/// @brief This method creates a Square outline.
/// @param center The center of the square.
/// @param normal The direction the square is facing.
/// @param size The size of the square.
/// @param color The color of the square. Set to red by default.
/// @return Returns a pointer to the DebugQuad struct created.
////////////////////////////////////////////////////////////////////
DebugQuad* DebugRenderer::CreateDebugSquare(Vector3f32 center, Vector3f32 normal, float32 size, Vector4 color)
{
	DebugQuad* square = new DebugQuad();

	Vector3f32 tangent = {};
	Vector3f32 bitangent = {};
	
	if (abs(normal.y) > 0.99f)
		tangent = Vector3f32(1.0f, 0.0f, 0.0f);
	else
		tangent = (normal.CrossProduct(Vector3f32(0.0f, 1.0f, 0.0f))).Normalize();

	bitangent = (normal.CrossProduct(tangent)).Normalize();

	square->vertices[0].pos = center + (tangent * -(size / 2)) + (bitangent * -(size / 2));
	square->vertices[1].pos = center + (tangent * (size / 2)) + (bitangent * -(size / 2));
	square->vertices[2].pos = center + (tangent * (size / 2)) + (bitangent * (size / 2));
	square->vertices[3].pos = center + (tangent * -(size / 2)) + (bitangent * (size / 2));

	square->lines[0] = DebugRenderer::AddDebugLine(square->vertices[0], square->vertices[1]);
	square->lines[1] = DebugRenderer::AddDebugLine(square->vertices[1], square->vertices[2]);
	square->lines[2] = DebugRenderer::AddDebugLine(square->vertices[2], square->vertices[3]);
	square->lines[3] = DebugRenderer::AddDebugLine(square->vertices[3], square->vertices[0]);

	return square;
}

/////////////////////////////////////////////////////////////////////////////////////
/// @brief Method used to push a DebugLine in the line Array.
/// @param line The line to push.
/// @return Returns true if the lineCount doesn't exceed the constexpr MAX_LINES.
/////////////////////////////////////////////////////////////////////////////////////
bool DebugRenderer::PushLine(DebugLine& line)
{
	if ((m_vertexVector.size() / 2) < MAX_LINES)
	{
		DebugRenderer::Instance().m_vertexVector.push_back(line.from);
		DebugRenderer::Instance().m_vertexVector.push_back(line.to);

		FrameResourcesManager::GetCurrentFrameResource()->m_pDebugLinesCB->CopyData(m_vertexVector.data(), sizeof(Vertex) * m_vertexVector.size());
		return true;
	}

	return false;
}

void DebugRenderer::ClearLines()
{
	m_vertexVector.clear();
}

/////////////////////////////////////////////////////////////////////////
/// @brief Method used to draw every DebugLine stored in m_lineArray.
/// @param vp The current ViewProj Matrix.
/////////////////////////////////////////////////////////////////////////
void DebugRenderer::BeginDebugDraw(ID3D12GraphicsCommandList* pCmdList, RenderCamera* cam)
{
	m_pCmdList = pCmdList;

	m_pCmdList->SetGraphicsRootSignature(m_pPSO->m_pRootSignature);
	m_pCmdList->SetPipelineState(m_pPSO->m_pPipelineState);
	m_pCmdList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);

	m_pCmdList->SetGraphicsRoot32BitConstants(0, 16, &cam->GetVPMatrix(), 0);

	m_pCmdList->IASetVertexBuffers(0, 1, &m_vertices);	
}

void DebugRenderer::EndDebugDraw()
{
	m_pCmdList->DrawInstanced(m_vertexVector.size(), 1, 0, 0);
	ClearLines();
}

}


#endif