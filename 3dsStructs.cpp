#include "3dsStructs.h"

CVector3::CVector3(float X, float Y, float Z)
{
	x = X;
	y = X;
	z = Z;
}

CVector3::CVector3()
{
	x = 0;
	y = 0;
	z = 0;
}

CVector3 CVector3::operator +(CVector3 v1)
{
	return CVector3(x+v1.x, y+v1.y, z+v1.z);
}

CVector3 CVector3::operator -(CVector3 v1)
{
	return CVector3(x-v1.x, y-v1.y, z-v1.z);
}

CVector3 CVector3::operator *(float num)
{
	return CVector3(x*num, y*num, z*num);
}

CVector3 CVector3::operator /(float num)
{
	return CVector3(x/num, y/num, z/num);
}

/**************************************************/
CVector3 Cross(CVector3 v1, CVector3 v2)
{
	CVector3 normal;

	normal.x = (v1.y*v2.z - v2.y*v1.z);
	normal.y = (v1.z*v2.x - v1.x*v2.z);
	normal.z = (v1.x*v2.y - v2.x*v1.y);

	return normal;
}

float Magnitude(CVector3 v1)
{
	return sqrt(v1.x*v1.x + v1.y*v1.y + v1.z*v1.z);
}

CVector3 Normalize(CVector3 v1)
{
	float Mag = Magnitude(v1);

	v1 = v1 / Mag;

	return v1;
}

/**************************************************/
