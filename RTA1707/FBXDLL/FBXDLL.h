#pragma once

#ifdef FBXDLL_EXPORTS
#define FBXDLL_API __declspec( dllexport )
#else
#define FBXDLL_API __declspec( dllimport )
#endif
#include <vector>
#include <DirectXMath.h>
struct PositionTriangle
{
	DirectX::XMFLOAT3 m_posA, m_posB, m_posC;
};
struct JointTransform
{
	DirectX::XMFLOAT4X4 m_transform;
	int m_parent;
};
namespace FBXDLL
{
	FBXDLL_API std::vector<PositionTriangle> FBX_GetBindPoseMesh( const char* const );
	FBXDLL_API std::vector<JointTransform> FBX_GetJoints( const char* const );
	FBXDLL_API bool TestFBX_PrintInfo( const char* const );
}