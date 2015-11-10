#pragma once
#include "HpD3D9Type.h"
#include "HpNode.h"
#include "StringHash.h"


/// %Bone in a skeleton.
struct Bone
{
	/// Construct with defaults.
	Bone() :
		parentIndex_(0),
		initialPosition_(Vector3::Zero),
		initialRotation_(Quaternion::Identity),
		initialScale_(Vector3::One),
		animated_(true)
	{
	}
	/// Bone name.
	String name_;
	/// Bone name hash.
	StringHash nameHash_;
	/// Parent bone index.
	unsigned parentIndex_;
	/// Reset position. (世界矩阵)
	Vector3 initialPosition_;
	/// Reset rotation.
	Quaternion initialRotation_;
	/// Reset scale.
	Vector3 initialScale_;

	/// Offset matrix.（世界矩阵的逆矩阵） 从世界坐标系到模型坐标系的转换
	Matrix offsetMatrix_;
	/// Animation enable flag.
	bool animated_;
	/// Scene node.
	HpNode* node_;

};
typedef std::vector<Bone> VEC_BONE;
class Skeleton
{
public:
	Skeleton();
	~Skeleton();
	/// Set root bone's index.
	void SetRootBoneIndex(unsigned index);

	/// Clear bones.
	void ClearBones();
	/// Reset all animating bones to initial positions.
	void Reset();
	/// Reset all animating bones to initial positions without marking the nodes dirty. Requires the node dirtying to be performed later.
	void ResetSilent();

	/// Return all bones.
	const VEC_BONE& GetBones() const { return bones_; }

	/// Return modifiable bones.
	VEC_BONE& GetModifiableBones() { return bones_; }

	/// Return number of bones.
	unsigned int GetNumBones() const { return bones_.size(); }

	/// Return root bone.
	Bone* GetRootBone();

	/// Return bone by index.
	Bone* GetBone(unsigned index);

	/// Return bone by name.
	Bone* GetBone(const char* boneName);
	Bone* GetBone(StringHash boneNameHash);

	//void Load(class HpSkeleton* pSkeleton);
	void SetSkeleton();
private:
	/// Bones.
	VEC_BONE bones_;
	/// Root bone index.
	unsigned rootBoneIndex_;

	/// Scene node.
	HpNode* node_;
};

