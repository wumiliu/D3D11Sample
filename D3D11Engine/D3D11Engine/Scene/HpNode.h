#pragma once
#include "HpD3D9Type.h"
#include "StringHash.h"

typedef std::shared_ptr<class HpNode> HpNodePtr;
typedef std::weak_ptr<class HpNode> HpNodeWeakPtr;

typedef std::vector<HpNodePtr> VEC_HPNODE_PTR;

typedef std::shared_ptr<class Component> ComponentPtr;
typedef std::weak_ptr<class Component> ComponentWeakPtr;

typedef std::vector<ComponentPtr> VEC_COMPONENT_PTR;
typedef std::vector<Component*> VEC_COMPONENT_WeakPtr;




static const unsigned M_MAX_UNSIGNED = 0xffffffff;
static const unsigned FIRST_REPLICATED_ID = 0x1;
static const unsigned LAST_REPLICATED_ID = 0xffffff;
static const unsigned FIRST_LOCAL_ID = 0x01000000;
static const unsigned LAST_LOCAL_ID = 0xffffffff;

class Scene;

/// Component and child node creation mode for networking.
enum CreateMode
{
	REPLICATED = 0,
	LOCAL = 1
};

/// Transform space for translations and rotations.
enum TransformSpace
{
	TS_LOCAL = 0,
	TS_PARENT,
	TS_WORLD
};

class HpNode
{

public:
	HpNode();
	~HpNode();

	/// Create a child scene node (with specified ID if provided).
//	HpNodePtr CreateChild(const String& name , unsigned id =0);
	//HpNodePtr CreateChild(unsigned id);
	/// Create a child node with specific ID.
	HpNode* CreateChild(unsigned id, CreateMode mode);
	/// Create a child scene node (with specified ID if provided).
	HpNode* CreateChild(const String& name = "", CreateMode mode = REPLICATED, unsigned id = 0);

	void AddChild(HpNodePtr node, unsigned index = M_MAX_UNSIGNED);

	/// Mark node and child nodes to need world transform recalculation. Notify listener components.
	void MarkDirty();


	/// Return ID.
	unsigned GetID() const { return id_; }

	/// Return name.
	const String& GetName() const { return name_; }

	/// Return name hash.
	StringHash GetNameHash() const { return nameHash_; }

	/// Return parent scene node.
	HpNode* GetParent() const { return parent_; }

	/// Return scene.
	Scene* GetScene() const { return scene_; }


	void SetName(const String& name);
	void SetPosition(const Vector3& position);
	void SetDirection(const Vector3& direction);
	/// Set rotation in parent space.
	void SetRotation(const Quaternion& rotation);


	/// Move the scene node in the chosen transform space.
	void Translate(const Vector3& delta, TransformSpace space = TS_LOCAL);

	/// Rotate the scene node in the chosen transform space.
	void Rotate(const Quaternion& delta, TransformSpace space = TS_LOCAL);

	/// Rotate around the X axis.
	void Pitch(float angle, TransformSpace space = TS_LOCAL);
	/// Rotate around the Y axis.
	void Yaw(float angle, TransformSpace space = TS_LOCAL);
	/// Rotate around the Z axis.
	void Roll(float angle, TransformSpace space = TS_LOCAL);
	/// Look at a target position in the chosen transform space. Note that the up vector is always specified in world space. Return true if successful, or false if resulted in an illegal rotation, in which case the current rotation remains.
	bool LookAt(const Vector3& target, const Vector3& up = Vector3::Up, TransformSpace space = TS_WORLD);

	/// Set uniform scale in parent space.
	void SetScale(float scale);
	/// Set scale in parent space.
	void SetScale(const Vector3& scale);

	/// Set position in world space.
	void SetWorldPosition(const Vector3& position);

	/// Set rotation in world space.
	void SetWorldRotation(const Quaternion& rotation);

	/// Set uniform scale in world space.
	void SetWorldScale(const Vector3& scale);

