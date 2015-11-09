// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef SECONDARYCOMMON_H
#define SECONDARYCOMMON_H

#define USE_NAMESPACE
#ifdef USE_NAMESPACE
#define NAMESPACE IE

#define BEGIN_NAMESPACE namespace NAMESPACE \
							{
#define END_NAMESPACE	}

#define USING_NAMESPACE using namespace NAMESPACE;
#else
#define NAMESPACE

#define BEGIN_NAMESPACE
#define END_NAMESPACE

#define USING_NAMESPACE
#endif

#define EXTERN_C extern "C"
#define DLL_EXPORT __declspec(dllexport)
#define DLL_IMPORT __declspec(dllimport)
//
//#ifdef DECLARE_DLL
//#define CORE_API DLL_EXPORT
//#else
//#define CORE_API DLL_IMPORT
//#endif


#define USE_FUNCTION_INLINING
#ifdef USE_FUNCTION_INLINING
#define INLINE __forceinline
#else
#define INLINE
#endif


#ifndef NULL
#define NULL 0
#endif

#define STRINGIZE(Value) #Value

BEGIN_NAMESPACE

typedef unsigned char uchar;
typedef char int8;
typedef unsigned char uint8;
typedef short int16;
typedef unsigned short uint16;
typedef int int32;
typedef unsigned int uint32;
typedef long int64;
typedef unsigned long uint64;
typedef float float32;
typedef long float float64;
typedef double double32;
typedef long double double64;

END_NAMESPACE
#endif // SECONDARYCOMMON_H
