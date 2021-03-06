//-------------------------------------------------------------------------------------
// SimpleMath.inl -- Simplified C++ Math wrapper for DirectXMath
//
// THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF
// ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A
// PARTICULAR PURPOSE.
//  
// Copyright (c) Microsoft Corporation. All rights reserved.
//
// http://go.microsoft.com/fwlink/?LinkId=248929
//-------------------------------------------------------------------------------------

#pragma once

/****************************************************************************
 *
 * Vector2
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool Vector2::operator == ( const Vector2& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    return XMVector2Equal( v1, v2 );
}

inline bool Vector2::operator != ( const Vector2& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    return XMVector2NotEqual( v1, v2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline Vector2& Vector2::operator+= (const Vector2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorAdd(v1,v2);
    XMStoreFloat2( this, X );
    return *this;
}

inline Vector2& Vector2::operator-= (const Vector2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    XMStoreFloat2( this, X );
    return *this;
}

inline Vector2& Vector2::operator*= (const Vector2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    XMStoreFloat2( this, X );
    return *this;
}

inline Vector2& Vector2::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVectorScale(v1,S);
    XMStoreFloat2( this, X );
    return *this;
} 

inline Vector2& Vector2::operator/= (float S)
{
    using namespace DirectX;
    assert( S != 0.0f );
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVectorScale(v1, 1.f/S);
    XMStoreFloat2( this, X );
    return *this;
} 

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline Vector2 operator+ (const Vector2& V1, const Vector2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V1 );
    XMVECTOR v2 = XMLoadFloat2( &V2 );
    XMVECTOR X = XMVectorAdd(v1,v2);
    Vector2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline Vector2 operator- (const Vector2& V1, const Vector2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V1 );
    XMVECTOR v2 = XMLoadFloat2( &V2 );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    Vector2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline Vector2 operator* (const Vector2& V1, const Vector2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V1 );
    XMVECTOR v2 = XMLoadFloat2( &V2 );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    Vector2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline Vector2 operator* (const Vector2& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorScale(v1,S);
    Vector2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline Vector2 operator/ (const Vector2& V1, const Vector2& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V1 );
    XMVECTOR v2 = XMLoadFloat2( &V2 );
    XMVECTOR X = XMVectorDivide(v1,v2);
    Vector2 R;
    XMStoreFloat2( &R, X );
    return R;
}

inline Vector2 operator* (float S, const Vector2& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &V );
    XMVECTOR X = XMVectorScale(v1,S);
    Vector2 R;
    XMStoreFloat2( &R, X );
    return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool Vector2::InBounds( const Vector2& Bounds ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &Bounds );
    return XMVector2InBounds( v1, v2 );
}

inline float Vector2::Length() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVector2Length( v1 );
    return XMVectorGetX( X );
}

inline float Vector2::LengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVector2LengthSq( v1 );
    return XMVectorGetX( X );
}

inline float Vector2::Dot( const Vector2& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR X = XMVector2Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void Vector2::Cross( const Vector2& V, Vector2& result ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR R = XMVector2Cross( v1, v2 );
    XMStoreFloat2( &result, R );
}

inline Vector2 Vector2::Cross( const Vector2& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &V );
    XMVECTOR R = XMVector2Cross( v1, v2 );

    Vector2 result;
    XMStoreFloat2( &result, R );
    return result;
}

inline void Vector2::Normalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVector2Normalize( v1 );
    XMStoreFloat2( this, X );
}

inline void Vector2::Normalize( Vector2& result ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR X = XMVector2Normalize( v1 );
    XMStoreFloat2( &result, X );
}

inline void Vector2::Clamp( const Vector2& vmin, const Vector2& vmax )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &vmin );
    XMVECTOR v3 = XMLoadFloat2( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat2( this, X );
}

inline void Vector2::Clamp( const Vector2& vmin, const Vector2& vmax, Vector2& result ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( this );
    XMVECTOR v2 = XMLoadFloat2( &vmin );
    XMVECTOR v3 = XMLoadFloat2( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat2( &result, X );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float Vector2::Distance( const Vector2& v1, const Vector2& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector2Length( V );
    return XMVectorGetX( X );
}

inline float Vector2::DistanceSquared( const Vector2& v1, const Vector2& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector2LengthSq( V );
    return XMVectorGetX( X );
}

inline void Vector2::Min( const Vector2& v1, const Vector2& v2, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Min( const Vector2& v1, const Vector2& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::Max( const Vector2& v1, const Vector2& v2, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Max( const Vector2& v1, const Vector2& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::Lerp( const Vector2& v1, const Vector2& v2, float t, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Lerp( const Vector2& v1, const Vector2& v2, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::SmoothStep( const Vector2& v1, const Vector2& v2, float t, Vector2& result )
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::SmoothStep( const Vector2& v1, const Vector2& v2, float t )
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::Barycentric( const Vector2& v1, const Vector2& v2, const Vector2& v3, float f, float g, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Barycentric( const Vector2& v1, const Vector2& v2, const Vector2& v3, float f, float g )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::CatmullRom( const Vector2& v1, const Vector2& v2, const Vector2& v3, const Vector2& v4, float t, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR x4 = XMLoadFloat2( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::CatmullRom( const Vector2& v1, const Vector2& v2, const Vector2& v3, const Vector2& v4, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &v2 );
    XMVECTOR x3 = XMLoadFloat2( &v3 );
    XMVECTOR x4 = XMLoadFloat2( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::Hermite( const Vector2& v1, const Vector2& t1, const Vector2& v2, const Vector2& t2, float t, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &t1 );
    XMVECTOR x3 = XMLoadFloat2( &v2 );
    XMVECTOR x4 = XMLoadFloat2( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Hermite( const Vector2& v1, const Vector2& t1, const Vector2& v2, const Vector2& t2, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat2( &v1 );
    XMVECTOR x2 = XMLoadFloat2( &t1 );
    XMVECTOR x3 = XMLoadFloat2( &v2 );
    XMVECTOR x4 = XMLoadFloat2( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::Reflect( const Vector2& ivec, const Vector2& nvec, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Reflect( i, n );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Reflect( const Vector2& ivec, const Vector2& nvec )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Reflect( i, n );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::Refract( const Vector2& ivec, const Vector2& nvec, float refractionIndex, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Refract( i, n, refractionIndex );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Refract( const Vector2& ivec, const Vector2& nvec, float refractionIndex )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat2( &ivec );
    XMVECTOR n = XMLoadFloat2( &nvec );
    XMVECTOR X = XMVector2Refract( i, n, refractionIndex );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::Transform( const Vector2& v, const Quaternion& quat, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Transform( const Vector2& v, const Quaternion& quat )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

inline void Vector2::Transform( const Vector2& v, const Matrix& m, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformCoord( v1, M );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::Transform( const Vector2& v, const Matrix& m )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformCoord( v1, M );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

_Use_decl_annotations_
inline void Vector2::Transform( const Vector2* varray, size_t count, const Matrix& m, Vector2* resultArray )
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformCoordStream( resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M );
}

inline void Vector2::Transform( const Vector2& v, const Matrix& m, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2Transform( v1, M );
    XMStoreFloat4( &result, X );
}

_Use_decl_annotations_
inline void Vector2::Transform( const Vector2* varray, size_t count, const Matrix& m, Vector4* resultArray )
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT2), count, M );
}

inline void Vector2::TransformNormal( const Vector2& v, const Matrix& m, Vector2& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformNormal( v1, M );
    XMStoreFloat2( &result, X );
}

inline Vector2 Vector2::TransformNormal( const Vector2& v, const Matrix& m )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector2TransformNormal( v1, M );

    Vector2 result;
    XMStoreFloat2( &result, X );
    return result;
}

_Use_decl_annotations_
inline void Vector2::TransformNormal( const Vector2* varray, size_t count, const Matrix& m, Vector2* resultArray )
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector2TransformNormalStream( resultArray, sizeof(XMFLOAT2), varray, sizeof(XMFLOAT2), count, M );
}


/****************************************************************************
 *
 * Vector3
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool Vector3::operator == ( const Vector3& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    return XMVector3Equal( v1, v2 );
}

inline bool Vector3::operator != ( const Vector3& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    return XMVector3NotEqual( v1, v2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline Vector3& Vector3::operator+= (const Vector3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorAdd(v1,v2);
    XMStoreFloat3( this, X );
    return *this;
}

inline Vector3& Vector3::operator-= (const Vector3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    XMStoreFloat3( this, X );
    return *this;
}

inline Vector3& Vector3::operator*= (const Vector3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    XMStoreFloat3( this, X );
    return *this;
}

inline Vector3& Vector3::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVectorScale(v1,S);
    XMStoreFloat3( this, X );
    return *this;
} 

inline Vector3& Vector3::operator/= (float S)
{
    using namespace DirectX;
    assert( S != 0.0f );
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVectorScale(v1, 1.f/S);
    XMStoreFloat3( this, X );
    return *this;
} 

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline Vector3 Vector3::operator- () const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVectorNegate( v1 );
    Vector3 R;
    XMStoreFloat3( &R, X );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline Vector3 operator+ (const Vector3& V1, const Vector3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V1 );
    XMVECTOR v2 = XMLoadFloat3( &V2 );
    XMVECTOR X = XMVectorAdd(v1,v2);
    Vector3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline Vector3 operator- (const Vector3& V1, const Vector3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V1 );
    XMVECTOR v2 = XMLoadFloat3( &V2 );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    Vector3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline Vector3 operator* (const Vector3& V1, const Vector3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V1 );
    XMVECTOR v2 = XMLoadFloat3( &V2 );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    Vector3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline Vector3 operator* (const Vector3& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorScale(v1,S);
    Vector3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline Vector3 operator/ (const Vector3& V1, const Vector3& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V1 );
    XMVECTOR v2 = XMLoadFloat3( &V2 );
    XMVECTOR X = XMVectorDivide(v1,v2);
    Vector3 R;
    XMStoreFloat3( &R, X );
    return R;
}

inline Vector3 operator* (float S, const Vector3& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &V );
    XMVECTOR X = XMVectorScale(v1,S);
    Vector3 R;
    XMStoreFloat3( &R, X );
    return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool Vector3::InBounds( const Vector3& Bounds ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &Bounds );
    return XMVector3InBounds( v1, v2 );
}

inline float Vector3::Length() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVector3Length( v1 );
    return XMVectorGetX( X );
}

inline float Vector3::LengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVector3LengthSq( v1 );
    return XMVectorGetX( X );
}

inline float Vector3::Dot( const Vector3& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR X = XMVector3Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void Vector3::Cross( const Vector3& V, Vector3& result ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR R = XMVector3Cross( v1, v2 );
    XMStoreFloat3( &result, R );
}

inline Vector3 Vector3::Cross( const Vector3& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &V );
    XMVECTOR R = XMVector3Cross( v1, v2 );

    Vector3 result;
    XMStoreFloat3( &result, R );
    return result;
}

inline void Vector3::Normalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVector3Normalize( v1 );
    XMStoreFloat3( this, X );
}

inline void Vector3::Normalize( Vector3& result ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR X = XMVector3Normalize( v1 );
    XMStoreFloat3( &result, X );
}

inline void Vector3::Clamp( const Vector3& vmin, const Vector3& vmax )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &vmin );
    XMVECTOR v3 = XMLoadFloat3( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat3( this, X );
}

inline void Vector3::Clamp( const Vector3& vmin, const Vector3& vmax, Vector3& result ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( this );
    XMVECTOR v2 = XMLoadFloat3( &vmin );
    XMVECTOR v3 = XMLoadFloat3( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat3( &result, X );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float Vector3::Distance( const Vector3& v1, const Vector3& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector3Length( V );
    return XMVectorGetX( X );
}

inline float Vector3::DistanceSquared( const Vector3& v1, const Vector3& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector3LengthSq( V );
    return XMVectorGetX( X );
}

inline void Vector3::Min( const Vector3& v1, const Vector3& v2, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Min( const Vector3& v1, const Vector3& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::Max( const Vector3& v1, const Vector3& v2, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Max( const Vector3& v1, const Vector3& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::Lerp( const Vector3& v1, const Vector3& v2, float t, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Lerp( const Vector3& v1, const Vector3& v2, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::SmoothStep( const Vector3& v1, const Vector3& v2, float t, Vector3& result )
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::SmoothStep( const Vector3& v1, const Vector3& v2, float t )
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::Barycentric( const Vector3& v1, const Vector3& v2, const Vector3& v3, float f, float g, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Barycentric( const Vector3& v1, const Vector3& v2, const Vector3& v3, float f, float g )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::CatmullRom( const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float t, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR x4 = XMLoadFloat3( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::CatmullRom( const Vector3& v1, const Vector3& v2, const Vector3& v3, const Vector3& v4, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &v2 );
    XMVECTOR x3 = XMLoadFloat3( &v3 );
    XMVECTOR x4 = XMLoadFloat3( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::Hermite( const Vector3& v1, const Vector3& t1, const Vector3& v2, const Vector3& t2, float t, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &t1 );
    XMVECTOR x3 = XMLoadFloat3( &v2 );
    XMVECTOR x4 = XMLoadFloat3( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Hermite( const Vector3& v1, const Vector3& t1, const Vector3& v2, const Vector3& t2, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat3( &v1 );
    XMVECTOR x2 = XMLoadFloat3( &t1 );
    XMVECTOR x3 = XMLoadFloat3( &v2 );
    XMVECTOR x4 = XMLoadFloat3( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::Reflect( const Vector3& ivec, const Vector3& nvec, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Reflect( i, n );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Reflect( const Vector3& ivec, const Vector3& nvec )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Reflect( i, n );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::Refract( const Vector3& ivec, const Vector3& nvec, float refractionIndex, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Refract( i, n, refractionIndex );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Refract( const Vector3& ivec, const Vector3& nvec, float refractionIndex )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat3( &ivec );
    XMVECTOR n = XMLoadFloat3( &nvec );
    XMVECTOR X = XMVector3Refract( i, n, refractionIndex );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::Transform( const Vector3& v, const Quaternion& quat, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Transform( const Vector3& v, const Quaternion& quat )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

inline void Vector3::Transform( const Vector3& v, const Matrix& m, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformCoord( v1, M );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::Transform( const Vector3& v, const Matrix& m )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformCoord( v1, M );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

_Use_decl_annotations_
inline void Vector3::Transform( const Vector3* varray, size_t count, const Matrix& m, Vector3* resultArray )
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformCoordStream( resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M );
}

inline void Vector3::Transform( const Vector3& v, const Matrix& m, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3Transform( v1, M );
    XMStoreFloat4( &result, X );
}

_Use_decl_annotations_
inline void Vector3::Transform( const Vector3* varray, size_t count, const Matrix& m, Vector4* resultArray )
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT3), count, M );
}

inline void Vector3::TransformNormal( const Vector3& v, const Matrix& m, Vector3& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformNormal( v1, M );
    XMStoreFloat3( &result, X );
}

inline Vector3 Vector3::TransformNormal( const Vector3& v, const Matrix& m )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector3TransformNormal( v1, M );

    Vector3 result;
    XMStoreFloat3( &result, X );
    return result;
}

_Use_decl_annotations_
inline void Vector3::TransformNormal( const Vector3* varray, size_t count, const Matrix& m, Vector3* resultArray )
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector3TransformNormalStream( resultArray, sizeof(XMFLOAT3), varray, sizeof(XMFLOAT3), count, M );
}


/****************************************************************************
 *
 * Vector4
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool Vector4::operator == ( const Vector4& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    return XMVector4Equal( v1, v2 );
}

inline bool Vector4::operator != ( const Vector4& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    return XMVector4NotEqual( v1, v2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline Vector4& Vector4::operator+= (const Vector4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorAdd(v1,v2);
    XMStoreFloat4( this, X );
    return *this;
}

inline Vector4& Vector4::operator-= (const Vector4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    XMStoreFloat4( this, X );
    return *this;
}

inline Vector4& Vector4::operator*= (const Vector4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    XMStoreFloat4( this, X );
    return *this;
}

inline Vector4& Vector4::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVectorScale(v1,S);
    XMStoreFloat4( this, X );
    return *this;
} 

inline Vector4& Vector4::operator/= (float S)
{
    using namespace DirectX;
    assert( S != 0.0f );
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVectorScale(v1, 1.f/S);
    XMStoreFloat4( this, X );
    return *this;
} 

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline Vector4 Vector4::operator- () const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVectorNegate( v1 );
    Vector4 R;
    XMStoreFloat4( &R, X );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline Vector4 operator+ (const Vector4& V1, const Vector4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V1 );
    XMVECTOR v2 = XMLoadFloat4( &V2 );
    XMVECTOR X = XMVectorAdd(v1,v2);
    Vector4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline Vector4 operator- (const Vector4& V1, const Vector4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V1 );
    XMVECTOR v2 = XMLoadFloat4( &V2 );
    XMVECTOR X = XMVectorSubtract(v1,v2);
    Vector4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline Vector4 operator* (const Vector4& V1, const Vector4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V1 );
    XMVECTOR v2 = XMLoadFloat4( &V2 );
    XMVECTOR X = XMVectorMultiply(v1,v2);
    Vector4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline Vector4 operator* (const Vector4& V, float S)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorScale(v1,S);
    Vector4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline Vector4 operator/ (const Vector4& V1, const Vector4& V2)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V1 );
    XMVECTOR v2 = XMLoadFloat4( &V2 );
    XMVECTOR X = XMVectorDivide(v1,v2);
    Vector4 R;
    XMStoreFloat4( &R, X );
    return R;
}

inline Vector4 operator* (float S, const Vector4& V)
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &V );
    XMVECTOR X = XMVectorScale(v1,S);
    Vector4 R;
    XMStoreFloat4( &R, X );
    return R;
}

//------------------------------------------------------------------------------
// Vector operations
//------------------------------------------------------------------------------

inline bool Vector4::InBounds( const Vector4& Bounds ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &Bounds );
    return XMVector4InBounds( v1, v2 );
}

inline float Vector4::Length() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVector4Length( v1 );
    return XMVectorGetX( X );
}

inline float Vector4::LengthSquared() const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVector4LengthSq( v1 );
    return XMVectorGetX( X );
}

inline float Vector4::Dot( const Vector4& V ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &V );
    XMVECTOR X = XMVector4Dot( v1, v2 );
    return XMVectorGetX( X );
}

inline void Vector4::Cross( const Vector4& v1, const Vector4& v2, Vector4& result ) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( this );
    XMVECTOR x2 = XMLoadFloat4( &v1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR R = XMVector4Cross( x1, x2, x3 );
    XMStoreFloat4( &result, R );
}

inline Vector4 Vector4::Cross( const Vector4& v1, const Vector4& v2 ) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( this );
    XMVECTOR x2 = XMLoadFloat4( &v1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR R = XMVector4Cross( x1, x2, x3 );

    Vector4 result;
    XMStoreFloat4( &result, R );
    return result;
}

inline void Vector4::Normalize()
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVector4Normalize( v1 );
    XMStoreFloat4( this, X );
}

inline void Vector4::Normalize( Vector4& result ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR X = XMVector4Normalize( v1 );
    XMStoreFloat4( &result, X );
}

inline void Vector4::Clamp( const Vector4& vmin, const Vector4& vmax )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &vmin );
    XMVECTOR v3 = XMLoadFloat4( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat4( this, X );
}

inline void Vector4::Clamp( const Vector4& vmin, const Vector4& vmax, Vector4& result ) const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( this );
    XMVECTOR v2 = XMLoadFloat4( &vmin );
    XMVECTOR v3 = XMLoadFloat4( &vmax );
    XMVECTOR X = XMVectorClamp( v1, v2, v3 );
    XMStoreFloat4( &result, X );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline float Vector4::Distance( const Vector4& v1, const Vector4& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector4Length( V );
    return XMVectorGetX( X );
}

inline float Vector4::DistanceSquared( const Vector4& v1, const Vector4& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR V = XMVectorSubtract( x2, x1 );
    XMVECTOR X = XMVector4LengthSq( V );
    return XMVectorGetX( X );
}

inline void Vector4::Min( const Vector4& v1, const Vector4& v2, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Min( const Vector4& v1, const Vector4& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMin( x1, x2 );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Max( const Vector4& v1, const Vector4& v2, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Max( const Vector4& v1, const Vector4& v2 )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorMax( x1, x2 );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Lerp( const Vector4& v1, const Vector4& v2, float t, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Lerp( const Vector4& v1, const Vector4& v2, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::SmoothStep( const Vector4& v1, const Vector4& v2, float t, Vector4& result )
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::SmoothStep( const Vector4& v1, const Vector4& v2, float t )
{
    using namespace DirectX;
    t = (t > 1.0f) ? 1.0f : ((t < 0.0f) ? 0.0f : t);  // Clamp value to 0 to 1
    t = t*t*(3.f - 2.f*t);
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR X = XMVectorLerp( x1, x2, t );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Barycentric( const Vector4& v1, const Vector4& v2, const Vector4& v3, float f, float g, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Barycentric( const Vector4& v1, const Vector4& v2, const Vector4& v3, float f, float g )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR X = XMVectorBaryCentric( x1, x2, x3, f, g );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::CatmullRom( const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4, float t, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR x4 = XMLoadFloat4( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::CatmullRom( const Vector4& v1, const Vector4& v2, const Vector4& v3, const Vector4& v4, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &v2 );
    XMVECTOR x3 = XMLoadFloat4( &v3 );
    XMVECTOR x4 = XMLoadFloat4( &v4 );
    XMVECTOR X = XMVectorCatmullRom( x1, x2, x3, x4, t );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Hermite( const Vector4& v1, const Vector4& t1, const Vector4& v2, const Vector4& t2, float t, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &t1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR x4 = XMLoadFloat4( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Hermite( const Vector4& v1, const Vector4& t1, const Vector4& v2, const Vector4& t2, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( &v1 );
    XMVECTOR x2 = XMLoadFloat4( &t1 );
    XMVECTOR x3 = XMLoadFloat4( &v2 );
    XMVECTOR x4 = XMLoadFloat4( &t2 );
    XMVECTOR X = XMVectorHermite( x1, x2, x3, x4, t );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Reflect( const Vector4& ivec, const Vector4& nvec, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Reflect( i, n );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Reflect( const Vector4& ivec, const Vector4& nvec )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Reflect( i, n );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Refract( const Vector4& ivec, const Vector4& nvec, float refractionIndex, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Refract( i, n, refractionIndex );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Refract( const Vector4& ivec, const Vector4& nvec, float refractionIndex )
{
    using namespace DirectX;
    XMVECTOR i = XMLoadFloat4( &ivec );
    XMVECTOR n = XMLoadFloat4( &nvec );
    XMVECTOR X = XMVector4Refract( i, n, refractionIndex );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Transform( const Vector2& v, const Quaternion& quat, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Transform( const Vector2& v, const Quaternion& quat )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat2( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Transform( const Vector3& v, const Quaternion& quat, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Transform( const Vector3& v, const Quaternion& quat )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat3( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( g_XMIdentityR3, X, g_XMSelect1110 ); // result.w = 1.f

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Transform( const Vector4& v, const Quaternion& quat, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( v1, X, g_XMSelect1110 ); // result.w = v.w
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Transform( const Vector4& v, const Quaternion& quat )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMVECTOR q = XMLoadFloat4( &quat );
    XMVECTOR X = XMVector3Rotate( v1, q );
    X = XMVectorSelect( v1, X, g_XMSelect1110 ); // result.w = v.w

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

inline void Vector4::Transform( const Vector4& v, const Matrix& m, Vector4& result )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector4Transform( v1, M );
    XMStoreFloat4( &result, X );
}

inline Vector4 Vector4::Transform( const Vector4& v, const Matrix& m )
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( &v );
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVECTOR X = XMVector4Transform( v1, M );

    Vector4 result;
    XMStoreFloat4( &result, X );
    return result;
}

_Use_decl_annotations_
inline void Vector4::Transform( const Vector4* varray, size_t count, const Matrix& m, Vector4* resultArray )
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( &m );
    XMVector4TransformStream( resultArray, sizeof(XMFLOAT4), varray, sizeof(XMFLOAT4), count, M );
}


/****************************************************************************
 *
 * Matrix
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool Matrix::operator == ( const Matrix& M ) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    return ( XMVector4Equal( x1, y1 )
             && XMVector4Equal( x2, y2 )
             && XMVector4Equal( x3, y3 )
             && XMVector4Equal( x4, y4 ) ) != 0;
}


inline bool Matrix::operator != ( const Matrix& M ) const
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

	return (XMVector4NotEqual(x1, y1)
		|| XMVector4NotEqual(x2, y2)
		|| XMVector4NotEqual(x3, y3)
		|| XMVector4NotEqual(x4, y4)) != 0;
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline Matrix& Matrix::operator+= (const Matrix& M)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    x1 = XMVectorAdd( x1, y1 );
    x2 = XMVectorAdd( x2, y2 );
    x3 = XMVectorAdd( x3, y3 );
    x4 = XMVectorAdd( x4, y4 );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

inline Matrix& Matrix::operator-= (const Matrix& M)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    x1 = XMVectorSubtract( x1, y1 );
    x2 = XMVectorSubtract( x2, y2 );
    x3 = XMVectorSubtract( x3, y3 );
    x4 = XMVectorSubtract( x4, y4 );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

inline Matrix& Matrix::operator*= (const Matrix& M)
{
    using namespace DirectX;
    XMMATRIX M1 = XMLoadFloat4x4( this );
    XMMATRIX M2 = XMLoadFloat4x4( &M );
    XMMATRIX X = XMMatrixMultiply( M1, M2 );
    XMStoreFloat4x4( this, X );
    return *this;
}

inline Matrix& Matrix::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    x1 = XMVectorScale( x1, S );
    x2 = XMVectorScale( x2, S );
    x3 = XMVectorScale( x3, S );
    x4 = XMVectorScale( x4, S );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

inline Matrix& Matrix::operator/= (float S)
{
    using namespace DirectX;
    assert( S != 0.f );
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    float rs = 1.f / S;

    x1 = XMVectorScale( x1, rs );
    x2 = XMVectorScale( x2, rs );
    x3 = XMVectorScale( x3, rs );
    x4 = XMVectorScale( x4, rs );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

inline Matrix& Matrix::operator/= (const Matrix& M)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<XMFLOAT4*>(&_41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    x1 = XMVectorDivide( x1, y1 );
    x2 = XMVectorDivide( x2, y2 );
    x3 = XMVectorDivide( x3, y3 );
    x4 = XMVectorDivide( x4, y4 );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&_41), x4 );
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline Matrix Matrix::operator- () const
{
    using namespace DirectX;
    XMVECTOR v1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_11) );
    XMVECTOR v2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_21) );
    XMVECTOR v3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_31) );
    XMVECTOR v4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&_41) );

    v1 = XMVectorNegate( v1 );
    v2 = XMVectorNegate( v2 );
    v3 = XMVectorNegate( v3 );
    v4 = XMVectorNegate( v4 );

    Matrix R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), v1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), v2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), v3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), v4 );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline Matrix operator+ (const Matrix& M1, const Matrix& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorAdd( x1, y1 );
    x2 = XMVectorAdd( x2, y2 );
    x3 = XMVectorAdd( x3, y3 );
    x4 = XMVectorAdd( x4, y4 );

    Matrix R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline Matrix operator- (const Matrix& M1, const Matrix& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorSubtract( x1, y1 );
    x2 = XMVectorSubtract( x2, y2 );
    x3 = XMVectorSubtract( x3, y3 );
    x4 = XMVectorSubtract( x4, y4 );

    Matrix R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline Matrix operator* (const Matrix& M1, const Matrix& M2)
{
    using namespace DirectX;
    XMMATRIX m1 = XMLoadFloat4x4( &M1 );
    XMMATRIX m2 = XMLoadFloat4x4( &M2 );
    XMMATRIX X = XMMatrixMultiply( m1, m2 );

    Matrix R;
    XMStoreFloat4x4( &R, X );
    return R;
}

inline Matrix operator* (const Matrix& M, float S)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    x1 = XMVectorScale( x1, S );
    x2 = XMVectorScale( x2, S );
    x3 = XMVectorScale( x3, S );
    x4 = XMVectorScale( x4, S );

    Matrix R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline Matrix operator/ (const Matrix& M, float S)
{
    using namespace DirectX;
    assert( S != 0.f );

    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    float rs = 1.f / S;

    x1 = XMVectorScale( x1, rs );
    x2 = XMVectorScale( x2, rs );
    x3 = XMVectorScale( x3, rs );
    x4 = XMVectorScale( x4, rs );

    Matrix R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline Matrix operator/ (const Matrix& M1, const Matrix& M2)
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorDivide( x1, y1 );
    x2 = XMVectorDivide( x2, y2 );
    x3 = XMVectorDivide( x3, y3 );
    x4 = XMVectorDivide( x4, y4 );

    Matrix R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

inline Matrix operator* (float S, const Matrix& M)
{
    using namespace DirectX;

    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M._41) );

    x1 = XMVectorScale( x1, S );
    x2 = XMVectorScale( x2, S );
    x3 = XMVectorScale( x3, S );
    x4 = XMVectorScale( x4, S );

    Matrix R;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&R._41), x4 );
    return R;
}

//------------------------------------------------------------------------------
// Matrix operations
//------------------------------------------------------------------------------

inline bool Matrix::Decompose( Vector3& scale, Quaternion& rotation, Vector3& translation )
{
    using namespace DirectX;

    XMVECTOR s, r, t;

    if ( !XMMatrixDecompose( &s, &r, &t, *this ) )
        return false;

    XMStoreFloat3( &scale, s );
    XMStoreFloat4( &rotation, r );
    XMStoreFloat3( &translation, t );

    return true;
}
inline Vector3  Matrix::Scale()
{
	using namespace DirectX;
	Vector3  vScale;
	vScale.x = Right().Length();
	vScale.y = Up().Length();
	vScale.z = Backward().Length();
	return vScale;
}
inline Matrix Matrix::Transpose() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixTranspose( M ) );
    return R;
}

inline void Matrix::Transpose( Matrix& result ) const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    XMStoreFloat4x4( &result, XMMatrixTranspose( M ) );
}

inline Matrix Matrix::Invert() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    Matrix R;
    XMVECTOR det;
    XMStoreFloat4x4( &R, XMMatrixInverse( &det, M ) );
    return R;
}

inline void Matrix::Invert( Matrix& result ) const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    XMVECTOR det;
    XMStoreFloat4x4( &result, XMMatrixInverse( &det, M ) );
}

inline float Matrix::Determinant() const
{
    using namespace DirectX;
    XMMATRIX M = XMLoadFloat4x4( this );
    return XMVectorGetX( XMMatrixDeterminant( M ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

_Use_decl_annotations_
inline Matrix Matrix::CreateBillboard( const Vector3& object, const Vector3& cameraPosition, const Vector3& cameraUp, const Vector3* cameraForward )
{
    using namespace DirectX;
    XMVECTOR O = XMLoadFloat3( &object );
    XMVECTOR C = XMLoadFloat3( &cameraPosition );
    XMVECTOR Z = XMVectorSubtract( O, C );

    XMVECTOR N = XMVector3LengthSq( Z );
    if ( XMVector3Less( N, g_XMEpsilon ) )
    {
        if ( cameraForward )
        {
            XMVECTOR F = XMLoadFloat3( cameraForward );
            Z = XMVectorNegate( F );
        }
        else
            Z = g_XMNegIdentityR2;
    }
    else
    {
        Z = XMVector3Normalize( Z );
    }

    XMVECTOR up = XMLoadFloat3( &cameraUp );
    XMVECTOR X = XMVector3Cross( up, Z );
    X = XMVector3Normalize( X );

    XMVECTOR Y = XMVector3Cross( Z, X );

    XMMATRIX M;
    M.r[0] = X;
    M.r[1] = Y;
    M.r[2] = Z;
    M.r[3] = XMVectorSetW( O, 1.f );

    Matrix R;
    XMStoreFloat4x4( &R, M );
    return R;
}

_Use_decl_annotations_
inline Matrix Matrix::CreateConstrainedBillboard( const Vector3& object, const Vector3& cameraPosition, const Vector3& rotateAxis,
                                                  const Vector3* cameraForward, const Vector3* objectForward )
{
    using namespace DirectX;

    static const XMVECTORF32 s_minAngle = { 0.99825467075f, 0.99825467075f, 0.99825467075f, 0.99825467075f }; // 1.0 - XMConvertToRadians( 0.1f );

    XMVECTOR O = XMLoadFloat3( &object );
    XMVECTOR C = XMLoadFloat3( &cameraPosition );
    XMVECTOR faceDir = XMVectorSubtract( O, C );

    XMVECTOR N = XMVector3LengthSq( faceDir );
    if (XMVector3Less(N, g_XMEpsilon))
    {
        if (cameraForward)
        {
            XMVECTOR F = XMLoadFloat3( cameraForward );
            faceDir = XMVectorNegate( F );
        }
        else
            faceDir = g_XMNegIdentityR2;
    }
    else
    {
        faceDir = XMVector3Normalize( faceDir );
    }

    XMVECTOR Y = XMLoadFloat3( &rotateAxis );
    XMVECTOR X, Z;

    XMVECTOR dot = XMVectorAbs( XMVector3Dot( Y, faceDir ) );
    if ( XMVector3Greater( dot, s_minAngle ) )
    {
        if ( objectForward )
        {
            Z = XMLoadFloat3( objectForward );
            dot = XMVectorAbs( XMVector3Dot( Y, Z ) );
            if ( XMVector3Greater( dot, s_minAngle ) )
            {
                dot = XMVectorAbs( XMVector3Dot( Y, g_XMNegIdentityR2 ) );
                Z = ( XMVector3Greater( dot, s_minAngle ) ) ? g_XMIdentityR0 : g_XMNegIdentityR2;
            }
        }
        else
        {
            dot = XMVectorAbs( XMVector3Dot( Y, g_XMNegIdentityR2 ) );
            Z = ( XMVector3Greater( dot, s_minAngle ) ) ? g_XMIdentityR0 : g_XMNegIdentityR2;
        }

        X = XMVector3Cross( Y, Z );
        X = XMVector3Normalize( X );

        Z = XMVector3Cross( X, Y );
        Z = XMVector3Normalize( Z );
    }
    else
    {
        X = XMVector3Cross( Y, faceDir );
        X = XMVector3Normalize( X );

        Z = XMVector3Cross( X, Y );
        Z = XMVector3Normalize( Z );
    }

    XMMATRIX M;
    M.r[0] = X;
    M.r[1] = Y;
    M.r[2] = Z;
    M.r[3] = XMVectorSetW( O, 1.f );

    Matrix R;
    XMStoreFloat4x4( &R, M );
    return R;
}

inline Matrix Matrix::CreateTranslation( const Vector3& position )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixTranslation( position.x, position.y, position.z ) );
    return R;
}

inline Matrix Matrix::CreateTranslation( float x, float y, float z )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixTranslation( x, y, z ) );
    return R;
}

inline Matrix Matrix::CreateScale( const Vector3& scales )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixScaling( scales.x, scales.y, scales.z ) );
    return R;
}

inline Matrix Matrix::CreateScale( float xs, float ys, float zs )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixScaling( xs, ys, zs ) );
    return R;
}

inline Matrix Matrix::CreateScale( float scale )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixScaling( scale, scale, scale ) );
    return R;
}

inline Matrix Matrix::CreateRotationX( float radians )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixRotationX( radians ) );
    return R;
}

inline Matrix Matrix::CreateRotationY( float radians )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixRotationY( radians ) );
    return R;
}

inline Matrix Matrix::CreateRotationZ( float radians )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixRotationZ( radians ) );
    return R;
}

inline Matrix Matrix::CreateFromAxisAngle( const Vector3& axis, float angle )
{
    using namespace DirectX;
    Matrix R;
    XMVECTOR a = XMLoadFloat3( &axis );
    XMStoreFloat4x4( &R, XMMatrixRotationAxis( a, angle ) );
    return R;
}

inline Matrix Matrix::CreatePerspectiveFieldOfView( float fov, float aspectRatio, float nearPlane, float farPlane )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveFovRH( fov, aspectRatio, nearPlane, farPlane ) );
    return R;
}

inline Matrix Matrix::CreatePerspective( float width, float height, float nearPlane, float farPlane )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveRH( width, height, nearPlane, farPlane ) );
    return R;
}

inline Matrix Matrix::CreatePerspectiveOffCenter( float left, float right, float bottom, float top, float nearPlane, float farPlane )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixPerspectiveOffCenterRH( left, right, bottom, top, nearPlane, farPlane ) );
    return R;
}

inline Matrix Matrix::CreateOrthographic( float width, float height, float zNearPlane, float zFarPlane )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixOrthographicRH( width, height, zNearPlane, zFarPlane ) );
    return R;
}

inline Matrix Matrix::CreateOrthographicOffCenter( float left, float right, float bottom, float top, float zNearPlane, float zFarPlane )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixOrthographicOffCenterRH( left, right, bottom, top, zNearPlane, zFarPlane ) );
    return R;
}

inline Matrix Matrix::CreateLookAt( const Vector3& eye, const Vector3& target, const Vector3& up )
{
    using namespace DirectX;
    Matrix R;
    XMVECTOR eyev = XMLoadFloat3( &eye );
    XMVECTOR targetv = XMLoadFloat3( &target );
    XMVECTOR upv = XMLoadFloat3( &up );
    XMStoreFloat4x4( &R, XMMatrixLookAtRH( eyev, targetv, upv ) );
    return R;
}

inline Matrix Matrix::CreateLookAtLh(const Vector3& eye, const Vector3& target, const Vector3& up)
{
	using namespace DirectX;
	Matrix R;
	XMVECTOR eyev = XMLoadFloat3(&eye);
	XMVECTOR targetv = XMLoadFloat3(&target);
	XMVECTOR upv = XMLoadFloat3(&up);
	XMStoreFloat4x4(&R, XMMatrixLookAtLH(eyev, targetv, upv));
	return R;
}


inline Matrix Matrix::CreateWorld( const Vector3& position, const Vector3& forward, const Vector3& up )
{
    using namespace DirectX;
    XMVECTOR zaxis = XMVector3Normalize( XMVectorNegate( XMLoadFloat3( &forward ) ) );
    XMVECTOR yaxis = XMLoadFloat3( &up );
    XMVECTOR xaxis = XMVector3Normalize( XMVector3Cross( yaxis, zaxis ) );
    yaxis = XMVector3Cross( zaxis, xaxis );
    
    Matrix R;
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._11 ), xaxis );
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._21 ), yaxis );
    XMStoreFloat3( reinterpret_cast<XMFLOAT3*>( &R._31 ), zaxis );
    R._14 = R._24 = R._34 = 0.f;
    R._41 = position.x; R._42 = position.y; R._43 = position.z;
    R._44 = 1.f;
    return R;
}

inline Matrix Matrix::CreateFromQuaternion( const Quaternion& rotation )
{
    using namespace DirectX;
    Matrix R;
    XMVECTOR quatv = XMLoadFloat4( &rotation );
    XMStoreFloat4x4( &R, XMMatrixRotationQuaternion( quatv ) );
    return R;
}

inline Matrix Matrix::CreateFromYawPitchRoll( float yaw, float pitch, float roll )
{
    using namespace DirectX;
    Matrix R;
    XMStoreFloat4x4( &R, XMMatrixRotationRollPitchYaw( pitch, yaw, roll ) );
    return R;
}

inline Matrix Matrix::CreateShadow( const Vector3& lightDir, const Plane& plane )
{
    using namespace DirectX;
    Matrix R;
    XMVECTOR light = XMLoadFloat3( &lightDir );
    XMVECTOR planev = XMLoadFloat4( &plane );
    XMStoreFloat4x4( &R, XMMatrixShadow( planev, light ) );
    return R;
}

inline Matrix Matrix::CreateReflection( const Plane& plane )
{
    using namespace DirectX;
    Matrix R;
    XMVECTOR planev = XMLoadFloat4( &plane );
    XMStoreFloat4x4( &R, XMMatrixReflect( planev ) );
    return R;
}

inline void Matrix::Lerp( const Matrix& M1, const Matrix& M2, float t, Matrix& result )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorLerp( x1, y1, t );
    x2 = XMVectorLerp( x2, y2, t );
    x3 = XMVectorLerp( x3, y3, t );
    x4 = XMVectorLerp( x4, y4, t );

    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._41), x4 );
}

inline Matrix Matrix::Lerp( const Matrix& M1, const Matrix& M2, float t )
{
    using namespace DirectX;
    XMVECTOR x1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._11) );
    XMVECTOR x2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._21) );
    XMVECTOR x3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._31) );
    XMVECTOR x4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M1._41) );

    XMVECTOR y1 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._11) );
    XMVECTOR y2 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._21) );
    XMVECTOR y3 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._31) );
    XMVECTOR y4 = XMLoadFloat4( reinterpret_cast<const XMFLOAT4*>(&M2._41) );

    x1 = XMVectorLerp( x1, y1, t );
    x2 = XMVectorLerp( x2, y2, t );
    x3 = XMVectorLerp( x3, y3, t );
    x4 = XMVectorLerp( x4, y4, t );

    Matrix result;
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._11), x1 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._21), x2 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._31), x3 );
    XMStoreFloat4( reinterpret_cast<XMFLOAT4*>(&result._41), x4 );
    return result;
}

inline void Matrix::Transform( const Matrix& M, const Quaternion& rotation, Matrix& result )
{
    using namespace DirectX;
    XMVECTOR quatv = XMLoadFloat4( &rotation );

    XMMATRIX M0 = XMLoadFloat4x4( &M );
    XMMATRIX M1 = XMMatrixRotationQuaternion( quatv );

    XMStoreFloat4x4( &result, XMMatrixMultiply( M0, M1 ) );
}

inline Matrix Matrix::Transform( const Matrix& M, const Quaternion& rotation )
{
    using namespace DirectX;
    XMVECTOR quatv = XMLoadFloat4( &rotation );

    XMMATRIX M0 = XMLoadFloat4x4( &M );
    XMMATRIX M1 = XMMatrixRotationQuaternion( quatv );

    Matrix result;
    XMStoreFloat4x4( &result, XMMatrixMultiply( M0, M1 ) );
    return result;
}


/****************************************************************************
 *
 * Plane
 *
 ****************************************************************************/