	void SetTransform(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

	/// Return world space transform matrix.
	const Matrix& GetWorldTransform() const
	{
		if (dirty_)
			UpdateWorldTransform();

		return worldTransform_;
	}
	/// Return rotation in world space.
	Quaternion GetWorldRotation() const
	{
		if (dirty_)
			UpdateWorldTransform();

		return worldRotation_;
	}

	void UpdateWorldTransform()const;

	/// Return parent space transform matrix.
	Matrix GetTransform() const;


	/// Return position in world space.
	Vector3 GetWorldPosition() const
	{
		if (dirty_)
			UpdateWorldTransform();
		return worldTransform_.Translation();
	}
	/// Return scale in world space.
	Vector3 GetWorldScale() const
	{
		if (dirty_)
			UpdateWorldTransform();

		return worldTransform_.Scale();
	}
	/// Set position in parent space silently without marking the node & child nodes dirty. Used by animation code.
	void SetPositionSilent(const Vector3& position) { position_ = position; }

	/// Set position in parent space silently without marking the node & child nodes dirty. Used by animation code.
	void SetRotationSilent(const Quaternion& rotation) { rotation_ = rotation; }

	/// Set scale in parent space silently without marking the node & child nodes dirty. Used by animation code.
	void SetScaleSilent(const Vector3& scale) { scale_ = scale; }

	/// Set local transform silently without marking the node & child nodes dirty. Used by animation code.
	void SetTransformSilent(const Vector3& position, const Quaternion& rotation, const Vector3& scale);

	/// Return immediate child scene nodes.
	const VEC_HPNODE_PTR& GetChildren() const { return children_; }
	int GetNumChildren() const{ return children_.size(); }

	/// Return child scene node by index.
	HpNode* GetChild(unsigned index) const;
	/// Return child scene node by name.
	HpNode* GetChild(const String& name, bool recursive = false) const;
	/// Return child scene node by name.
	HpNode* GetChild(const char* name, bool recursive = false) const;
	/// Return child scene node by name hash.
	HpNode* GetChild(StringHash nameHash, bool recursive = false) const;


	void RemoveChild(HpNode* pNode);

	/// Remove all child scene nodes.
	void RemoveAllChildren();
	/// Remove child scene nodes that match criteria.
	void RemoveChildren(bool removeReplicated, bool removeLocal, bool recursive);
	/// Remove child node by iterator.
	void RemoveChild(VEC_HPNODE_PTR::iterator iter);


	/// Return component by type. If there are several, returns the first.
	Component* GetComponent(StringHash type, bool recursive = false) const;

	/// Template version of creating a component.
	template <class T> T* CreateComponent(CreateMode mode = REPLICATED, unsigned id = 0);
	/// Template version of returning a component by type.
	template <class T> T* GetComponent(bool recursive = false) const;

	/// Add a pre-created component.
	void AddComponent(class Component* component, unsigned id, CreateMode mode);

	/// Remove all components from this node.
	void RemoveAllComponents();
	/// Remove components that match criteria.
	void RemoveComponents(bool removeReplicated, bool removeLocal);

	/// Remove a component from this node.
	void RemoveComponent(Component* component);
	/// Remove the first component of specific type from this node.
	void RemoveComponent(StringHash type);
	/// Remove a component from this node with the specified iterator.
	void RemoveComponent(VEC_COMPONENT_PTR::iterator i);


	/// Add listener component that is notified of node being dirtied. Can either be in the same node or another.
	void AddListener(Component* component);

	/// Mark node dirty in scene replication states.
	void MarkReplicationDirty();
private:

public:
	/// Set ID. Called by Scene.
	void SetID(unsigned id);
	/// Set scene. Called by Scene.
	void SetScene(Scene* scene);
	/// Reset scene, ID and owner. Called by Scene.
	void ResetScene();
private:
	/// World-space transform matrix.
	mutable Matrix worldTransform_;
	mutable Quaternion worldRotation_;

	/// World transform needs update flag.
	mutable bool dirty_;
	/// Parent scene node.
	HpNode* parent_;
	/// Scene (root node.)
	Scene* scene_;
	/// Unique ID within the scene.
	unsigned id_;
	/// Position.
	Vector3 position_;
	/// Rotation.
	Quaternion rotation_;
	/// Scale.
	Vector3 scale_;

	/// Name.
	String name_;
	/// Name hash.
	StringHash nameHash_;

	VEC_HPNODE_PTR children_;
	/// Components.
	VEC_COMPONENT_PTR components_;
	VEC_COMPONENT_WeakPtr  listeners_;

};

template <class T>
T* HpNode::GetComponent(bool recursive /*= false*/) const
{
	return static_cast<T*>(GetComponent(T::GetTypeStatic(), recursive));
}

template <class T>
T* HpNode::CreateComponent(CreateMode mode /*= REPLICATED*/, unsigned id /*= 0*/)
{
	if (id_ >= FIRST_LOCAL_ID && mode == REPLICATED)
		mode = LOCAL;
	Component* newComponent = static_cast<Component*>(new T);
	AddComponent(newComponent, id, mode);
	return static_cast<T*>(newComponent);
}

