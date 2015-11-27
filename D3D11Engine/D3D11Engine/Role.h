#pragma once
#include "HpD3D9Type.h"
#include "Framework/GameObject.h"
class Role
{
public:
	Role();
	~Role();
	void Init(std::shared_ptr<class Scene> scene_);
	void Render(Matrix view, Matrix proj);
	virtual void UpdateScene(float fTotalTime, float fDeltaTime);

protected:
	void CreateRagdollBone(const String& boneName, const Vector3& size, const Vector3& position, const Quaternion& rotation);
private:
	GameObject gameObject;
	class HpNode* rootNode_;


};

