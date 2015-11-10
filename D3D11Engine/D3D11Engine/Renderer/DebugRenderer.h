#pragma once
#include "Scene/Component.h"
#include "Framework/Frustum.h"


typedef std::shared_ptr<class VertexDeclaration>VertexDeclarationPtr;
/// Debug rendering line.
struct DebugLine
{
	/// Construct undefined.
	DebugLine()
	{
	}

	/// Construct with start and end positions and color.
	DebugLine(const Vector3& start, const Vector3& end, Color color) :
		start_(start),
		end_(end),
		color_(color)
	{
	}

	/// Start position.
	Vector3 start_;
	/// End position.
	Vector3 end_;
	/// Color.
	Color color_;
};

/// Debug render triangle.
struct DebugTriangle
{
	/// Construct undefined.
	DebugTriangle()
	{
	}

	/// Construct with start and end positions and color.
	DebugTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, Color color) :
		v1_(v1),
		v2_(v2),
		v3_(v3),
		color_(color)
	{
	}

	/// Vertex a.
	Vector3 v1_;
	/// Vertex b.
	Vector3 v2_;
	/// Vertex c.
	Vector3 v3_;
	/// Color.
	Color color_;

};

/// Debug render triangle.
struct DebugTriangleEx
{

	/// Vertex a.
	Vector3 v1_;
	/// Vertex b.
	Vector3 v2_;
	/// Vertex c.
	Vector3 v3_;
	/// Color.
	unsigned color_;

};
class DebugRenderer :public Component
{
	OBJECT(DebugRenderer);

public:
	DebugRenderer();
	~DebugRenderer();
	/// Set the camera viewpoint. Call before rendering, or before adding geometry if you want to use culling.
	void SetView(class Camera* camera);
	/// Add a line.
	void AddLine(const Vector3& start, const Vector3& end, const Color& color, bool depthTest = true);

	/// Add a triangle.
	void AddTriangle(const Vector3& v1, const Vector3& v2, const Vector3& v3, const Color& color, bool depthTest = true);

	/// Add a scene node represented as its coordinate axes.
	void AddNode(HpNode * node, float scale = 1.0f, bool depthTest = true);

	/// Add a frustum.
	void AddFrustum(const Frustum& frustum, const Color& color, bool depthTest = true, bool bShowClip = false);

	/// Add a circle.
	void AddCircle(const Vector3& center, const Vector3& normal, float radius, const Color& color, int steps = 64, bool depthTest = true);
	/// Add a cross.
	void AddCross(const Vector3& center, float size, const Color& color, bool depthTest = true);
	/// Add a quad on the XZ plane.
	void AddQuad(const Vector3& center, float width, float height, const Color& color, bool depthTest = true);
	/// Update vertex buffer and render all debug lines. The viewport and rendertarget should be set before.
	void Render();
protected:
	void CreateVertexBuffer();
	void EndFrame();
private:

	/// Lines rendered with depth test.
	std::vector<DebugLine> lines_;
	/// Lines rendered without depth test.
	std::vector<DebugLine> noDepthLines_;
	/// Triangles rendered with depth test.
	std::vector<DebugTriangle> triangles_;
	/// Triangles rendered without depth test.
	std::vector<DebugTriangle> noDepthTriangles_;


	/// View transform.
	Matrix view_;
	/// Projection transform.
	Matrix projection_;
	/// View frustum.
	Frustum frustum_;

	/// Vertex buffer.
	std::shared_ptr<class D3D11VertexBuffer> vertexBufferPtr;
	ID3D11Device			*m_d3dDevice;				//D3D11设备
	ID3D11DeviceContext		*m_deviceContext;			//设备上下文
	std::shared_ptr<class D3D11RendererMaterial>m_MaterialPtr;
	VertexDeclarationPtr m_InputLayout;
};

