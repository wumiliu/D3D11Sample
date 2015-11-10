#include "GeometryGens.h"

namespace GeoGen
{
	void CreateBox(float width, float height, float depth, MeshData &mesh)
	{
		mesh.vertices.clear();
		mesh.indices.clear();

		//24 vertices
		mesh.vertices.resize(24);
		//36 indices
		mesh.indices.resize(36);

		float halfW = width * 0.5f;
		float halfH = height * 0.5f;
		float halfD = depth * 0.5f;

		//front
		mesh.vertices[0].pos = XMFLOAT3(-halfW,-halfH,-halfD);
		mesh.vertices[0].normal = XMFLOAT3(0.f,0.f,-1.f);
		mesh.vertices[0].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[0].tex = XMFLOAT2(0.f,1.f);
		mesh.vertices[1].pos = XMFLOAT3(-halfW,halfH,-halfD);
		mesh.vertices[1].normal = XMFLOAT3(0.f,0.f,-1.f);
		mesh.vertices[1].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[1].tex = XMFLOAT2(0.f,0.f);
		mesh.vertices[2].pos = XMFLOAT3(halfW,halfH,-halfD);
		mesh.vertices[2].normal = XMFLOAT3(0.f,0.f,-1.f);
		mesh.vertices[2].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[2].tex = XMFLOAT2(1.f,0.f);
		mesh.vertices[3].pos = XMFLOAT3(halfW,-halfH,-halfD);
		mesh.vertices[3].normal = XMFLOAT3(0.f,0.f,-1.f);
		mesh.vertices[3].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[3].tex = XMFLOAT2(1.f,1.f);
		//left
		mesh.vertices[4].pos = XMFLOAT3(-halfW,-halfH,halfD);
		mesh.vertices[4].normal = XMFLOAT3(-1.f,0.f,0.f);
		mesh.vertices[4].tangent = XMFLOAT3(0.f,0.f,-1.f);
		mesh.vertices[4].tex = XMFLOAT2(0.f,1.f);
		mesh.vertices[5].pos = XMFLOAT3(-halfW,halfH,halfD);
		mesh.vertices[5].normal = XMFLOAT3(-1.f,0.f,0.f);
		mesh.vertices[5].tangent = XMFLOAT3(0.f,0.f,-1.f);
		mesh.vertices[5].tex = XMFLOAT2(0.f,0.f);
		mesh.vertices[6].pos = XMFLOAT3(-halfW,halfH,-halfD);
		mesh.vertices[6].normal = XMFLOAT3(-1.f,0.f,0.f);
		mesh.vertices[6].tangent = XMFLOAT3(0.f,0.f,-1.f);
		mesh.vertices[6].tex = XMFLOAT2(1.f,0.f);
		mesh.vertices[7].pos = XMFLOAT3(-halfW,-halfH,-halfD);
		mesh.vertices[7].normal = XMFLOAT3(-1.f,0.f,0.f);
		mesh.vertices[7].tangent = XMFLOAT3(0.f,0.f,-1.f);
		mesh.vertices[7].tex = XMFLOAT2(1.f,1.f);
		//back
		mesh.vertices[8].pos = XMFLOAT3(halfW,-halfH,halfD);
		mesh.vertices[8].normal = XMFLOAT3(0.f,0.f,1.f);
		mesh.vertices[8].tangent = XMFLOAT3(-1.f,0.f,0.f);
		mesh.vertices[8].tex = XMFLOAT2(0.f,1.f);
		mesh.vertices[9].pos = XMFLOAT3(halfW,halfH,halfD);
		mesh.vertices[9].normal = XMFLOAT3(0.f,0.f,1.f);
		mesh.vertices[9].tangent = XMFLOAT3(-1.f,0.f,0.f);
		mesh.vertices[9].tex = XMFLOAT2(0.f,0.f);
		mesh.vertices[10].pos = XMFLOAT3(-halfW,halfH,halfD);
		mesh.vertices[10].normal = XMFLOAT3(0.f,0.f,1.f);
		mesh.vertices[10].tangent = XMFLOAT3(-1.f,0.f,0.f);
		mesh.vertices[10].tex = XMFLOAT2(1.f,0.f);
		mesh.vertices[11].pos = XMFLOAT3(-halfW,-halfH,halfD);
		mesh.vertices[11].normal = XMFLOAT3(0.f,0.f,1.f);
		mesh.vertices[11].tangent = XMFLOAT3(-1.f,0.f,0.f);
		mesh.vertices[11].tex = XMFLOAT2(1.f,1.f);
		//right
		mesh.vertices[12].pos = XMFLOAT3(halfW,-halfH,-halfD);
		mesh.vertices[12].normal = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[12].tangent = XMFLOAT3(0.f,0.f,1.f);
		mesh.vertices[12].tex = XMFLOAT2(0.f,1.f);
		mesh.vertices[13].pos = XMFLOAT3(halfW,halfH,-halfD);
		mesh.vertices[13].normal = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[13].tangent = XMFLOAT3(0.f,0.f,1.f);
		mesh.vertices[13].tex = XMFLOAT2(0.f,0.f);
		mesh.vertices[14].pos = XMFLOAT3(halfW,halfH,halfD);
		mesh.vertices[14].normal = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[14].tangent = XMFLOAT3(0.f,0.f,1.f);
		mesh.vertices[14].tex = XMFLOAT2(1.f,0.f);
		mesh.vertices[15].pos = XMFLOAT3(halfW,-halfH,halfD);
		mesh.vertices[15].normal = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[15].tangent = XMFLOAT3(0.f,0.f,1.f);
		mesh.vertices[15].tex = XMFLOAT2(1.f,1.f);
		//top
		mesh.vertices[16].pos = XMFLOAT3(-halfW,halfH,-halfD);
		mesh.vertices[16].normal = XMFLOAT3(0.f,1.f,0.f);
		mesh.vertices[16].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[16].tex = XMFLOAT2(0.f,1.f);
		mesh.vertices[17].pos = XMFLOAT3(-halfW,halfH,halfD);
		mesh.vertices[17].normal = XMFLOAT3(0.f,1.f,0.f);
		mesh.vertices[17].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[17].tex = XMFLOAT2(0.f,0.f);
		mesh.vertices[18].pos = XMFLOAT3(halfW,halfH,halfD);
		mesh.vertices[18].normal = XMFLOAT3(0.f,1.f,0.f);
		mesh.vertices[18].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[18].tex = XMFLOAT2(1.f,0.f);
		mesh.vertices[19].pos = XMFLOAT3(halfW,halfH,-halfD);
		mesh.vertices[19].normal = XMFLOAT3(0.f,1.f,0.f);
		mesh.vertices[19].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[19].tex = XMFLOAT2(1.f,1.f);
		//bottom
		mesh.vertices[20].pos = XMFLOAT3(-halfW,-halfH,halfD);
		mesh.vertices[20].normal = XMFLOAT3(0.f,-1.f,0.f);
		mesh.vertices[20].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[20].tex = XMFLOAT2(0.f,1.f);
		mesh.vertices[21].pos = XMFLOAT3(-halfW,-halfH,-halfD);
		mesh.vertices[21].normal = XMFLOAT3(0.f,-1.f,0.f);
		mesh.vertices[21].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[21].tex = XMFLOAT2(0.f,0.f);
		mesh.vertices[22].pos = XMFLOAT3(halfW,-halfH,-halfD);
		mesh.vertices[22].normal = XMFLOAT3(0.f,-1.f,0.f);
		mesh.vertices[22].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[22].tex = XMFLOAT2(1.f,0.f);
		mesh.vertices[23].pos = XMFLOAT3(halfW,-halfH,halfD);
		mesh.vertices[23].normal = XMFLOAT3(0.f,-1.f,0.f);
		mesh.vertices[23].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[23].tex = XMFLOAT2(1.f,1.f);
		
		//Construct index
		mesh.indices[0] = 0;
		mesh.indices[1] = 1;
		mesh.indices[2] = 2;
		mesh.indices[3] = 0;
		mesh.indices[4] = 2;
		mesh.indices[5] = 3;
		
		mesh.indices[6] = 4;
		mesh.indices[7] = 5;
		mesh.indices[8] = 6;
		mesh.indices[9] = 4;
		mesh.indices[10] = 6;
		mesh.indices[11] = 7;
		
		mesh.indices[12] = 8;
		mesh.indices[13] = 9;
		mesh.indices[14] = 10;
		mesh.indices[15] = 8;
		mesh.indices[16] = 10;
		mesh.indices[17] = 11;
		
		mesh.indices[18] = 12;
		mesh.indices[19] = 13;
		mesh.indices[20] = 14;
		mesh.indices[21] = 12;
		mesh.indices[22] = 14;
		mesh.indices[23] = 15;
		
		mesh.indices[24] = 16;
		mesh.indices[25] = 17;
		mesh.indices[26] = 18;
		mesh.indices[27] = 16;
		mesh.indices[28] = 18;
		mesh.indices[29] = 19;
		
		mesh.indices[30] = 20;
		mesh.indices[31] = 21;
		mesh.indices[32] = 22;
		mesh.indices[33] = 20;
		mesh.indices[34] = 22;
		mesh.indices[35] = 23;
	}

