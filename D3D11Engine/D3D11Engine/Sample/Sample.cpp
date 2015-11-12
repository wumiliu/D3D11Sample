#include "Sample.h"
#include "SampleBase.h"

Sample::Sample(HINSTANCE hInstance, int nWidth /*= 1024*/, int nHeight /*= 600*/):
D3D11App(hInstance)
{
	mClientWidth = nWidth;
	mClientHeight = nHeight;
	pitch_ = yaw_ = 0.0f;
}


Sample::~Sample()
{

}

void Sample::InitResource()
{
	SkyBoxPtr = std::make_shared<SkyBox>();
	SkyBoxPtr->InitResource();
	gameObject.InitResource(GEOMETRY_TYPE_GRID);
	gameObject.SetTexture("Data\\Texture\\Ice.dds");
	gameSphereObject.InitResource(GEOMETRY_TYPE_SPHERE);
	gameSphereObject.SetTexture("Data\\Texture\\wall01.dds");
	g_objSprite.ResetSize(mClientWidth, mClientHeight);
	CreateScrene();
}

void Sample::CreateScrene()
{
	scene_ = std::make_shared<Scene>();
	cameraNode_ = scene_->CreateChild("Camera");
	cameraNode_->SetPosition(Vector3(0.0f, 2.0f, -30.0f));
	pitch_ = -5.0f;
	Quaternion q = Quaternion::CreateFromEulerAngles(pitch_, 0.0f, 0.0f);
	cameraNode_->SetRotation(q);
	float fieldOfView = (float)XM_PI / 4.0f;
	float AspectHByW = (float)mClientWidth / (float)mClientHeight;
	cameraMain = cameraNode_->CreateComponent<Camera>();
	cameraMain->ProjParams(fieldOfView, AspectHByW, 1.0f, 1000.0f);
}


void Sample::UpdateScene(float fTotalTime, float fDeltaTime)
{
	const float MOVE_SPEED = 20.0f;
	float dt = fDeltaTime / 1000.0f;
	if (::GetAsyncKeyState('W') & 0x8000)
		cameraNode_->Translate(Vector3::Backward * MOVE_SPEED * dt);
	if (::GetAsyncKeyState('S') & 0x8000)
		cameraNode_->Translate(Vector3::Forward * MOVE_SPEED * dt);
	if (::GetAsyncKeyState('A') & 0x8000)
		cameraNode_->Translate(Vector3::Left * MOVE_SPEED * dt);
	if (::GetAsyncKeyState('D') & 0x8000)
		cameraNode_->Translate(Vector3::Right * MOVE_SPEED * dt);
}

void Sample::RenderSample()
{
	SwapChainPtr->TurnZBufferOn();
	Matrix mWorld;
	Matrix mView;
	Matrix mProj;
	if (cameraMain)
	{
		mView = cameraMain->GetView();
		mProj = cameraMain->GetProjection();
	}

	gameObject.Render(Matrix::CreateScale(5, 5, 5), mView, mProj);
	gameSphereObject.Render(Matrix::CreateScale(3, 3, 3), mView, mProj);


	Vector3 eyePos = cameraNode_->GetWorldPosition();
	mWorld = Matrix::CreateTranslation(eyePos.x, eyePos.y, eyePos.z);
	SkyBoxPtr->Render(mWorld*mView*mProj);
}

void Sample::DrawScene()
{
	SwapChainPtr->Begin();
	RenderSample();
	SwapChainPtr->Flip();
}

void Sample::OnMouseUp(WPARAM btnState, int x, int y)
{
	Matrix mWorld;
	Vector3 vPos = { 0, 0, 5 };
	mWorld = Matrix::CreateTranslation(vPos);
	Quaternion q = Quaternion::CreateFromEulerAngles(-20.0f, 45.0f, 0.0f);
	mWorld = Matrix::CreateFromQuaternion(q) * mWorld;
	Camera* cameraMain = cameraNode_->GetComponent<Camera>(true);
	if (cameraMain)
	{
		DirectX::SimpleMath::Ray ray = cameraMain->CalcPickingRay(x, y, mWorld);
	}
	D3D11App::OnMouseUp(btnState, x, y);
}

void Sample::OnMouseMove(WPARAM btnState, int x, int y)
{
	if (bMouseDown)
	{
		if (mouseLast.bLeftDown)
		{
			int nX = x - mouseLast.X;
			int nY = y - mouseLast.Y;
			// Mouse sensitivity as degrees per pixel
			const float MOUSE_SENSITIVITY = 0.1f;
			yaw_ += MOUSE_SENSITIVITY * nX;
			pitch_ += MOUSE_SENSITIVITY * nY;
			pitch_ = MathHelper::Clamp(pitch_, -90.0f, 90.0f);
			Quaternion q = Quaternion::CreateFromEulerAngles(pitch_, yaw_, 0.0f);
			cameraNode_->SetRotation(q);
		}
		else
		{

		}
	}
	D3D11App::OnMouseMove(btnState, x, y);
}
