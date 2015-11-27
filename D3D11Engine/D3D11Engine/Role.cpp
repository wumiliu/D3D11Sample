#include "Role.h"
#include "Scene/Scene.h"

Role::Role()
{
}


Role::~Role()
{
}

void Role::Init(std::shared_ptr<class Scene> scene_)
{
	gameObject.SetTexture("Data\\Texture\\ice.dds");
	gameObject.InitResource(GEOMETRY_TYPE_BOX);
	

	rootNode_ = scene_->CreateChild("rootNode_");
	rootNode_->SetWorldPosition({ 0, 10, 0 });
	
	HpNode* pNode_ = rootNode_->CreateChild("Bip01_Pelvis");
	pNode_->SetWorldPosition({ 0, 8, 0 });

	pNode_ = rootNode_->CreateChild("Bip01_Spine1");
	pNode_->SetWorldPosition({ 3, 8, 0 });
}


void Role::Render(Matrix view, Matrix proj)
{
	Matrix world = rootNode_->GetWorldTransform();
	int nNumber = rootNode_->GetNumChildren();
	for (int i = 0; i < nNumber; ++i)
	{
		HpNode* pNode = rootNode_->GetChild(i);
		if (pNode)
		{
			world = pNode->GetWorldTransform();
			gameObject.Render(world, view, proj);
		}
	}



}

void Role::CreateRagdollBone(const String& boneName, const Vector3& size, const Vector3& position, const Quaternion& rotation)
{

}

void Role::UpdateScene(float fTotalTime, float fDeltaTime)
{
	Quaternion q = Quaternion::CreateFromEulerAngles(0, fTotalTime*20.0f, 0);
	rootNode_->SetRotation(q);
}

