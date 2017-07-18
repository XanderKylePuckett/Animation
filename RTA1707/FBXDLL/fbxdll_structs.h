#pragma once
#include <vector>
#include <DirectXMath.h>
struct PositionUvTriangle
{
	DirectX::XMFLOAT3 m_posA, m_posB, m_posC;
	DirectX::XMFLOAT2 m_uvA, m_uvB, m_uvC;
};
struct JointTransform
{
	DirectX::XMFLOAT4X4 m_transform;
	int m_parent;
};
struct Keyframe
{
	std::vector<JointTransform> m_joints;
	double m_time;
};
struct AnimClip
{
	std::vector<Keyframe> m_frames;
	double m_duration;
};