inline Plane::Plane(const Vector3& point1, const Vector3& point2, const Vector3& point3 )
{
    using namespace DirectX;
    XMVECTOR P0 = XMLoadFloat3( &point1 );
    XMVECTOR P1 = XMLoadFloat3( &point2 );
    XMVECTOR P2 = XMLoadFloat3( &point3 );
    XMStoreFloat4( this, XMPlaneFromPoints( P0, P1, P2 ) );
}

inline Plane::Plane(const Vector3& point, const Vector3& normal)
{
    using namespace DirectX;
    XMVECTOR P = XMLoadFloat3( &point );
    XMVECTOR N = XMLoadFloat3( &normal );
    XMStoreFloat4( this, XMPlaneFromPointNormal( P, N ) );
}

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool Plane::operator == ( const Plane& p ) const
{
    using namespace DirectX;
    XMVECTOR p1 = XMLoadFloat4( this );
    XMVECTOR p2 = XMLoadFloat4( &p );
    return XMPlaneEqual( p1, p2 );
}

inline bool Plane::operator != ( const Plane& p ) const
{
    using namespace DirectX;
    XMVECTOR p1 = XMLoadFloat4( this );
    XMVECTOR p2 = XMLoadFloat4( &p );
    return XMPlaneNotEqual( p1, p2 );
}

