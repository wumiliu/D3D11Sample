#pragma once

#if defined(_XBOX_ONE) && defined(_TITLE)
#include <d3d11_x.h>
#else
#include <d3d11_1.h>
#endif

#include <DirectXMath.h>

namespace DirectX
{
	struct VertexPositionNormalTangentUTexC
	{
		VertexPositionNormalTangentUTexC()
		{ }
		XMFLOAT3 Position;
		XMFLOAT3 Normal;
		XMFLOAT3 TangentU;
		XMFLOAT2 TexC;

		static const int InputElementCount = 4;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};

	// Vertex struct holding position, color, and texture mapping information.
	struct VertexPositionColorTexture
	{
		VertexPositionColorTexture()
		{ }

		VertexPositionColorTexture(XMFLOAT3 const& position, XMFLOAT4 const& color, XMFLOAT2 const& textureCoordinate)
			: position(position),
			color(color),
			textureCoordinate(textureCoordinate)
		{ }

		VertexPositionColorTexture(FXMVECTOR position, FXMVECTOR color, FXMVECTOR textureCoordinate)
		{
			XMStoreFloat3(&this->position, position);
			XMStoreFloat4(&this->color, color);
			XMStoreFloat2(&this->textureCoordinate, textureCoordinate);
		}

		XMFLOAT3 position;
		XMFLOAT4 color;
		XMFLOAT2 textureCoordinate;

		static const int InputElementCount = 3;
		static const D3D11_INPUT_ELEMENT_DESC InputElements[InputElementCount];
	};

}