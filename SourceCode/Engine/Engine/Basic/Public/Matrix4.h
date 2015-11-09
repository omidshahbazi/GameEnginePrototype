// Copyright 2012-2015 ?????????????. All Rights Reserved.
#ifndef MATRIX4_H
#define MATRIX4_H

#include <Public\Common.h>
#include <Public\SmallObjectAllocationPolicy.h>

BEGIN_NAMESPACE

struct Vector2;
struct Vector3;

struct BASIC_API Matrix4
{
public:
	INLINE Matrix4(bool SetIdentity = false)
	{
		if (SetIdentity)
			MakeIdentity();
	}

	INLINE Matrix4(const Matrix4 &Other)
	{
		*this = Other;
	}

	INLINE const float32 *GetPointer(void) const
	{
		return m_Cells;
	}
	INLINE 	float32 *GetPointer(void)
	{
		return m_Cells;
	}

	INLINE float32 &operator()(int32 Row, int32 Column)
	{
		return m_Cells[Row * 4 + Column];
	}

	INLINE float32 operator()(int32 Row, int32 Column) const
	{
		return m_Cells[Row * 4 + Column];
	}

	INLINE float32 &operator[](int32 Index)
	{
		return m_Cells[Index];
	}

	INLINE float32 operator[](int32 Index) const
	{
		return m_Cells[Index];
	}

	Matrix4 &operator=(const Matrix4 &Other);

	Matrix4 &operator=(float32 Scalar);

	bool operator==(const Matrix4 &Other) const;

	bool operator!=(const Matrix4 &Other) const;

	Matrix4 operator+(const Matrix4 &Other) const;

	Matrix4 &operator+=(const Matrix4 &Other);

	Matrix4 operator-(const Matrix4 &Other) const;

	Matrix4 &operator-=(const Matrix4 &Other);

	Matrix4 operator*(const Matrix4 &Other) const;

	Matrix4 &operator*=(const Matrix4 &Other);

	Matrix4 operator*(float32 Scalar) const;

	Matrix4 &operator*=(float32 Scalar);

	Matrix4 &MakeInverse(void);

	Matrix4 GetInverse(void) const;

	Matrix4 &MakeIdentity(void);

	bool IsIdentity(void) const;

	Matrix4 &Set(const Vector3 &Translation, const Vector3 &Rotation, const Vector3 &Scale);

	Matrix4 &SetPosition(const Vector3 &Translation);

	Matrix4 &SetPosition(float32 X, float32 Y, float32 Z);

	Vector3 GetPosition(void) const;

	Matrix4 &SetRotation(const Vector3 &Rotation);

	Matrix4 &SetRotation(float32 X, float32 Y, float32 Z);

	Vector3 GetRotation(void) const;

	Matrix4 &SetScale(const Vector3 &Scale);

	Matrix4 &SetScale(float32 X, float32 Y, float32 Z);

	Matrix4 &SetScale(float32 Scalar);

	Vector3 GetScale(void) const;

	Vector3 GetRight(void) const;
	Vector3 GetUp(void) const;
	Vector3 GetForward(void) const;

	void SetRotationCenter(const Vector3 &Center, const Vector3 &Translate);

	void TransformVector(Vector3 &Vector) const;

	void TranslateVector(Vector3 &Vector) const;

	void RotateVector(Vector3 &Vector) const;

	void MakePerspectiveProjectionMatrix(float32 FieldOfView, float32 AspectRatio, float32 NearClipDistance, float32 FarClipDistance);
	void MakeOrthographicProjectionMatrix(float32 Width, float32 Height, float32 NearClipDistance, float32 FarClipDistance);

private:
	float32 m_Cells[16];

public:
	static const Matrix4 IDENTITY;
};

END_NAMESPACE
#endif // MATRIX4_H