//------------------------------------------------------------------------------
// Plane operations
//------------------------------------------------------------------------------

inline void Plane::Normalize()
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMStoreFloat4( this, XMPlaneNormalize( p ) );
}

inline void Plane::Normalize( Plane& result ) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMPlaneNormalize( p ) );
}

inline float Plane::Dot( const Vector4& v ) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR v0 = XMLoadFloat4( &v );
    return XMVectorGetX( XMPlaneDot( p, v0 ) );
}

inline float Plane::DotCoordinate( const Vector3& position ) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR v0 = XMLoadFloat3( &position );
    return XMVectorGetX( XMPlaneDotCoord( p, v0 ) );
}

inline float Plane::DotNormal( const Vector3& normal ) const
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( this );
    XMVECTOR n0 = XMLoadFloat3( &normal );
    return XMVectorGetX( XMPlaneDotNormal( p, n0 ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline void Plane::Transform( const Plane& plane, const Matrix& M, Plane& result )
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMMATRIX m0 = XMLoadFloat4x4( &M );
    XMStoreFloat4( &result, XMPlaneTransform( p, m0 ) );
}

inline Plane Plane::Transform( const Plane& plane, const Matrix& M )
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMMATRIX m0 = XMLoadFloat4x4( &M );

    Plane result;
    XMStoreFloat4( &result, XMPlaneTransform( p, m0 ) );
    return result;
}

