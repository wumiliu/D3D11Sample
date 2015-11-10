#include "Skeleton.h"

Skeleton::Skeleton():
rootBoneIndex_(M_MAX_UNSIGNED)
{
}


Skeleton::~Skeleton()
{
	delete node_;
}

void Skeleton::SetRootBoneIndex(unsigned index)
{
	if (index < bones_.size())
		rootBoneIndex_ = index;
}


void Skeleton::ClearBones()
{
	bones_.clear();
	rootBoneIndex_ = M_MAX_UNSIGNED;
}
void Skeleton::Reset()
{
	for (VEC_BONE::iterator i = bones_.begin(); i != bones_.end(); ++i)
	{
		if (i->animated_ && !i->node_)
		{
			i->node_->SetTransform(i->initialPosition_, i->initialRotation_, i->initialScale_);
		}
	}
}

void Skeleton::ResetSilent()
{
	for (VEC_BONE::iterator i = bones_.begin(); i != bones_.end(); ++i)
	{
		if (i->animated_ && !i->node_)
		{
			i->node_->SetTransformSilent(i->initialPosition_, i->initialRotation_, i->initialScale_);
		}
	}
}

Bone* Skeleton::GetRootBone()
{
	return GetBone(rootBoneIndex_);
}

Bone* Skeleton::GetBone(unsigned index)
{
	return index < bones_.size() ? &bones_[index] : (Bone*)0;
}

Bone* Skeleton::GetBone(const char* boneName)
{
	return GetBone(StringHash(boneName));
}

Bone* Skeleton::GetBone(StringHash nameHash)
{
	for (VEC_BONE::iterator i = bones_.begin(); i != bones_.end(); ++i)
	{
		if (i->nameHash_ == nameHash)
			return &(*i);
	}
	return 0;
}

/*
void Skeleton::Load(class HpSkeleton* pSkeleton)
{
	unsigned bones = pSkeleton->getNumBones();
	bones_.resize(bones);

	for (unsigned i = 0; i < bones; ++i)
	{
		HpBone* pBone = pSkeleton->getBone(i);
		Bone newBone;
		newBone.name_ = pBone->getName().c_str();
		newBone.nameHash_ = newBone.name_.c_str();
		newBone.parentIndex_ = pBone->ParentIndex;
		newBone.initialPosition_ = pBone->Translation;
		newBone.initialRotation_ = pBone->RotationQuat;
		newBone.initialScale_ = pBone->Scale;

		Matrix M;
		XMVECTOR S = XMLoadFloat3(&newBone.initialScale_);
		XMVECTOR P = XMLoadFloat3(&newBone.initialPosition_);
		XMVECTOR Q = XMLoadFloat4(&newBone.initialRotation_);
		XMVECTOR zero = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		XMStoreFloat4x4(&M, XMMatrixAffineTransformation(S, zero, Q, P));
		newBone.offsetMatrix_ = M.Invert();
	}
	SetSkeleton();
}*/

void Skeleton::SetSkeleton()
{
	VEC_BONE::iterator i = bones_.begin();
	node_ = new HpNode();
	node_->SetName("MyRoot");
	++i;

	for (; i != bones_.end(); ++i)
	{
		i->node_ = node_->CreateChild(i->name_);
	}
}
