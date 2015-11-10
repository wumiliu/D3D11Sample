#include "Scene.h"
#include "Component.h"

Scene::Scene():
replicatedNodeID_(FIRST_REPLICATED_ID),
localNodeID_(FIRST_LOCAL_ID)
{
	// Assign an ID to self so that nodes can refer to this node as a parent
	SetID(GetFreeNodeID(REPLICATED));
	NodeAdded(this);
}


Scene::~Scene()
{
	// Remove root-level components first, so that scene subsystems such as the octree destroy themselves. This will speed up
	// the removal of child nodes' components
	RemoveAllComponents();
	RemoveAllChildren();

	// Remove scene reference and owner from all nodes that still exist
	for (HP_HashMap_NODE_ITERATOR i = replicatedNodes_.begin(); i != replicatedNodes_.end(); ++i)
		i->second->ResetScene();
	for (HP_HashMap_NODE_ITERATOR i = localNodes_.begin(); i != localNodes_.end(); ++i)
		i->second->ResetScene();

}

unsigned Scene::GetFreeNodeID(CreateMode mode)
{
	if (mode == REPLICATED)
	{
		for (;;)
		{
			unsigned ret = replicatedNodeID_;
			if (replicatedNodeID_ < LAST_REPLICATED_ID)
				++replicatedNodeID_;
			else
				replicatedNodeID_ = FIRST_REPLICATED_ID;

			if (replicatedNodes_.find(ret) == replicatedNodes_.end())
				return ret;
		}
	}
	else
	{
		for (;;)
		{
			unsigned ret = localNodeID_;
			if (localNodeID_ < LAST_LOCAL_ID)
				++localNodeID_;
			else
				localNodeID_ = FIRST_LOCAL_ID;
			if (localNodes_.find(ret) == localNodes_.end())
				return ret;
		}
	}
}

unsigned Scene::GetFreeComponentID(CreateMode mode)
{
	if (mode == REPLICATED)
	{
		for (;;)
		{
			unsigned ret = replicatedComponentID_;
			if (replicatedComponentID_ < LAST_REPLICATED_ID)
				++replicatedNodeID_;
			else
				replicatedComponentID_ = FIRST_REPLICATED_ID;

			if (replicatedComponents_.find(ret) == replicatedComponents_.end())
				return ret;
		}
	}
	else
	{
		for (;;)
		{
			unsigned ret = localComponentID_;
			if (localComponentID_ < LAST_LOCAL_ID)
				++localComponentID_;
			else
				localComponentID_ = FIRST_LOCAL_ID;
			if (localComponents_.find(ret) == localComponents_.end())
				return ret;
		}
	}
}

void Scene::NodeAdded(HpNode* node)
{
	if (!node || node->GetScene() == this)
		return;
	// Remove from old scene first
	Scene* oldScene = node->GetScene();
	if (oldScene)
		oldScene->NodeRemoved(node);

	node->SetScene(this);
	// If the new node has an ID of zero (default), assign a replicated ID now
	unsigned id = node->GetID();
	if (!id)
	{
		id = GetFreeNodeID(REPLICATED);
		node->SetID(id);
	}
	// If node with same ID exists, remove the scene reference from it and overwrite with the new node
	if (id < FIRST_LOCAL_ID)
	{
		HP_HashMap_NODE_ITERATOR iter = replicatedNodes_.find(id);
		if (iter != replicatedNodes_.end() && iter->second != node)
		{
			NodeRemoved(iter->second);
		}
		replicatedNodes_[id] = node;
		MarkReplicationDirty(node);
	}
	else
	{
		HP_HashMap_NODE_ITERATOR  iter = localNodes_.find(id);
		if (iter != localNodes_.end() && iter->second != node)
		{
			NodeRemoved(iter->second);
		}
		localNodes_[id] = node;
	}

	// Add already created components and child nodes now
	const VEC_HPNODE_PTR & children = node->GetChildren();
	VEC_HPNODE_PTR::const_iterator iter = children.begin();
	for (; iter != children.end(); ++iter)
		NodeAdded((*iter).get());

}

void Scene::NodeRemoved(HpNode* node)
{
	if (!node || node->GetScene() != this)
		return;
	unsigned id = node->GetID();
	if (id < FIRST_LOCAL_ID)
	{
		HP_HashMap_NODE_ITERATOR iter = replicatedNodes_.find(id);
		if (iter != replicatedNodes_.end())
		{
			replicatedNodes_.erase(iter);
		}
		MarkReplicationDirty(node);
	}
	else
	{
		HP_HashMap_NODE_ITERATOR iter = localNodes_.find(id);
		if (iter != localNodes_.end())
		{
			localNodes_.erase(iter);
		}
	}
}
void Scene::MarkReplicationDirty(HpNode* node)
{
	unsigned id = node->GetID();

	if (id < FIRST_LOCAL_ID)
	{
	}
}

HpNode* Scene::GetNode(unsigned id) const
{
	if (id < FIRST_LOCAL_ID)
	{
		HP_HashMap_NODE_ITERATOR i = replicatedNodes_.find(id);
		return i != replicatedNodes_.end() ? i->second : 0;
	}
	else
	{
		HP_HashMap_NODE_ITERATOR i = localNodes_.find(id);
		return i != localNodes_.end() ? i->second : 0;
	}
}

void Scene::ComponentAdded(Component* component)
{
	if (!component)
		return;

	unsigned id = component->GetID();

	// If the new component has an ID of zero (default), assign a replicated ID now
	if (!id)
	{
		id = GetFreeComponentID(REPLICATED);
		component->SetID(id);
	}

	if (id < FIRST_LOCAL_ID)
	{
		HP_HashMap_Component_Iter i = replicatedComponents_.find(id);
		if (i != replicatedComponents_.end() && i->second!= component)
		{
			ComponentRemoved(i->second);
		}

		replicatedComponents_[id] = component;
	}
	else
	{
		HP_HashMap_Component_Iter i = localComponents_.find(id);
		if (i != localComponents_.end() && i->second!= component)
		{
			ComponentRemoved(i->second);
		}

		localComponents_[id] = component;
	}

	component->OnSceneSet(this);
}

void Scene::ComponentRemoved(Component* component)
{

}

Component* Scene::GetComponent(unsigned id) const
{

	if (id < FIRST_LOCAL_ID)
	{
		HP_HashMap_Component_Iter i = replicatedComponents_.find(id);
		return i != replicatedComponents_.end() ? i->second : 0;
	}
	else
	{
		HP_HashMap_Component_Iter i = localComponents_.find(id);
		return i != localComponents_.end() ? i->second : 0;
	}
}