inline void Plane::Transform( const Plane& plane, const Quaternion& rotation, Plane& result )
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMVECTOR q = XMLoadFloat4( &rotation );
    XMVECTOR X = XMVector3Rotate( p, q );
    X = XMVectorSelect( p, X, g_XMSelect1110 ); // result.d = plane.d
    XMStoreFloat4( &result, X );
}

inline Plane Plane::Transform( const Plane& plane, const Quaternion& rotation )
{
    using namespace DirectX;
    XMVECTOR p = XMLoadFloat4( &plane );
    XMVECTOR q = XMLoadFloat4( &rotation );
    XMVECTOR X = XMVector3Rotate( p, q );
    X = XMVectorSelect( p, X, g_XMSelect1110 ); // result.d = plane.d

    Plane result;
    XMStoreFloat4( &result, X );
    return result;
}


/****************************************************************************
 *
 * Quaternion
 *
 ****************************************************************************/

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------

inline bool Quaternion::operator == ( const Quaternion& q ) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    return XMQuaternionEqual( q1, q2 );
}

inline bool Quaternion::operator != ( const Quaternion& q ) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    return XMQuaternionNotEqual( q1, q2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline Quaternion& Quaternion::operator+= (const Quaternion& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    XMStoreFloat4( this, XMVectorAdd( q1, q2 ) );
    return *this;
}

inline Quaternion& Quaternion::operator-= (const Quaternion& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    XMStoreFloat4( this, XMVectorSubtract( q1, q2 ) );
    return *this;
}

inline Quaternion& Quaternion::operator*= (const Quaternion& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    XMStoreFloat4( this, XMQuaternionMultiply( q1, q2 ) );
    return *this;
}

inline Quaternion& Quaternion::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( this, XMVectorScale( q, S ) );
    return *this;
}