	void CreateGrid(float width, float height, UINT m, UINT n, MeshData &mesh)
	{
		mesh.vertices.clear();
		mesh.indices.clear();
		
		UINT nVertsRow = m + 1;
		UINT nVertsCol = n + 1;
		
		//Start coordinates: oX, oZ
		float oX = -width * 0.5f;
		float oZ = height * 0.5f;
		
		float dx = width / m;
		float dz = height /n;
		//texture coordinate delta
		float dxTex = 1.f / m;
		float dyTex = 1.f /n;

		//Vertex number:nVertsRow * nVertsCol
		mesh.vertices.resize(nVertsRow * nVertsCol);

		for(UINT i=0; i<nVertsCol; ++i)
		{
			float tmpZ = oZ - dz * i;
			for(UINT j=0; j<nVertsRow; ++j)
			{
				UINT index = nVertsRow * i + j;
				mesh.vertices[index].pos.x = oX + dx * j;
				mesh.vertices[index].pos.y = 0.f;
				mesh.vertices[index].pos.z = tmpZ;

				mesh.vertices[index].normal = XMFLOAT3(0.f,1.f,0.f);
				mesh.vertices[index].tangent = XMFLOAT3(1.f,0.f,0.f);
				
				mesh.vertices[index].tex = XMFLOAT2(dxTex*j,dyTex*i);
			}
		}

		//Total grid number: m*n
		UINT nIndices = m * n * 6;
		mesh.indices.resize(nIndices);
		UINT tmp = 0;
		for(UINT i=0; i<n; ++i)
		{
			for(UINT j=0; j<m; ++j)
			{
				mesh.indices[tmp] = i * nVertsRow + j;
				mesh.indices[tmp+1] = i * nVertsRow + j + 1;
				mesh.indices[tmp+2] = (i + 1) * nVertsRow + j;
				mesh.indices[tmp+3] = i * nVertsRow + j + 1;
				mesh.indices[tmp+4] = (i + 1) * nVertsRow + j + 1;
				mesh.indices[tmp+5] = (i + 1) * nVertsRow + j;
				
				tmp += 6;
			}
		}
	}

