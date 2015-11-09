#ifndef _HP_D3D9TYPE_H
#define _HP_D3D9TYPE_H
#include <windows.h>
#include <d3d11_1.h>
#include <d3d11.h>
#include <d3d10.h>
#include <DirectXMath.h>
#include <DirectXColors.h>
#include <d3d11shader.h >
#include <D3Dcompiler.h >
#include <tchar.h>
#include <time.h> 
#include <stdio.h>
#include <iostream>

#include <DirectXMath.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

#include <algorithm>
#include <array>
#include <exception>
#include <malloc.h>
#include <map>
#include <memory>
#include <set>
#include <string>
#include <vector>
#include <memory>

#pragma comment(lib, "winmm.lib") 
#pragma comment(lib, "kernel32.lib") 
using namespace DirectX;

#ifndef GRAPHIC_API
#if defined(_WIN32)
#ifdef GRAPHIC_EXPORTS
#define GRAPHIC_API __declspec(dllexport)
#else
#define GRAPHIC_API __declspec(dllimport)
#endif
#else// 其他平台都是静态库
#define GRAPHIC_API
#endif
#endif
typedef	unsigned long	ulong;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned char	uchar;

typedef unsigned int    uint32;
typedef unsigned short  uint16;
typedef unsigned char   uint8;
typedef int   int32;


#ifndef SAFE_DELETE
#define SAFE_DELETE(p)       { if(p) { delete (p);     (p)=NULL; } }
#endif    
#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) { if(p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#endif



#ifndef V
#define V(x)           { hr = (x); }
#endif
#ifndef V_RETURN
#define V_RETURN(x)    { hr = (x); if( FAILED(hr) ) { return hr; } }
#endif


template<typename T>
void SafeRelease(T *t)
{
	if (t)
	{
		t->Release();
		t = NULL;
	}
}

struct  MousePos
{
	int X;
	int Y;
	bool bLeftDown;
	MousePos()
	{
		X = 0;
		Y = 0;
		bLeftDown = false;
	}
	MousePos(int x, int y)
	{
		X = x;
		Y = y;
		bLeftDown = false;
	}
};
typedef std::vector<D3D11_INPUT_ELEMENT_DESC> LayoutVector;
typedef std::string String;

#endif