inline Quaternion& Quaternion::operator/= (const Quaternion& q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    q2 = XMQuaternionInverse( q2 );
    XMStoreFloat4( this, XMQuaternionMultiply( q1, q2 ) );
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline Quaternion Quaternion::operator- () const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );

    Quaternion R;
    XMStoreFloat4( &R, XMVectorNegate( q ) );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline Quaternion operator+ (const Quaternion& Q1, const Quaternion& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q1 );
    XMVECTOR q2 = XMLoadFloat4( &Q2 );

    Quaternion R;
    XMStoreFloat4( &R, XMVectorAdd( q1, q2 ) );
    return R;
}

inline Quaternion operator- (const Quaternion& Q1, const Quaternion& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q1 );
    XMVECTOR q2 = XMLoadFloat4( &Q2 );

    Quaternion R;
    XMStoreFloat4( &R, XMVectorSubtract( q1, q2 ) );
    return R;
}

inline Quaternion operator* (const Quaternion& Q1, const Quaternion& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q1 );
    XMVECTOR q2 = XMLoadFloat4( &Q2 );

    Quaternion R;
    XMStoreFloat4( &R, XMQuaternionMultiply( q1, q2 ) );
    return R;
}

inline Quaternion operator* (const Quaternion& Q, float S)
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( &Q );

    Quaternion R;
    XMStoreFloat4( &R, XMVectorScale( q, S ) );
    return R;
}