	void CreateCylinder(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh)
	{
		mesh.vertices.clear();
		mesh.indices.clear();
		
		//radius delta for each stack: dRadius
		float dRadius = (bottomRadius - topRadius) / stack;
		//height delta for each stack
		float dHeight = height / stack;

		//Vertex number in each row
		int vertsPerRow = slice + 1;
		//Number of rows
		int nRows = stack + 1;

		//Total vertex number
		int nVerts = vertsPerRow * nRows;
		//total index number
		int nIndices = slice * stack * 6;

		mesh.vertices.resize(nVerts);
		mesh.indices.resize(nIndices);

		float topY = height * 0.5f;

		for(int i=0; i<nRows; ++i)
		{
			float tmpY = topY - dHeight * i;
			float tmpRadius = topRadius + i * dRadius;

			for(int j=0; j<vertsPerRow; ++j)
			{
				float theta = XM_2PI * j / slice;
				int index = i * vertsPerRow + j;
				mesh.vertices[index].pos = XMFLOAT3(tmpRadius*cos(theta),tmpY,tmpRadius*sin(theta));
				XMVECTOR N = XMVectorSet(cos(theta),(bottomRadius-topRadius)/height,sin(theta),0.f);
				//Normal
				XMStoreFloat3(&(mesh.vertices[index].normal),XMVector3Normalize(N));
				//Tangent
				mesh.vertices[index].tangent = XMFLOAT3(-sin(theta),0.f,cos(theta));
				//Texcoord
				mesh.vertices[index].tex = XMFLOAT2(1.f*j/slice,1.f*i/stack);
			}
		}

		UINT tmp(0);
		for(int i=0; i<stack; ++i)
		{
			for(int j=0; j<slice; ++j)
			{
				mesh.indices[tmp] = i * vertsPerRow + j;
				mesh.indices[tmp+1] = (i + 1) * vertsPerRow + j + 1;
				mesh.indices[tmp+2] = (i + 1) * vertsPerRow + j;
				mesh.indices[tmp+3] = i * vertsPerRow + j;
				mesh.indices[tmp+4] = i * vertsPerRow + j + 1;
				mesh.indices[tmp+5] = (i + 1) * vertsPerRow + j + 1;

				tmp += 6;
			}
		}
	}

