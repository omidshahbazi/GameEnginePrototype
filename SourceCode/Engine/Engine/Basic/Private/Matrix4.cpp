// Copyright 2012-2015 ?????????????. All Rights Reserved.
#include <Public\Matrix4.h>
#include <Public\Vector2.h>
#include <Public\Vector3.h>
#include <Public\CMath.h>

//#define LEFT_HAND_MATRIX

BEGIN_NAMESPACE


const Matrix4 Matrix4::IDENTITY(true);


Matrix4 &Matrix4::operator=(const Matrix4 &Other)
{
	if (this == &Other)
		return *this;

	memcpy(m_Cells, Other.m_Cells, 16 * sizeof(float));

	return *this;
}


Matrix4 &Matrix4::operator=(float32 Scalar)
{
	for (uint32 i = 0; i < 16; ++i)
		m_Cells[i] = Scalar;

	return *this;
}


bool Matrix4::operator==(const Matrix4 &Other) const
{
	for (uint32 i = 0; i < 16; ++i)
	if (m_Cells[i] != Other.m_Cells[i])
		return false;

	return true;
}


bool Matrix4::operator!=(const Matrix4 &Other) const
{
	return !(*this == Other);
}


Matrix4 Matrix4::operator+(const Matrix4 &Other) const
{
	Matrix4 temp(false);

	temp[0] = m_Cells[0] + Other[0];
	temp[1] = m_Cells[1] + Other[1];
	temp[2] = m_Cells[2] + Other[2];
	temp[3] = m_Cells[3] + Other[3];
	temp[4] = m_Cells[4] + Other[4];
	temp[5] = m_Cells[5] + Other[5];
	temp[6] = m_Cells[6] + Other[6];
	temp[7] = m_Cells[7] + Other[7];
	temp[8] = m_Cells[8] + Other[8];
	temp[9] = m_Cells[9] + Other[9];
	temp[10] = m_Cells[10] + Other[10];
	temp[11] = m_Cells[11] + Other[11];
	temp[12] = m_Cells[12] + Other[12];
	temp[13] = m_Cells[13] + Other[13];
	temp[14] = m_Cells[14] + Other[14];
	temp[15] = m_Cells[15] + Other[15];

	return temp;
}


Matrix4 &Matrix4::operator+=(const Matrix4 &Other)
{
	m_Cells[0] += Other[0];
	m_Cells[1] += Other[1];
	m_Cells[2] += Other[2];
	m_Cells[3] += Other[3];
	m_Cells[4] += Other[4];
	m_Cells[5] += Other[5];
	m_Cells[6] += Other[6];
	m_Cells[7] += Other[7];
	m_Cells[8] += Other[8];
	m_Cells[9] += Other[9];
	m_Cells[10] += Other[10];
	m_Cells[11] += Other[11];
	m_Cells[12] += Other[12];
	m_Cells[13] += Other[13];
	m_Cells[14] += Other[14];
	m_Cells[15] += Other[15];

	return *this;
}


Matrix4 Matrix4::operator-(const Matrix4 &Other) const
{
	Matrix4 temp(false);

	temp[0] = m_Cells[0] - Other[0];
	temp[1] = m_Cells[1] - Other[1];
	temp[2] = m_Cells[2] - Other[2];
	temp[3] = m_Cells[3] - Other[3];
	temp[4] = m_Cells[4] - Other[4];
	temp[5] = m_Cells[5] - Other[5];
	temp[6] = m_Cells[6] - Other[6];
	temp[7] = m_Cells[7] - Other[7];
	temp[8] = m_Cells[8] - Other[8];
	temp[9] = m_Cells[9] - Other[9];
	temp[10] = m_Cells[10] - Other[10];
	temp[11] = m_Cells[11] - Other[11];
	temp[12] = m_Cells[12] - Other[12];
	temp[13] = m_Cells[13] - Other[13];
	temp[14] = m_Cells[14] - Other[14];
	temp[15] = m_Cells[15] - Other[15];

	return temp;
}