inline Quaternion operator/ (const Quaternion& Q1, const Quaternion& Q2)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q1 );
    XMVECTOR q2 = XMLoadFloat4( &Q2 );
    q2 = XMQuaternionInverse( q2 );

    Quaternion R;
    XMStoreFloat4( &R, XMQuaternionMultiply( q1, q2 ) );
    return R;
}

inline Quaternion operator* (float S, const Quaternion& Q)
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( &Q );

    Quaternion R;
    XMStoreFloat4( &R, XMVectorScale( q1, S ) );
    return R;
}

//------------------------------------------------------------------------------
// Quaternion operations
//------------------------------------------------------------------------------

inline float Quaternion::Length() const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    return XMVectorGetX( XMQuaternionLength( q ) );
}

inline float Quaternion::LengthSquared() const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    return XMVectorGetX( XMQuaternionLengthSq( q ) );
}

inline void Quaternion::Normalize()
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( this, XMQuaternionNormalize( q ) );
}

inline void Quaternion::Normalize( Quaternion& result ) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMQuaternionNormalize( q ) );
}

inline void Quaternion::Conjugate()
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( this, XMQuaternionConjugate( q ) );
}

inline void Quaternion::Conjugate( Quaternion& result ) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMQuaternionConjugate( q ) );
}

inline void Quaternion::Inverse( Quaternion& result ) const
{
    using namespace DirectX;
    XMVECTOR q = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMQuaternionInverse( q ) );
}

inline float Quaternion::Dot( const Quaternion& q ) const
{
    using namespace DirectX;
    XMVECTOR q1 = XMLoadFloat4( this );
    XMVECTOR q2 = XMLoadFloat4( &q );
    return XMVectorGetX( XMQuaternionDot( q1, q2 ) );
}


inline Vector3 Quaternion::EulerAngles() const
{
	using namespace DirectX;
	// Derivation from http://www.geometrictools.com/Documentation/EulerAngles.pdf
	// Order of rotations: Z first, then X, then Y
	static const float M_RADTODEG = XMConvertToDegrees(1.0f);
	float check = 2.0f * (-y * z + w * x);

	if (check < -0.995f)
	{
		return Vector3(
			-90.0f,
			0.0f,
			-atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * M_RADTODEG
			);
	}
	else if (check > 0.995f)
	{
		return Vector3(
			90.0f,
			0.0f,
			atan2f(2.0f * (x * z - w * y), 1.0f - 2.0f * (y * y + z * z)) * M_RADTODEG
			);
	}
	else
	{
		return Vector3(
			asinf(check) * M_RADTODEG,
			atan2f(2.0f * (x * z + w * y), 1.0f - 2.0f * (x * x + y* y)) * M_RADTODEG,
			atan2f(2.0f * (x * y + w * z), 1.0f - 2.0f * (x * x + z* z)) * M_RADTODEG
			);
	}

}


inline void Quaternion::ToAxisAndAngle(Vector3& Axis, float& Angle) const
{
	Angle = 2.f * acosf(w);
	Axis = GetRotationAxis();

}

inline Vector3 Quaternion::GetRotationAxis() const
{
	// Ensure we never try to sqrt a neg number
	//W = cos(a)
	//sin(a) = 1- W*W
	//X = s * Axis.x;  -- > Axis.x = X/s
	//Y = s * Axis.y;
	//Z = s * Axis.z;
	const float S = (1.0f - w*w) >= 0.0f ? (1.0f - w*w) : 0.0f;
	if (S >= 0.0001f)
	{
		return Vector3(x / S, y / S, z / S);
	}

	return Vector3(1.f, 0.f, 0.f);
}

inline void Quaternion::FromAxes(const Vector3& xAxis, const Vector3& yAxis, const Vector3& zAxis)
{
	using namespace DirectX;

	Matrix  m;
	m(0, 0) = xAxis.x;
	m(0, 1) = xAxis.y;
	m(0, 2) = xAxis.z;

	m(1, 0) = yAxis.x;
	m(1, 1) = yAxis.y;
	m(1, 2) = yAxis.z;

	m(2, 0) = zAxis.x;
	m(2, 1) = zAxis.y;
	m(2, 2) = zAxis.z;
	(*this) = CreateFromRotationMatrix(m);
}