	void AddCylinderTopCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh)
	{
		UINT start = mesh.vertices.size();

		for(int i=0; i<slice+1; ++i)
		{
			float theta = XM_2PI * i / slice;

			float x = topRadius*cosf(theta);
			float y = height * 0.5f;
			float z = topRadius*sinf(theta);

			float u = x/height + 0.5f;
			float v = z/height + 0.5f;

			mesh.vertices.push_back(Vertex(XMFLOAT3(x,y,z),XMFLOAT3(0.f,1.f,0.f),XMFLOAT3(1.f,0.f,0.f),XMFLOAT2(u,v)));
		}

		mesh.vertices.push_back(Vertex(XMFLOAT3(0.f,height*0.5f,0.f),XMFLOAT3(0.f,1.f,0.f),XMFLOAT3(1.f,0.f,0.f),XMFLOAT2(0.5f,0.5f)));

		UINT center = mesh.vertices.size() - 1;
		for(int i=0; i<slice; ++i)
		{
			mesh.indices.push_back(center);
			mesh.indices.push_back(start+i+1);
			mesh.indices.push_back(start+i);
		}
	}

	void AddCylinderBottomCap(float topRadius, float bottomRadius, float height, int slice, int stack, MeshData &mesh)
	{
		UINT start = mesh.vertices.size();

		for(int i=0; i<slice+1; ++i)
		{
			float theta = XM_2PI * i / slice;

			float x = bottomRadius*cosf(theta);
			float y = -height * 0.5f;
			float z = bottomRadius*sinf(theta);

			float u = x/height + 0.5f;
			float v = z/height + 0.5f;

			mesh.vertices.push_back(Vertex(XMFLOAT3(x,y,z),XMFLOAT3(0.f,-1.f,0.f),XMFLOAT3(1.f,0.f,0.f),XMFLOAT2(u,v)));
		}

		mesh.vertices.push_back(Vertex(XMFLOAT3(0.f,-height*0.5f,0.f),XMFLOAT3(0.f,-1.f,0.f),XMFLOAT3(1.f,0.f,0.f),XMFLOAT2(0.5f,0.5f)));

		UINT center = mesh.vertices.size() - 1;
		for(int i=0; i<slice; ++i)
		{
			mesh.indices.push_back(center);
			mesh.indices.push_back(start+i);
			mesh.indices.push_back(start+i+1);
		}
	}

	void CreateSphere(float radius, int slice, int stack, MeshData &mesh)
	{
		mesh.vertices.clear();
		mesh.indices.clear();

		//Vertex number per for
		int vertsPerRow = slice + 1;
		//Number of rows(Excepth the two vertices of top and bottom
		int nRows = stack - 1;

		//Total vertex number(including two vertices of top and bottom)
		int nVerts = vertsPerRow * nRows + 2;
		//Total index number
		int nIndices = (nRows-1)*slice*6 + slice * 6;

		mesh.vertices.resize(nVerts);
		mesh.indices.resize(nIndices);

		for(int i=1; i<=nRows; ++i)
		{
			float phy = XM_PI * i / stack;
			float tmpRadius = radius * sin(phy);
			for(int j=0; j<vertsPerRow; ++j)
			{
				float theta = XM_2PI * j / slice;
				UINT index = (i-1)*vertsPerRow+j;

				float x = tmpRadius*cos(theta);
				float y = radius*cos(phy);
				float z = tmpRadius*sin(theta);

				//Position
				mesh.vertices[index].pos = XMFLOAT3(x,y,z);
				//Normal
				XMVECTOR N = XMVectorSet(x,y,z,0.f);
				XMStoreFloat3(&mesh.vertices[index].normal,XMVector3Normalize(N));
				//Tangent
				XMVECTOR T = XMVectorSet(-sin(theta),0.f,cos(theta),0.f);
				XMStoreFloat3(&mesh.vertices[index].tangent,XMVector3Normalize(T));
				//Texcoord
				mesh.vertices[index].tex = XMFLOAT2(j*1.f/slice,i*1.f/stack);
			}
		}

		int size = vertsPerRow * nRows;
		//Two vertex for top and bottom
		mesh.vertices[size].pos = XMFLOAT3(0.f,radius,0.f);
		mesh.vertices[size].normal = XMFLOAT3(0.f,1.f,0.f);
		mesh.vertices[size].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[size].tex = XMFLOAT2(0.f,0.f);

		mesh.vertices[size+1].pos = XMFLOAT3(0.f,-radius,0.f);
		mesh.vertices[size+1].normal = XMFLOAT3(0.f,-1.f,0.f);
		mesh.vertices[size+1].tangent = XMFLOAT3(1.f,0.f,0.f);
		mesh.vertices[size+1].tex = XMFLOAT2(0.f,1.f);
		

		//Begin construct index
		UINT tmp(0);
		int start1 = 0;
		int start2 = mesh.vertices.size() - vertsPerRow - 2;
		int top = size;
		int bottom = size + 1;
		for(int i=0; i<slice; ++i)
		{
			mesh.indices[tmp] = top;
			mesh.indices[tmp+1] = start1+i+1;
			mesh.indices[tmp+2] = start1+i;

			tmp += 3;
		}

		for(int i=0; i<slice; ++i)
		{
			mesh.indices[tmp] = bottom;
			mesh.indices[tmp+1] = start2 + i;
			mesh.indices[tmp+2] = start2 + i + 1;

			tmp += 3;
		}

		for(int i=0; i<nRows-1; ++i)
		{
			for(int j=0; j<slice; ++j)
			{
				mesh.indices[tmp] = i * vertsPerRow + j;
				mesh.indices[tmp+1] = (i + 1) * vertsPerRow + j + 1;
				mesh.indices[tmp+2] = (i + 1) * vertsPerRow + j;
				mesh.indices[tmp+3] = i * vertsPerRow + j;
				mesh.indices[tmp+4] = i * vertsPerRow + j + 1;
				mesh.indices[tmp+5] = (i + 1) * vertsPerRow + j + 1;

				tmp += 6;
			}
		}
	}
};