Matrix4 &Matrix4::operator-=(const Matrix4 &Other)
{
	m_Cells[0] -= Other[0];
	m_Cells[1] -= Other[1];
	m_Cells[2] -= Other[2];
	m_Cells[3] -= Other[3];
	m_Cells[4] -= Other[4];
	m_Cells[5] -= Other[5];
	m_Cells[6] -= Other[6];
	m_Cells[7] -= Other[7];
	m_Cells[8] -= Other[8];
	m_Cells[9] -= Other[9];
	m_Cells[10] -= Other[10];
	m_Cells[11] -= Other[11];
	m_Cells[12] -= Other[12];
	m_Cells[13] -= Other[13];
	m_Cells[14] -= Other[14];
	m_Cells[15] -= Other[15];

	return *this;
}


Matrix4 Matrix4::operator*(const Matrix4 &Matrix) const
{
	Matrix4 ret(false);

	const float32 *m1 = m_Cells;
	const float32 *m2 = Matrix.m_Cells;
	float32 *m3 = ret.m_Cells;

	m3[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	m3[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	m3[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	m3[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

	m3[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	m3[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	m3[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	m3[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

	m3[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	m3[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	m3[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	m3[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

	m3[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	m3[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	m3[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	m3[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

	return ret;
}


Matrix4 &Matrix4::operator*=(const Matrix4 &Other)
{
	const Matrix4 temp(*this);

	const float32 *m1 = temp.m_Cells;
	const float32 *m2 = Other.m_Cells;

	m_Cells[0] = m1[0] * m2[0] + m1[4] * m2[1] + m1[8] * m2[2] + m1[12] * m2[3];
	m_Cells[1] = m1[1] * m2[0] + m1[5] * m2[1] + m1[9] * m2[2] + m1[13] * m2[3];
	m_Cells[2] = m1[2] * m2[0] + m1[6] * m2[1] + m1[10] * m2[2] + m1[14] * m2[3];
	m_Cells[3] = m1[3] * m2[0] + m1[7] * m2[1] + m1[11] * m2[2] + m1[15] * m2[3];

	m_Cells[4] = m1[0] * m2[4] + m1[4] * m2[5] + m1[8] * m2[6] + m1[12] * m2[7];
	m_Cells[5] = m1[1] * m2[4] + m1[5] * m2[5] + m1[9] * m2[6] + m1[13] * m2[7];
	m_Cells[6] = m1[2] * m2[4] + m1[6] * m2[5] + m1[10] * m2[6] + m1[14] * m2[7];
	m_Cells[7] = m1[3] * m2[4] + m1[7] * m2[5] + m1[11] * m2[6] + m1[15] * m2[7];

	m_Cells[8] = m1[0] * m2[8] + m1[4] * m2[9] + m1[8] * m2[10] + m1[12] * m2[11];
	m_Cells[9] = m1[1] * m2[8] + m1[5] * m2[9] + m1[9] * m2[10] + m1[13] * m2[11];
	m_Cells[10] = m1[2] * m2[8] + m1[6] * m2[9] + m1[10] * m2[10] + m1[14] * m2[11];
	m_Cells[11] = m1[3] * m2[8] + m1[7] * m2[9] + m1[11] * m2[10] + m1[15] * m2[11];

	m_Cells[12] = m1[0] * m2[12] + m1[4] * m2[13] + m1[8] * m2[14] + m1[12] * m2[15];
	m_Cells[13] = m1[1] * m2[12] + m1[5] * m2[13] + m1[9] * m2[14] + m1[13] * m2[15];
	m_Cells[14] = m1[2] * m2[12] + m1[6] * m2[13] + m1[10] * m2[14] + m1[14] * m2[15];
	m_Cells[15] = m1[3] * m2[12] + m1[7] * m2[13] + m1[11] * m2[14] + m1[15] * m2[15];

	return *this;
}


Matrix4 Matrix4::operator*(float32 Scalar) const
{
	Matrix4 temp(false);

	temp[0] = m_Cells[0] * Scalar;
	temp[1] = m_Cells[1] * Scalar;
	temp[2] = m_Cells[2] * Scalar;
	temp[3] = m_Cells[3] * Scalar;
	temp[4] = m_Cells[4] * Scalar;
	temp[5] = m_Cells[5] * Scalar;
	temp[6] = m_Cells[6] * Scalar;
	temp[7] = m_Cells[7] * Scalar;
	temp[8] = m_Cells[8] * Scalar;
	temp[9] = m_Cells[9] * Scalar;
	temp[10] = m_Cells[10] * Scalar;
	temp[11] = m_Cells[11] * Scalar;
	temp[12] = m_Cells[12] * Scalar;
	temp[13] = m_Cells[13] * Scalar;
	temp[14] = m_Cells[14] * Scalar;
	temp[15] = m_Cells[15] * Scalar;

	return temp;
}


Matrix4 &Matrix4::operator*=(float32 Scalar)
{
	m_Cells[0] *= Scalar;
	m_Cells[1] *= Scalar;
	m_Cells[2] *= Scalar;
	m_Cells[3] *= Scalar;
	m_Cells[4] *= Scalar;
	m_Cells[5] *= Scalar;
	m_Cells[6] *= Scalar;
	m_Cells[7] *= Scalar;
	m_Cells[8] *= Scalar;
	m_Cells[9] *= Scalar;
	m_Cells[10] *= Scalar;
	m_Cells[11] *= Scalar;
	m_Cells[12] *= Scalar;
	m_Cells[13] *= Scalar;
	m_Cells[14] *= Scalar;
	m_Cells[15] *= Scalar;

	return *this;
}


Matrix4 &Matrix4::MakeInverse(void)
{
	Matrix4 temp(false);

	const Matrix4 &m = *this;

	float32 d = (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) -
		(m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
		(m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)) +
		(m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) -
		(m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
		(m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0));

	//if (Math::IsZero(d, FLT_MIN))
	//	return false;

	d = Math::Reciprocal(d);

	temp(0, 0) = d * (m(1, 1) * (m(2, 2) * m(3, 3) - m(2, 3) * m(3, 2)) +
		m(1, 2) * (m(2, 3) * m(3, 1) - m(2, 1) * m(3, 3)) +
		m(1, 3) * (m(2, 1) * m(3, 2) - m(2, 2) * m(3, 1)));
	temp(0, 1) = d * (m(2, 1) * (m(0, 2) * m(3, 3) - m(0, 3) * m(3, 2)) +
		m(2, 2) * (m(0, 3) * m(3, 1) - m(0, 1) * m(3, 3)) +
		m(2, 3) * (m(0, 1) * m(3, 2) - m(0, 2) * m(3, 1)));
	temp(0, 2) = d * (m(3, 1) * (m(0, 2) * m(1, 3) - m(0, 3) * m(1, 2)) +
		m(3, 2) * (m(0, 3) * m(1, 1) - m(0, 1) * m(1, 3)) +
		m(3, 3) * (m(0, 1) * m(1, 2) - m(0, 2) * m(1, 1)));
	temp(0, 3) = d * (m(0, 1) * (m(1, 3) * m(2, 2) - m(1, 2) * m(2, 3)) +
		m(0, 2) * (m(1, 1) * m(2, 3) - m(1, 3) * m(2, 1)) +
		m(0, 3) * (m(1, 2) * m(2, 1) - m(1, 1) * m(2, 2)));
	temp(1, 0) = d * (m(1, 2) * (m(2, 0) * m(3, 3) - m(2, 3) * m(3, 0)) +
		m(1, 3) * (m(2, 2) * m(3, 0) - m(2, 0) * m(3, 2)) +
		m(1, 0) * (m(2, 3) * m(3, 2) - m(2, 2) * m(3, 3)));
	temp(1, 1) = d * (m(2, 2) * (m(0, 0) * m(3, 3) - m(0, 3) * m(3, 0)) +
		m(2, 3) * (m(0, 2) * m(3, 0) - m(0, 0) * m(3, 2)) +
		m(2, 0) * (m(0, 3) * m(3, 2) - m(0, 2) * m(3, 3)));
	temp(1, 2) = d * (m(3, 2) * (m(0, 0) * m(1, 3) - m(0, 3) * m(1, 0)) +
		m(3, 3) * (m(0, 2) * m(1, 0) - m(0, 0) * m(1, 2)) +
		m(3, 0) * (m(0, 3) * m(1, 2) - m(0, 2) * m(1, 3)));
	temp(1, 3) = d * (m(0, 2) * (m(1, 3) * m(2, 0) - m(1, 0) * m(2, 3)) +
		m(0, 3) * (m(1, 0) * m(2, 2) - m(1, 2) * m(2, 0)) +
		m(0, 0) * (m(1, 2) * m(2, 3) - m(1, 3) * m(2, 2)));
	temp(2, 0) = d * (m(1, 3) * (m(2, 0) * m(3, 1) - m(2, 1) * m(3, 0)) +
		m(1, 0) * (m(2, 1) * m(3, 3) - m(2, 3) * m(3, 1)) +
		m(1, 1) * (m(2, 3) * m(3, 0) - m(2, 0) * m(3, 3)));
	temp(2, 1) = d * (m(2, 3) * (m(0, 0) * m(3, 1) - m(0, 1) * m(3, 0)) +
		m(2, 0) * (m(0, 1) * m(3, 3) - m(0, 3) * m(3, 1)) +
		m(2, 1) * (m(0, 3) * m(3, 0) - m(0, 0) * m(3, 3)));
	temp(2, 2) = d * (m(3, 3) * (m(0, 0) * m(1, 1) - m(0, 1) * m(1, 0)) +
		m(3, 0) * (m(0, 1) * m(1, 3) - m(0, 3) * m(1, 1)) +
		m(3, 1) * (m(0, 3) * m(1, 0) - m(0, 0) * m(1, 3)));
	temp(2, 3) = d * (m(0, 3) * (m(1, 1) * m(2, 0) - m(1, 0) * m(2, 1)) +
		m(0, 0) * (m(1, 3) * m(2, 1) - m(1, 1) * m(2, 3)) +
		m(0, 1) * (m(1, 0) * m(2, 3) - m(1, 3) * m(2, 0)));
	temp(3, 0) = d * (m(1, 0) * (m(2, 2) * m(3, 1) - m(2, 1) * m(3, 2)) +
		m(1, 1) * (m(2, 0) * m(3, 2) - m(2, 2) * m(3, 0)) +
		m(1, 2) * (m(2, 1) * m(3, 0) - m(2, 0) * m(3, 1)));
	temp(3, 1) = d * (m(2, 0) * (m(0, 2) * m(3, 1) - m(0, 1) * m(3, 2)) +
		m(2, 1) * (m(0, 0) * m(3, 2) - m(0, 2) * m(3, 0)) +
		m(2, 2) * (m(0, 1) * m(3, 0) - m(0, 0) * m(3, 1)));
	temp(3, 2) = d * (m(3, 0) * (m(0, 2) * m(1, 1) - m(0, 1) * m(1, 2)) +
		m(3, 1) * (m(0, 0) * m(1, 2) - m(0, 2) * m(1, 0)) +
		m(3, 2) * (m(0, 1) * m(1, 0) - m(0, 0) * m(1, 1)));
	temp(3, 3) = d * (m(0, 0) * (m(1, 1) * m(2, 2) - m(1, 2) * m(2, 1)) +
		m(0, 1) * (m(1, 2) * m(2, 0) - m(1, 0) * m(2, 2)) +
		m(0, 2) * (m(1, 0) * m(2, 1) - m(1, 1) * m(2, 0)));

	*this = temp;

	return *this;
}


Matrix4 Matrix4::GetInverse(void) const
{
	Matrix4 mat(*this);
	mat.MakeInverse();
	return mat;
}


Matrix4 &Matrix4::MakeIdentity(void)
{
	memset(m_Cells, 0, 16 * sizeof(float32));
	m_Cells[0] = m_Cells[5] = m_Cells[10] = m_Cells[15] = 1;

	return *this;
}


bool Matrix4::IsIdentity(void) const
{
	if (!Math::EqualCheck(m_Cells[12], 0) || !Math::EqualCheck(m_Cells[13], 0) || !Math::EqualCheck(m_Cells[14], 0) || !Math::EqualCheck(m_Cells[15], 1))
		return false;

	if (!Math::EqualCheck(m_Cells[0], 1) || !Math::EqualCheck(m_Cells[1], 0) || !Math::EqualCheck(m_Cells[2], 0) || !Math::EqualCheck(m_Cells[3], 0))
		return false;

	if (!Math::EqualCheck(m_Cells[4], 0) || !Math::EqualCheck(m_Cells[5], 1) || !Math::EqualCheck(m_Cells[6], 0) || !Math::EqualCheck(m_Cells[7], 0))
		return false;

	if (!Math::EqualCheck(m_Cells[8], 0) || !Math::EqualCheck(m_Cells[9], 0) || !Math::EqualCheck(m_Cells[10], 1) || !Math::EqualCheck(m_Cells[11], 0))
		return false;

	return true;
}


Matrix4 &Matrix4::Set(const Vector3 &Translation, const Vector3 &Rotation, const Vector3 &Scale)
{
	m_Cells[12] = Translation.X;
	m_Cells[13] = Translation.Y;
	m_Cells[14] = Translation.Z;

	SetRotation(Rotation);

	m_Cells[0] = Scale.X;
	m_Cells[5] = Scale.Y;
	m_Cells[10] = Scale.Z;

	return *this;
}


Matrix4 &Matrix4::SetPosition(const Vector3 &Translation)
{
	m_Cells[12] = Translation.X;
	m_Cells[13] = Translation.Y;
	m_Cells[14] = Translation.Z;

	return *this;
}


Matrix4 &Matrix4::SetPosition(float32 X, float32 Y, float32 Z)
{
	m_Cells[12] = X;
	m_Cells[13] = Y;
	m_Cells[14] = Z;

	return *this;
}


Vector3 Matrix4::GetPosition(void) const
{
	return Vector3(m_Cells[12], m_Cells[13], m_Cells[14]);
}


Matrix4 &Matrix4::SetRotation(const Vector3 &Rotation)
{
	return SetRotation(Rotation.X, Rotation.Y, Rotation.Z);
}


Matrix4 &Matrix4::SetRotation(float32 X, float32 Y, float32 Z)
{
	const float32 radiansX = X * Math::DEGREES_TO_RADIANS,
		radiansY = Y * Math::DEGREES_TO_RADIANS,
		radiansZ = Z * Math::DEGREES_TO_RADIANS;

	const float32 cr = cos(radiansX);
	const float32 sr = sin(radiansX);
	const float32 cp = cos(radiansY);
	const float32 sp = sin(radiansY);
	const float32 cy = cos(radiansZ);
	const float32 sy = sin(radiansZ);

	m_Cells[0] = (cp*cy);
	m_Cells[1] = (cp*sy);
	m_Cells[2] = (-sp);

	const float32 srsp = sr*sp;
	const float32 crsp = cr*sp;

	m_Cells[4] = (srsp*cy - cr*sy);
	m_Cells[5] = (srsp*sy + cr*cy);
	m_Cells[6] = (sr*cp);

	m_Cells[8] = (crsp*cy + sr*sy);
	m_Cells[9] = (crsp*sy - sr*cy);
	m_Cells[10] = (cr*cp);

	return *this;
}


Vector3 Matrix4::GetRotation(void) const
{
	const Matrix4 &mat = *this;
	Vector3 scale = GetScale();
	// we need to check for negative scale on to axes, which would bring up wrong results
	if (scale.Y < 0 && scale.Z < 0)
	{
		scale.Y = -scale.Y;
		scale.Z = -scale.Z;
	}
	else if (scale.X < 0 && scale.Z < 0)
	{
		scale.X = -scale.X;
		scale.Z = -scale.Z;
	}
	else if (scale.X < 0 && scale.Y < 0)
	{
		scale.X = -scale.X;
		scale.Y = -scale.Y;
	}
	const Vector3 invScale(Math::Reciprocal(scale.X), Math::Reciprocal(scale.Y), Math::Reciprocal(scale.Z));

	float32 Y = -asin(Math::Clamp(mat[2] * invScale.X, -1.0F, 1.0F));
	const float32 C = cos(Y);
	Y *= Math::RADIANS_TO_DEGREES;

	float32 rotx, roty, X, Z;

	if (!Math::IsZero(C))
	{
		const float32 invC = Math::Reciprocal(C);
		rotx = mat[10] * invC * invScale.Z;
		roty = mat[6] * invC * invScale.Y;
		X = atan2(roty, rotx) * Math::RADIANS_TO_DEGREES;
		rotx = mat[0] * invC * invScale.X;
		roty = mat[1] * invC * invScale.X;
		Z = atan2(roty, rotx) * Math::RADIANS_TO_DEGREES;
	}
	else
	{
		X = 0.0;
		rotx = mat[5] * invScale.Y;
		roty = -mat[4] * invScale.Y;
		Z = atan2(roty, rotx) * Math::RADIANS_TO_DEGREES;
	}

	// fix values that get below zero
	if (X < 0.0) X += 360.0;
	if (Y < 0.0) Y += 360.0;
	if (Z < 0.0) Z += 360.0;

	return Vector3(X, Y, Z);
}


Matrix4 &Matrix4::SetScale(const Vector3 &Scale)
{
	m_Cells[0] = Scale.X;
	m_Cells[5] = Scale.Y;
	m_Cells[10] = Scale.Z;

	return *this;
}


Matrix4 &Matrix4::SetScale(float32 X, float32 Y, float32 Z)
{
	m_Cells[0] = X;
	m_Cells[5] = Y;
	m_Cells[10] = Z;

	return *this;
}


Matrix4 &Matrix4::SetScale(float32 Scalar)
{
	m_Cells[0] = m_Cells[5] = m_Cells[10] = Scalar;

	return *this;
}


Vector3 Matrix4::GetScale(void) const
{
	// See http://www.robertblum.com/articles/2005/02/14/decomposing-matrices

	if (Math::IsZero(m_Cells[1]) && Math::IsZero(m_Cells[2]) &&
		Math::IsZero(m_Cells[4]) && Math::IsZero(m_Cells[6]) &&
		Math::IsZero(m_Cells[8]) && Math::IsZero(m_Cells[9]))
		return Vector3(m_Cells[0], m_Cells[5], m_Cells[10]);

	// We have to do the full calculation.
	return Vector3(
		Math::SquareRoot(m_Cells[0] * m_Cells[0] + m_Cells[1] * m_Cells[1] + m_Cells[2] * m_Cells[2]),
		Math::SquareRoot(m_Cells[4] * m_Cells[4] + m_Cells[5] * m_Cells[5] + m_Cells[6] * m_Cells[6]),
		Math::SquareRoot(m_Cells[8] * m_Cells[8] + m_Cells[9] * m_Cells[9] + m_Cells[10] * m_Cells[10]));
}


Vector3 Matrix4::GetRight(void) const
{
	return Vector3(m_Cells[0], m_Cells[4], m_Cells[8]).Normalized();
}


Vector3 Matrix4::GetUp(void) const
{
	return Vector3(m_Cells[1], m_Cells[5], m_Cells[9]).Normalized();
}


Vector3 Matrix4::GetForward(void) const
{
	return Vector3(m_Cells[2], m_Cells[6], m_Cells[10]).Normalized()
#ifndef LEFT_HAND_MATRIX
		* -1
#endif
		;
}


void Matrix4::SetRotationCenter(const Vector3 &Center, const Vector3 &Translation)
{
	m_Cells[12] = -m_Cells[0] * Center.X - m_Cells[4] * Center.Y - m_Cells[8] * Center.Z + (Center.X - Translation.X);
	m_Cells[13] = -m_Cells[1] * Center.X - m_Cells[5] * Center.Y - m_Cells[9] * Center.Z + (Center.Y - Translation.Y);
	m_Cells[14] = -m_Cells[2] * Center.X - m_Cells[6] * Center.Y - m_Cells[10] * Center.Z + (Center.Z - Translation.Z);
	m_Cells[15] = 1.0F;
}


void Matrix4::TransformVector(Vector3 &Vector) const
{
	Vector.X = Vector.X*m_Cells[0] + Vector.Y*m_Cells[4] + Vector.Z*m_Cells[8] + m_Cells[12];
	Vector.Y = Vector.X*m_Cells[1] + Vector.Y*m_Cells[5] + Vector.Z*m_Cells[9] + m_Cells[13];
	Vector.Z = Vector.X*m_Cells[2] + Vector.Y*m_Cells[6] + Vector.Z*m_Cells[10] + m_Cells[14];
}


void Matrix4::TranslateVector(Vector3 &Vector) const
{
	Vector.X += m_Cells[12];
	Vector.Y += m_Cells[13];
	Vector.Z += m_Cells[14];
}


void Matrix4::RotateVector(Vector3 &Vector) const
{
	Vector3 tmp(Vector);
	Vector.X = tmp.X*m_Cells[0] + tmp.Y*m_Cells[4] + tmp.Z*m_Cells[8];
	Vector.Y = tmp.X*m_Cells[1] + tmp.Y*m_Cells[5] + tmp.Z*m_Cells[9];
	Vector.Z = tmp.X*m_Cells[2] + tmp.Y*m_Cells[6] + tmp.Z*m_Cells[10];
}


void Matrix4::MakePerspectiveProjectionMatrix(float32 FieldOfView, float32 AspectRatio, float32 NearClipDistance, float32 FarClipDistance)
{
	ASSERTION_LOG(AspectRatio != 0.0F, "AspectRatio must be non-zero, devide by zero will happen")
	ASSERTION_LOG(NearClipDistance != FarClipDistance, "NearClipDistance and FarClipDistance cannot equals, devide by zero will happen")

	const float32 h = Math::Reciprocal(tan((FieldOfView * Math::DEGREES_TO_RADIANS) * 0.5F));
	const float32 w = h / AspectRatio;

#ifdef LEFT_HAND_MATRIX
	m_Cells[0] = w;
	m_Cells[1] = 0.0F;
	m_Cells[2] = 0.0F;
	m_Cells[3] = 0.0F;

	m_Cells[4] = 0.0F;
	m_Cells[5] = h;
	m_Cells[6] = 0.0F;
	m_Cells[7] = 0.0F;

	m_Cells[8] = 0.0F;
	m_Cells[9] = 0.0F;
	m_Cells[10] = FarClipDistance / (FarClipDistance - NearClipDistance);
	m_Cells[11] = 1.0F;

	m_Cells[12] = 0.0F;
	m_Cells[13] = 0.0F;
	m_Cells[14] = -NearClipDistance * FarClipDistance / (FarClipDistance - NearClipDistance);
	m_Cells[15] = 0.0F;
#else
	m_Cells[0] = w;
	m_Cells[1] = 0.0F;
	m_Cells[2] = 0.0F;
	m_Cells[3] = 0.0F;

	m_Cells[4] = 0.0F;
	m_Cells[5] = h;
	m_Cells[6] = 0.0F;
	m_Cells[7] = 0.0F;

	m_Cells[8] = 0.0F;
	m_Cells[9] = 0.0F;
	m_Cells[10] = FarClipDistance / (NearClipDistance - FarClipDistance); // DirectX version
	//m_Cells[10] = FarClipDistance + NearClipDistance / (NearClipDistance - FarClipDistance)); // OpenGL version
	m_Cells[11] = -1.0F;

	m_Cells[12] = 0.0F;
	m_Cells[13] = 0.0F;
	m_Cells[14] = NearClipDistance * FarClipDistance / (NearClipDistance - FarClipDistance); // DirectX version
	//m_Cells[14] = 2.0F * NearClipDistance * FarClipDistance/ (NearClipDistance - FarClipDistance); // OpenGL version
	m_Cells[15] = 0.0F;
#endif
}


void Matrix4::MakeOrthographicProjectionMatrix(float32 Width, float32 Height, float32 NearClipDistance, float32 FarClipDistance)
{
	ASSERTION_LOG(Width != 0, "Width must be non-zero, devide by zero will happen")
	ASSERTION_LOG(Height != 0, "Width must be non-zero, devide by zero will happen")
	ASSERTION_LOG(NearClipDistance != FarClipDistance, "NearClipDistance and FarClipDistance cannot equals, devide by zero will happen")

#ifdef LEFT_HAND_MATRIX
	m_Cells[0] = 2.0F / Width;
	m_Cells[1] = 0.0F;
	m_Cells[2] = 0.0F;
	m_Cells[3] = 0.0F;

	m_Cells[4] = 0.0F;
	m_Cells[5] = 2.0F / Height;
	m_Cells[6] = 0.0F;
	m_Cells[7] = 0.0F;

	m_Cells[8] = 0.0F;
	m_Cells[9] = 0.0F;
	m_Cells[10] = 1.0F / (FarClipDistance - NearClipDistance);
	m_Cells[11] = 0.0F;

	m_Cells[12] = 0.0F;
	m_Cells[13] = 0.0F;
	m_Cells[14] = NearClipDistance / (NearClipDistance - FarClipDistance);
	m_Cells[15] = 1.0F;
#else
	m_Cells[0] = 2.0F / Width;
	m_Cells[1] = 0.0F;
	m_Cells[2] = 0.0F;
	m_Cells[3] = 0.0F;

	m_Cells[4] = 0.0F;
	m_Cells[5] = 2.0F / Height;
	m_Cells[6] = 0.0F;
	m_Cells[7] = 0.0F;

	m_Cells[8] = 0.0F;
	m_Cells[9] = 0.0F;
	m_Cells[10] = 1.0F / (NearClipDistance - FarClipDistance);
	m_Cells[11] = 0.0F;

	m_Cells[12] = 0.0F;
	m_Cells[13] = 0.0F;
	m_Cells[14] = NearClipDistance / (NearClipDistance - FarClipDistance);
	m_Cells[15] = 1.0F;
#endif
}

END_NAMESPACE
