#pragma once

#include "StringHash.h"
#include "HpD3D9Type.h"


#define OBJECT(typeName) \
    public: \
        typedef typeName ClassName; \
        virtual StringHash GetType() const { return GetTypeStatic(); } \
        virtual StringHash GetBaseType() const { return GetBaseTypeStatic(); } \
        virtual const String& GetTypeName() const { return GetTypeNameStatic(); } \
        static StringHash GetTypeStatic() { static const StringHash typeStatic(#typeName); return typeStatic; } \
        static const String& GetTypeNameStatic() { static const String typeNameStatic(#typeName); return typeNameStatic; } 

#define BASEOBJECT(typeName) \
    public: \
        static StringHash GetBaseTypeStatic() { static const StringHash baseTypeStatic(#typeName); return baseTypeStatic; } 