inline Quaternion Quaternion::FromLookRotation(const Vector3& direction, const Vector3& upDirection)
{
	using namespace DirectX;

	Quaternion ret;
	Vector3 forward;
	direction.Normalize(forward);
	static const float M_EPSILON = 0.000001f;

	Vector3 v = forward.Cross(upDirection);
	// If direction & upDirection are parallel and crossproduct becomes zero, use FromRotationTo() fallback
	if (v.LengthSquared() >= M_EPSILON)
	{
		v.Normalize();
		Vector3 up = v.Cross(forward);
		Vector3 right = up.Cross(forward);
		 ret.FromAxes(right, up, forward);
	}
	else
		ret = Quaternion::CreateFromRotationTo(Vector3::Backward, forward);
	return ret;
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline Quaternion Quaternion::CreateFromAxisAngle( const Vector3& axis, float angle )
{
    using namespace DirectX;
    XMVECTOR a = XMLoadFloat3( &axis );

    Quaternion R;
    XMStoreFloat4( &R, XMQuaternionRotationAxis( a, angle ) );
    return R;
}

inline Quaternion Quaternion::CreateFromYawPitchRoll( float yaw, float pitch, float roll )
{
    using namespace DirectX;
    Quaternion R;
    XMStoreFloat4( &R, XMQuaternionRotationRollPitchYaw( pitch, yaw, roll ) );
    return R;
}

inline Quaternion Quaternion::CreateFromEulerAngles(float x, float y, float z)
{
#ifndef M_PI
#define M_PI 3.1415926535897932384626433f
#endif
	using namespace DirectX;
	Quaternion R;
	static const float M_DEGTORAD_2 = M_PI / 360.0f;    // M_DEGTORAD / 2.f
	x *= M_DEGTORAD_2;
	y *= M_DEGTORAD_2;
	z *= M_DEGTORAD_2;
	float sinX = sinf(x);
	float cosX = cosf(x);
	float sinY = sinf(y);
	float cosY = cosf(y);
	float sinZ = sinf(z);
	float cosZ = cosf(z);

	R.w = cosY * cosX * cosZ + sinY * sinX * sinZ;
	R.x = cosY * sinX * cosZ + sinY * cosX * sinZ;
	R.y = sinY * cosX * cosZ - cosY * sinX * sinZ;
	R.z = cosY * cosX * sinZ - sinY * sinX * cosZ;

	return R;
}

inline  Quaternion Quaternion::CreateFromRotationTo(const Vector3& start, const Vector3& end)
{
	static const float M_EPSILON = 0.000001f;
	using namespace DirectX;
	Quaternion R;
	Vector3 normStart;
	start.Normalize(normStart);
	Vector3 normEnd;
	end.Normalize(normEnd);
	float d = normStart.Dot(normEnd);
	if (d > -1.0f + M_EPSILON)
	{
		Vector3 c = normStart.Cross(normEnd);
		float s = sqrtf((1.0f + d) * 2.0f);
		float invS = 1.0f / s;

		R.x = c.x * invS;
		R.y = c.y * invS;
		R.z = c.z * invS;
		R.w = 0.5f * s;
	}
	else
	{
		Vector3 axis = Vector3::Right.Cross(normStart);
		if (axis.Length() < M_EPSILON)
			axis = Vector3::Up.Cross(normStart);

		return	CreateFromAngleAxis(180.f, axis);
	}
	return R;

}
inline  Quaternion Quaternion::CreateFromAngleAxis(float angle, const Vector3& axis)
{
	static const float M_DEGTORAD_2 = M_PI / 360.0f;    // M_DEGTORAD / 2.f
	Vector3 normAxis;
	axis.Normalize(normAxis);
	angle *= M_DEGTORAD_2;
	float sinAngle = sinf(angle);
	float cosAngle = cosf(angle);
	using namespace DirectX;
	Quaternion R;

	R.w = cosAngle;
	R.x= normAxis.x * sinAngle;
	R.y= normAxis.y * sinAngle;
	R.z= normAxis.z * sinAngle;
	return R;
}

inline Quaternion Quaternion::FromRotationMatrix(const Matrix& matrix)
{
	using namespace DirectX;
	Quaternion R;
	float t = matrix(0, 0) + matrix(1, 1) + matrix(2, 2);

	if (t > 0.0f)
	{
		float invS = 0.5f / sqrtf(1.0f + t);

		R.x = (matrix(1, 2)  - matrix(2, 1) ) * invS;
		R.y = (matrix(2, 0)  - matrix(0, 2) ) * invS;
		R.z = (matrix(0, 1)  - matrix(1, 0) ) * invS;
		R.w = 0.25f / invS;
	}
	else
	{
		if (matrix(0, 0) > matrix(1, 1) && matrix(0, 0)  >matrix(2, 2))
		{
			float invS = 0.5f / sqrtf(1.0f + matrix(0, 0) - matrix(1, 1) - matrix(2,2));

			R.x = 0.25f / invS;
			R.y = (matrix(1, 0)  +matrix(0, 1)  ) * invS;
			R.z = (matrix(0, 2)  +matrix(2, 0)  ) * invS;
			R.w =( matrix(1, 2) - matrix(2, 1) ) * invS;
		}
		else if (matrix(1, 1)  > matrix(2, 2))
		{
			float invS = 0.5f / sqrtf(1.0f + matrix(1, 1) - matrix(0, 0) - matrix(2, 2));

			R.x = (matrix(1, 0) + matrix(0, 1)) * invS;
			R.y = 0.25f / invS;
			R.z = (matrix(2, 1) + matrix(1, 2)) * invS;
			R.w = (matrix(2, 0) - matrix(0, 2)) * invS;
		}
		else
		{
			float invS = 0.5f / sqrtf(1.0f + matrix(2, 2) - matrix(0, 0) - matrix(1, 1));

			R.x = (matrix(2, 0) + matrix(0, 2)) * invS;
			R.y = (matrix(2, 1) + matrix(1, 2)) * invS;
			R.z = 0.25f / invS;
			R.w = (matrix(0, 1) - matrix(1, 0)) * invS;
		}
	}
	return R;
}


inline Quaternion Quaternion::CreateFromRotationMatrix( const Matrix& M )
{
    using namespace DirectX;
    XMMATRIX M0 = XMLoadFloat4x4( &M );

    Quaternion R;
    XMStoreFloat4( &R, XMQuaternionRotationMatrix( M0 ) );
    return R;
}

inline void Quaternion::Lerp( const Quaternion& q1, const Quaternion& q2, float t, Quaternion& result )
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    XMVECTOR dot = XMVector4Dot( Q0, Q1 );

    XMVECTOR R;
    if ( XMVector4GreaterOrEqual( dot, XMVectorZero() ) )
    {
        R = XMVectorLerp( Q0, Q1, t );
    }
    else
    {
        XMVECTOR tv = XMVectorReplicate( t );
        XMVECTOR t1v = XMVectorReplicate( 1.f - t );
        XMVECTOR X0 = XMVectorMultiply( Q0, t1v );
        XMVECTOR X1 = XMVectorMultiply( Q1, tv );
        R = XMVectorSubtract( X0, X1 );
    }

    XMStoreFloat4( &result, XMQuaternionNormalize( R ) );
}

inline Quaternion Quaternion::Lerp( const Quaternion& q1, const Quaternion& q2, float t )
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    XMVECTOR dot = XMVector4Dot( Q0, Q1 );

    XMVECTOR R;
    if ( XMVector4GreaterOrEqual( dot, XMVectorZero() ) )
    {
        R = XMVectorLerp( Q0, Q1, t );
    }
    else
    {
        XMVECTOR tv = XMVectorReplicate( t );
        XMVECTOR t1v = XMVectorReplicate( 1.f - t );
        XMVECTOR X0 = XMVectorMultiply( Q0, t1v );
        XMVECTOR X1 = XMVectorMultiply( Q1, tv );
        R = XMVectorSubtract( X0, X1 );
    }

    Quaternion result;
    XMStoreFloat4( &result, XMQuaternionNormalize( R ) );
    return result;
}

inline void Quaternion::Slerp( const Quaternion& q1, const Quaternion& q2, float t, Quaternion& result )
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );
    XMStoreFloat4( &result, XMQuaternionSlerp( Q0, Q1, t ) );
}

inline Quaternion Quaternion::Slerp( const Quaternion& q1, const Quaternion& q2, float t )
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    Quaternion result;
    XMStoreFloat4( &result, XMQuaternionSlerp( Q0, Q1, t ) );
    return result;
}

inline void Quaternion::Concatenate( const Quaternion& q1, const Quaternion& q2, Quaternion& result )
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );
    XMStoreFloat4( &result, XMQuaternionMultiply( Q1, Q0 ) );
}

inline Quaternion Quaternion::Concatenate( const Quaternion& q1, const Quaternion& q2 )
{
    using namespace DirectX;
    XMVECTOR Q0 = XMLoadFloat4( &q1 );
    XMVECTOR Q1 = XMLoadFloat4( &q2 );

    Quaternion result;
    XMStoreFloat4( &result, XMQuaternionMultiply( Q1, Q0 ) );
    return result;
}


/****************************************************************************
 *
 * Color
 *
 ****************************************************************************/

inline Color::Color( const DirectX::PackedVector::XMCOLOR& Packed )
{
    using namespace DirectX;
    XMStoreFloat4( this, PackedVector::XMLoadColor( &Packed ) );
}

