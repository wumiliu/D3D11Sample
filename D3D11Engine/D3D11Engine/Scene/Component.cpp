#include "Component.h"
#include "HpNode.h"

Component::Component():
node_(0),
id_(0),
enabled_(true)
{

}


Component::~Component()
{
}

void Component::SetNode(HpNode* node)
{
	node_ = node;
	OnNodeSet(node_);
}

void Component::OnNodeSet(HpNode* node)
{

}

void Component::OnSceneSet(Scene* scene)
{

}

void Component::OnMarkedDirty(HpNode* node)
{

}

Component* Component::GetComponent(StringHash type) const
{
	return node_ ? node_->GetComponent(type) : 0;
}

Scene* Component::GetScene() const
{
	return node_ ? node_->GetScene() : 0;
}

void Component::SetEnabled(bool enable)
{
	if (enable != enabled_)
	{
		enabled_ = enable;
		OnSetEnabled();
	
		// Send change event for the component
		Scene* scene = GetScene();
		if (scene)
		{
		}
	}
}

void Component::Remove()
{
	if (node_)
		node_->RemoveComponent(this);
}




