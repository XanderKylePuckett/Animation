#pragma once
#include <d3d11.h>
#include "fbxdll_structs.h"
namespace Renderer
{
	struct RGBAColor
	{
		union
		{
			struct
			{
				DirectX::XMFLOAT4 m_rgba;
			};
			struct
			{
				float m_channels[ 4 ];
			};
			struct
			{
				float m_red, m_green, m_blue, m_alpha;
			};
		};
		RGBAColor( void );
		RGBAColor( float, float, float, float = 1.0f );
		static const RGBAColor Red, Green, Blue, Cyan, Magenta, Yellow, Black, White;
	};

	struct PositionColorVertex
	{
		DirectX::XMFLOAT4 m_position;
		DirectX::XMFLOAT4 m_color;
		DirectX::XMFLOAT4 m_weights;
		DirectX::XMINT4 m_indices;
		PositionColorVertex( void );
		PositionColorVertex( float, float, float, const Renderer::RGBAColor& = Renderer::RGBAColor::White );
		PositionColorVertex( float _x, float _y, float _z, float _u, float _v );
	};

	struct ModelViewProjection
	{
		DirectX::XMFLOAT4X4 m_model;
		DirectX::XMFLOAT4X4 m_view;
		DirectX::XMFLOAT4X4 m_projection;
		DirectX::XMFLOAT4X4 m_joints[ 64u ];
	};

	struct Camera
	{
		DirectX::XMFLOAT4X4 m_cameraTransform;
		Camera( void );
		void TranslateCamera( float, float, float );
		void RotateCamera( float, float );
		DirectX::XMMATRIX GetViewMatrix( void ) const;
		void Update( float );
	};

	struct PipelineState
	{
		ID3D11InputLayout* m_inputLayout;
		ID3D11VertexShader* m_vertexShader;
		ID3D11PixelShader* m_pixelShader;
		ID3D11RenderTargetView* m_renderTargetView;
		ID3D11Texture2D* m_depthStencilBuffer;
		ID3D11DepthStencilState* m_depthStencilState;
		ID3D11DepthStencilView* m_depthStencilView;
		ID3D11RasterizerState* m_rasterizerState;
	};

	struct Triangle
	{
		union
		{
			struct
			{
				Renderer::PositionColorVertex m_vertices[ 3u ];
			};
			struct
			{
				Renderer::PositionColorVertex m_vertexA;
				Renderer::PositionColorVertex m_vertexB;
				Renderer::PositionColorVertex m_vertexC;
			};
		};
		Triangle( void );
		Triangle( const Renderer::PositionColorVertex&,
				  const Renderer::PositionColorVertex&,
				  const Renderer::PositionColorVertex& );
		Triangle( const Renderer::Triangle& );
		Triangle& operator=( const Renderer::Triangle& );
	};

	class TriangleMesh
	{
	private:
		Renderer::Triangle* m_triangles;
		unsigned int m_numTriangles, m_arrSize;
	public:
		TriangleMesh( void );
		TriangleMesh( const Renderer::TriangleMesh& );
		TriangleMesh( Renderer::TriangleMesh&& );
		Renderer::TriangleMesh& operator=( const Renderer::TriangleMesh& );
		Renderer::TriangleMesh& operator=( Renderer::TriangleMesh&& );
		~TriangleMesh( void );
		void InitSize( unsigned int );
		void AddTriangle( const Renderer::Triangle& );
		void Clear( void );
		const Renderer::Triangle* GetTriangles( void ) const;
		unsigned int GetNumTriangles( void ) const;
		DirectX::XMFLOAT4X4* m_joints = nullptr;
		DirectX::XMFLOAT4X4* m_invBindJoints = nullptr;
		int m_numJoints = 0u;
	};
}

template <typename T>
void ExtendDynArray( T*& _arr, unsigned int& _size )
{
	if ( 0u == _size )
	{
		delete[ ] _arr;
		_arr = new T[ _size = 1u ];
	}
	else
	{
		T* const newArr_ = new T[ _size << 1 ];
		for ( unsigned int i = 0u; i < _size; ++i )
			newArr_[ i ] = _arr[ i ];
		delete[ ] _arr;
		_arr = newArr_;
		_size <<= 1;
	}
}