inline Color::Color( const DirectX::PackedVector::XMUBYTEN4& Packed )
{
    using namespace DirectX;
    XMStoreFloat4( this, PackedVector::XMLoadUByteN4( &Packed ) );
}

//------------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool Color::operator == ( const Color& c ) const
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    return XMColorEqual( c1, c2 );
}

inline bool Color::operator != ( const Color& c ) const
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    return XMColorNotEqual( c1, c2 );
}

//------------------------------------------------------------------------------
// Assignment operators
//------------------------------------------------------------------------------

inline Color& Color::operator+= (const Color& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    XMStoreFloat4( this, XMVectorAdd( c1, c2 ) );
    return *this;
}

inline Color& Color::operator-= (const Color& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    XMStoreFloat4( this, XMVectorSubtract( c1, c2 ) );
    return *this;
}

inline Color& Color::operator*= (const Color& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    XMStoreFloat4( this, XMVectorMultiply( c1, c2 ) );
    return *this;
}

inline Color& Color::operator*= (float S)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMVectorScale( c, S ) );
    return *this;
}

inline Color& Color::operator/= (const Color& c)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( this );
    XMVECTOR c2 = XMLoadFloat4( &c );
    XMStoreFloat4( this, XMVectorDivide( c1, c2 ) );
    return *this;
}

//------------------------------------------------------------------------------
// Urnary operators
//------------------------------------------------------------------------------

inline Color Color::operator- () const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    Color R;
    XMStoreFloat4( &R, XMVectorNegate( c ) );
    return R;
}

//------------------------------------------------------------------------------
// Binary operators
//------------------------------------------------------------------------------

inline Color operator+ (const Color& C1, const Color& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C1 );
    XMVECTOR c2 = XMLoadFloat4( &C2 );
    Color R;
    XMStoreFloat4( &R, XMVectorAdd( c1, c2 ) );
    return R;
}

inline Color operator- (const Color& C1, const Color& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C1 );
    XMVECTOR c2 = XMLoadFloat4( &C2 );
    Color R;
    XMStoreFloat4( &R, XMVectorSubtract( c1, c2 ) );
    return R;
}

inline Color operator* (const Color& C1, const Color& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C1 );
    XMVECTOR c2 = XMLoadFloat4( &C2 );
    Color R;
    XMStoreFloat4( &R, XMVectorMultiply( c1, c2 ) );
    return R;
}

inline Color operator* (const Color& C, float S)
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( &C );
    Color R;
    XMStoreFloat4( &R, XMVectorScale( c, S ) );
    return R;
}

inline Color operator/ (const Color& C1, const Color& C2)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C1 );
    XMVECTOR c2 = XMLoadFloat4( &C2 );
    Color R;
    XMStoreFloat4( &R, XMVectorDivide( c1, c2 ) );
    return R;
}

inline Color operator* (float S, const Color& C)
{
    using namespace DirectX;
    XMVECTOR c1 = XMLoadFloat4( &C );
    Color R;
    XMStoreFloat4( &R, XMVectorScale( c1, S ) );
    return R;
}

//------------------------------------------------------------------------------
// Color operations
//------------------------------------------------------------------------------

inline DirectX::PackedVector::XMCOLOR Color::BGRA() const
{
    using namespace DirectX;
    XMVECTOR clr = XMLoadFloat4( this );
    PackedVector::XMCOLOR Packed;
    PackedVector::XMStoreColor( &Packed, clr );
    return Packed;
}

inline DirectX::PackedVector::XMUBYTEN4 Color::RGBA() const
{
    using namespace DirectX;
    XMVECTOR clr = XMLoadFloat4( this );
    PackedVector::XMUBYTEN4 Packed;
    PackedVector::XMStoreUByteN4( &Packed, clr );
    return Packed;
}

inline Vector3 Color::ToVector3() const
{
    return Vector3( x, y, z );
}

inline Vector4 Color::ToVector4() const
{
    return Vector4( x, y, z, w );
}

inline void Color::Negate()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMColorNegative( c) );
}

inline void Color::Negate( Color& result ) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMColorNegative( c ) );
}

inline void Color::Saturate()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMVectorSaturate( c ) );
}

inline void Color::Saturate( Color& result ) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMVectorSaturate( c ) );
}

inline void Color::Premultiply()
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMVECTOR a = XMVectorSplatW( c );
    a = XMVectorSelect( g_XMIdentityR3, a, g_XMSelect1110 );
    XMStoreFloat4( this, XMVectorMultiply( c, a ) );
}

inline void Color::Premultiply( Color& result ) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMVECTOR a = XMVectorSplatW( c );
    a = XMVectorSelect( g_XMIdentityR3, a, g_XMSelect1110 );
    XMStoreFloat4( &result, XMVectorMultiply( c, a ) );
}

inline void Color::AdjustSaturation( float sat )
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMColorAdjustSaturation( c, sat ) );
}

inline void Color::AdjustSaturation( float sat, Color& result ) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMColorAdjustSaturation( c, sat ) );
}

inline void Color::AdjustContrast( float contrast )
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( this, XMColorAdjustContrast( c, contrast ) );
}

inline void Color::AdjustContrast( float contrast, Color& result ) const
{
    using namespace DirectX;
    XMVECTOR c = XMLoadFloat4( this );
    XMStoreFloat4( &result, XMColorAdjustContrast( c, contrast ) );
}

//------------------------------------------------------------------------------
// Static functions
//------------------------------------------------------------------------------

inline void Color::Modulate( const Color& c1, const Color& c2, Color& result )
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );
    XMStoreFloat4( &result, XMColorModulate( C0, C1 ) );
}

inline Color Color::Modulate( const Color& c1, const Color& c2 )
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );

    Color result;
    XMStoreFloat4( &result, XMColorModulate( C0, C1 ) );
    return result;
}

inline void Color::Lerp( const Color& c1, const Color& c2, float t, Color& result )
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );
    XMStoreFloat4( &result, XMVectorLerp( C0, C1, t ) );
}

inline Color Color::Lerp( const Color& c1, const Color& c2, float t )
{
    using namespace DirectX;
    XMVECTOR C0 = XMLoadFloat4( &c1 );
    XMVECTOR C1 = XMLoadFloat4( &c2 );

    Color result;
    XMStoreFloat4( &result, XMVectorLerp( C0, C1, t ) );
    return result;
}


/****************************************************************************
 *
 * Ray
 *
 ****************************************************************************/

//-----------------------------------------------------------------------------
// Comparision operators
//------------------------------------------------------------------------------
inline bool Ray::operator == ( const Ray& r ) const
{
    using namespace DirectX;
    XMVECTOR r1p = XMLoadFloat3( &position );
    XMVECTOR r2p = XMLoadFloat3( &r.position );
    XMVECTOR r1d = XMLoadFloat3( &direction );
    XMVECTOR r2d = XMLoadFloat3( &r.direction );
    return XMVector3Equal( r1p, r2p ) && XMVector3Equal( r1d, r2d );
}

inline bool Ray::operator != ( const Ray& r ) const
{
    using namespace DirectX;
    XMVECTOR r1p = XMLoadFloat3( &position );
    XMVECTOR r2p = XMLoadFloat3( &r.position );
    XMVECTOR r1d = XMLoadFloat3( &direction );
    XMVECTOR r2d = XMLoadFloat3( &r.direction );
    return XMVector3NotEqual( r1p, r2p ) && XMVector3NotEqual( r1d, r2d );
}

//-----------------------------------------------------------------------------
// Ray operators
//------------------------------------------------------------------------------

inline bool Ray::Intersects( const BoundingSphere& sphere, _Out_ float& Dist ) const
{
    return sphere.Intersects( position, direction, Dist );
}

inline bool Ray::Intersects( const BoundingBox& box, _Out_ float& Dist ) const
{
    return box.Intersects( position, direction, Dist );
}

inline bool Ray::Intersects( const Vector3& tri0, const Vector3& tri1, const Vector3& tri2, _Out_ float& Dist ) const
{
    return DirectX::TriangleTests::Intersects( position, direction, tri0, tri1, tri2, Dist );
}

inline bool Ray::Intersects( const Plane& plane, _Out_ float& Dist ) const
{
    using namespace DirectX;

    XMVECTOR p = XMLoadFloat4( &plane );
    XMVECTOR dir = XMLoadFloat3( &direction );

    XMVECTOR nd = XMPlaneDotNormal( p, dir );

    if ( XMVector3LessOrEqual( XMVectorAbs( nd ), g_RayEpsilon ) )
    {
        Dist = 0.f;
        return false;
    }
    else
    {
        // t = -(dot(n,origin) + D) / dot(n,dir)
        XMVECTOR pos = XMLoadFloat3( &position );
        XMVECTOR v = XMPlaneDotNormal( p, pos );
        v = XMVectorAdd( v, XMVectorSplatW(p) );
        v = XMVectorDivide( v, nd );
        float dist = - XMVectorGetX( v );
        if (dist < 0)
        {
            Dist = 0.f;
            return false;
        }
        else
        {
            Dist = dist;
            return true;
        }
    }
}
