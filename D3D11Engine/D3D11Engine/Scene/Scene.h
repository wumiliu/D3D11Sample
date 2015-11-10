#pragma once

/// Root scene node, represents the whole scene.

#include "HpD3D9Type.h"
#include "HpNode.h"



typedef HP_HashMap<unsigned, HpNode*> HP_HashMap_NODE;
typedef HP_HashMap<unsigned, HpNode*>::const_iterator  HP_HashMap_NODE_ITERATOR;


typedef HP_HashMap<unsigned, Component*> HP_HashMap_Component;
typedef HP_HashMap<unsigned, Component*>::const_iterator  HP_HashMap_Component_Iter;


class Scene : public HpNode
{
public:
	using HpNode::GetComponent;
public:
	Scene();
	~Scene();
public:

	/// Get free node ID, either non-local or local.
	unsigned GetFreeNodeID(CreateMode mode);
	/// Get free component ID, either non-local or local.
	unsigned GetFreeComponentID(CreateMode mode);

	/// Node added. Assign scene pointer and add to ID map.
	void NodeAdded(HpNode* node);
	/// Node removed. Remove from ID map.
	void NodeRemoved(HpNode* node);
	/// Return node from the whole scene by ID, or null if not found.
	HpNode* GetNode(unsigned id) const;

	/// Component added. Add to ID map.
	void ComponentAdded(Component* component);
	void ComponentRemoved(Component* component);
	/// Return component from the whole scene by ID, or null if not found.
	Component* GetComponent(unsigned id) const;

	void MarkReplicationDirty(HpNode* node);

private:
	/// Replicated scene nodes by ID.
	HP_HashMap_NODE replicatedNodes_;
	/// Local scene nodes by ID.
	HP_HashMap_NODE localNodes_;

	/// Replicated components by ID.
	HP_HashMap_Component replicatedComponents_;
	/// Local components by ID.
	HP_HashMap_Component localComponents_;

	/// Next free non-local node ID.
	unsigned replicatedNodeID_;
	/// Next free local node ID.
	unsigned localNodeID_;

	/// Next free non-local component ID.
	unsigned replicatedComponentID_;
	/// Next free local component ID.
	unsigned localComponentID_;
};

