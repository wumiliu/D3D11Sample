#include "DebugRenderer.h"
#include "Scene/Camera.h"
#include "Scene/HpNode.h"
#include "DeviceManager.h"
#include "Graphics/D3D11VertexBuffer.h"
#include "ShaderManager.h"
#include "Graphics/D3D11VertexDeclaration.h"

// Cap the amount of lines to prevent crash when eg. debug rendering large heightfields
static const unsigned MAX_LINES = 1000000;
// Cap the amount of triangles to prevent crash.
static const unsigned MAX_TRIANGLES = 100000;
struct Test
{
	float x;
	float y;
	float z;
	float w;
};
unsigned ToUInt(Color color)
{
	DirectX::PackedVector::XMUBYTEN4 color_ = color.RGBA();
	return  color_.v;
}
DebugRenderer::DebugRenderer()
{
	CreateVertexBuffer();
}

void DebugRenderer::CreateVertexBuffer()
{
	vertexBufferPtr = std::make_shared<D3D11VertexBuffer>();
	m_deviceContext = g_objDeviecManager.GetImmediateContext();
}

DebugRenderer::~DebugRenderer()
{

}

void DebugRenderer::SetView(Camera* camera)
{
	if (!camera)
		return;

	view_ = camera->GetView();
	projection_ = camera->GetProjection();
	frustum_ = camera->GetFrustum();
}

void DebugRenderer::AddLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest /*= true*/)
{
	if (lines_.size() + noDepthLines_.size() >= MAX_LINES)
		return;

	if (depthTest)
		lines_.push_back(DebugLine(start, end, color));
	else
		noDepthLines_.push_back(DebugLine(start, end, color));
}

void DebugRenderer::AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Color& color, bool depthTest /*= true*/)
{
	if (triangles_.size() + noDepthTriangles_.size() >= MAX_TRIANGLES)
		return;

	if (depthTest)
		triangles_.push_back(DebugTriangle(v1, v2, v3, color));
	else
		noDepthTriangles_.push_back(DebugTriangle(v1, v2, v3, color));
}

void DebugRenderer::AddNode(HpNode * node, float scale /*= 1.0f*/, bool depthTest /*= true*/)
{
	if (!node)
		return;

	Vector3 start = node->GetWorldPosition();
	Quaternion rotation = node->GetWorldRotation();
	Vector3 rhs = Vector3::Transform(scale*Vector3::Right, rotation);
	Vector3 end = start +rhs;
	AddLine(start, end, { 1, 0, 0, 1 }, depthTest);
	rhs = Vector3::Transform(scale*Vector3::Up, rotation);
	end = start + rhs;
	AddLine(start, end, { 0, 1, 0, 1 }, depthTest);
	rhs = Vector3::Transform(scale*Vector3::Backward, rotation);
	end = start + rhs;
	AddLine(start, end, { 0, 0, 1, 1 }, depthTest);

}

void DebugRenderer::AddFrustum(const Frustum& frustum, const Color& color, bool depthTest /*= true*/, bool bShowClip)
{
	const Vector3* vertices = frustum.vertices_;

	AddLine(vertices[0], vertices[1], color, depthTest);
	AddLine(vertices[1], vertices[2], color, depthTest);
	AddLine(vertices[2], vertices[3], color, depthTest);
	AddLine(vertices[3], vertices[0], color, depthTest);
	AddLine(vertices[4], vertices[5], color, depthTest);
	AddLine(vertices[5], vertices[6], color, depthTest);
	AddLine(vertices[6], vertices[7], color, depthTest);
	AddLine(vertices[7], vertices[4], color, depthTest);
	AddLine(vertices[0], vertices[4], color, depthTest);
	AddLine(vertices[1], vertices[5], color, depthTest);
	AddLine(vertices[2], vertices[6], color, depthTest);
	AddLine(vertices[3], vertices[7], color, depthTest);
	if (bShowClip)
	{
		Color color_ = { 1.0f, 0.0f, 0.0f, 0.1f };
		AddTriangle(vertices[0], vertices[1], vertices[2], color_, depthTest);
		AddTriangle(vertices[0], vertices[2], vertices[3], color_, depthTest);

		AddTriangle(vertices[4], vertices[5], vertices[6], color_, depthTest);
		AddTriangle(vertices[4], vertices[6], vertices[7], color_, depthTest);

		AddTriangle(vertices[3], vertices[2], vertices[6], color_, depthTest);
		AddTriangle(vertices[3], vertices[6], vertices[7], color_, depthTest);

		AddTriangle(vertices[0], vertices[1], vertices[5], color_, depthTest);
		AddTriangle(vertices[0], vertices[5], vertices[4], color_, depthTest);

		AddTriangle(vertices[3], vertices[0], vertices[4], color_, depthTest);
		AddTriangle(vertices[3], vertices[4], vertices[7], color_, depthTest);

		AddTriangle(vertices[2], vertices[1], vertices[5], color_, depthTest);
		AddTriangle(vertices[2], vertices[5], vertices[6], color_, depthTest);

	}
}

void DebugRenderer::Render()
{
	ShaderVariationPtr vs = g_objShader.GetShader(VS, "Basic", "VERTEXCOLOR");
	ShaderVariationPtr ps = g_objShader.GetShader(PS, "Basic", "VERTEXCOLOR");
	vs->SetShaderParameter(VSP_MODEL, Matrix::Identity);
	vs->SetShaderParameter(VSP_VIEWPROJ, view_*projection_);

	m_MaterialPtr->SetMatrix(Matrix::Identity, view_, projection_);
	unsigned numVertices = (lines_.size() + noDepthLines_.size()) * 2 + (triangles_.size() + noDepthTriangles_.size()) * 3;
	// Resize the vertex buffer if too small or much too large
	if (vertexBufferPtr->GetVertexCount() < numVertices || vertexBufferPtr->GetVertexCount() > numVertices * 2)
		vertexBufferPtr->SetSize(numVertices, MASK_POSITION | MASK_COLOR, true);
	if (m_InputLayout)
	{
	}
	else
	{
		m_InputLayout = std::make_shared<VertexDeclaration>(vs.get(), vertexBufferPtr.get(), vertexBufferPtr->GetElementMask());
		m_deviceContext->IASetInputLayout(m_InputLayout->GetInputLayout());
	}
	float* dest = (float*)vertexBufferPtr->Lock(0, numVertices, true);
	if (!dest)
		return;


	for (unsigned i = 0; i < triangles_.size(); ++i)
	{
		const DebugTriangle& triangle = triangles_[i];

		dest[0] = triangle.v1_.x;
		dest[1] = triangle.v1_.y;
		dest[2] = triangle.v1_.z;
		((unsigned&)dest[3]) = ToUInt(triangle.color_);

		dest[4] = triangle.v2_.x;
		dest[5] = triangle.v2_.y;
		dest[6] = triangle.v2_.z;
		((unsigned&)dest[7]) = ToUInt(triangle.color_);

		dest[8] = triangle.v3_.x;
		dest[9] = triangle.v3_.y;
		dest[10] = triangle.v3_.z;
		((unsigned&)dest[11]) = ToUInt(triangle.color_);

		dest += 12;
	}

	vertexBufferPtr->Unlock();
	unsigned elementMask = vertexBufferPtr->GetElementMask();
	unsigned int stride = vertexBufferPtr->GetVertexSize();
	unsigned int offset = 0;
	ID3D11Buffer* vertexBuffers_ = (ID3D11Buffer*)vertexBufferPtr->GetGPUObject();
	m_deviceContext->IASetVertexBuffers(0, 1, &vertexBuffers_, &stride, &offset);
	ID3D11VertexShader*  pVertexShader = (ID3D11VertexShader*)vs->GetGPUObject();
	m_deviceContext->VSSetShader(pVertexShader, NULL, 0);
	ID3D11PixelShader*  pPixelShader = (ID3D11PixelShader*)ps->GetGPUObject();

	unsigned start = 0;
	unsigned count = 0;
	if (lines_.size())
	{
		count = lines_.size() * 2;
		m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_LINELIST);
		m_deviceContext->Draw(count, start);
		start += count;
	}
	if (triangles_.size())
	{
		count = triangles_.size() * 3;
		m_deviceContext->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		m_deviceContext->Draw(count, start);
		start += count;
	}
	EndFrame();
}

void DebugRenderer::EndFrame()
{
	unsigned linesSize = lines_.size();
	unsigned noDepthLinesSize = noDepthLines_.size();
	unsigned trianglesSize = triangles_.size();
	unsigned noDepthTrianglesSize = noDepthTriangles_.size();

	lines_.clear();
	noDepthLines_.clear();
	triangles_.clear();
	noDepthTriangles_.clear();

}

void DebugRenderer::AddCircle(const Vector3& center, const Vector3& normal, float radius, const Color& color, int steps /*= 64*/, bool depthTest /*= true*/)
{
	Quaternion orientation;
	Vector3 end;
	normal.Normalize(end);
	/// Define from the rotation difference between two direction vectors.
	orientation = Quaternion::CreateFromRotationTo(Vector3::Up, end);

	Vector3 rhs = Vector3::Transform(Vector3(radius, 0, 0), orientation);
	Vector3 p = rhs + center;

	for (int i = 1; i <= steps; ++i)
	{
		static const float M_DEGTORAD = M_PI / 180.0f;
		float angle = (float)i / (float)steps * 360.0f;
		angle *= M_DEGTORAD;
		Vector3 v(radius * cos(angle), 0, radius * sin(angle));
		rhs = Vector3::Transform(v,  orientation);

		Vector3 c = rhs  +center;
		AddLine(p, c, color, depthTest);
		p = c;
	}

	p = center + normal * (radius / 4.0f);
	AddLine(center, p, color, depthTest);
}

void DebugRenderer::AddCross(const Vector3& center, float size, const Color& color, bool depthTest /*= true*/)
{
	float halfSize = size / 2.0f;
	for (int i = 0; i < 3; ++i)
	{
		float start[3] = { center.x, center.y, center.z};
		float end[3] = { center.x, center.y, center.z };
		start[i] -= halfSize;
		end[i] += halfSize;
		Vector3 vStart(start);
		Vector3 vEnd(end);
		AddLine(vStart, vEnd, color, depthTest);
	}
}

void DebugRenderer::AddQuad(const Vector3& center, float width, float height, const Color& color, bool depthTest /*= true*/)
{
	Vector3 v0(center.x - width / 2, center.y, center.z - height / 2);
	Vector3 v1(center.x + width / 2, center.y, center.z - height / 2);
	Vector3 v2(center.x + width / 2, center.y, center.z + height / 2);
	Vector3 v3(center.x - width / 2, center.y, center.z + height / 2);
	AddLine(v0, v1, color, depthTest);
	AddLine(v1, v2, color, depthTest);
	AddLine(v2, v3, color, depthTest);
	AddLine(v3, v0, color, depthTest);
}



