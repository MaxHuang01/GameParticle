//---------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#include "Vect4D.h"

Vect4D::Vect4D()
{
	this->x = 0.0;
	this->y = 0.0;
	this->z = 0.0;
	this->w = 1.0;
}

Vect4D::Vect4D(float tx, float ty, float tz, float tw )
{
	this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;
}

Vect4D::~Vect4D()
{
	// nothing to delete
}

Vect4D::Vect4D(const Vect4D& v) 
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}


void Vect4D::operator=(const Vect4D& v) 
{
	this->x = v.x;
	this->y = v.y;
	this->z = v.z;
	this->w = v.w;
}


void Vect4D::norm(Vect4D& out)
{
	//float mag = sqrt( this->x * this->x + this->y * this->y + this->z * this->z );

	float mag = SqrtOpt(this->x * this->x + this->y * this->y + this->z * this->z);

	if( 0.0f < mag )
	{
		out.x = this->x / mag;
		out.y = this->y / mag;
		out.z = this->z / mag;
		out.w = 1.0;
	}
}

Vect4D Vect4D::operator + ( Vect4D &t ) 
{
	/*Vect4D out;
	
	out.x = this->x + t.x;
	out.y = this->y + t.y;
	out.z = this->z + t.z;

	return out;*/
	return Vect4D(this->x + t.x, this->y + t.y, this->z + t.z);
}

Vect4D Vect4D::operator - ( Vect4D &t )
{
	/*Vect4D out;
	
	out.x = this->x - t.x;
	out.y = this->y - t.y;
	out.z = this->z - t.z;

	return out;*/

	return Vect4D(this->x - t.x, this->y - t.y, this->z - t.z);
}

Vect4D Vect4D::operator *(float scale)
{
	/*Vect4D tmp;

	tmp.x = this->x * scale;
	tmp.y = this->y * scale;
	tmp.z = this->z * scale;

	return tmp;*/

	return Vect4D(this->x * scale, this->y * scale, this->z * scale);
}

float & Vect4D::operator[]( Vect e )
{
	switch(e)
	{
	case Vect::x:
			return x;
			break;
	case Vect::y:
			return y;
			break;
	case Vect::z:
			return z;
			break;
	case Vect::w:
			return w;
			break;
	default:
			assert(0);
			return x;
	}
}

void Vect4D::Cross( Vect4D& vin, Vect4D& vout)
{
	vout.x = (y*vin.z - z*vin.y);
	vout.y = (z*vin.x - x*vin.z);
	vout.z = (x*vin.y - y*vin.x);
	vout.w = 1.0f;

	/*Vect4D org = *this;
	__m128 om;
	__m128 rm;

	om = this->m;
	rm = vin.m;




	Vect4D A1;
	Vect4D B1;

	Vect4D A2;
	Vect4D B2;



	A1.m = _mm_shuffle_ps(om, om, _MM_SHUFFLE(3, 0, 2, 1));
	B1.m = _mm_shuffle_ps(rm, rm, _MM_SHUFFLE(3, 1, 0, 2));
	A1.m = _mm_mul_ps(_mm_shuffle_ps(om, om, _MM_SHUFFLE(3, 0, 2, 1)), _mm_shuffle_ps(rm, rm, _MM_SHUFFLE(3, 1, 0, 2)));

	A2.m = _mm_shuffle_ps(om, om, _MM_SHUFFLE(3, 1, 0, 2));
	B2.m = _mm_shuffle_ps(rm, rm, _MM_SHUFFLE(3, 0, 2, 1));
	A2.m = _mm_mul_ps(_mm_shuffle_ps(om, om, _MM_SHUFFLE(3, 1, 0, 2)), _mm_shuffle_ps(rm, rm, _MM_SHUFFLE(3, 0, 2, 1)));

	B1.m = _mm_sub_ps(A1.m, A2.m);

	vout = B1;*/
}

void Vect4D::set(float tx, float ty, float tz, float tw)
{
	this->x = tx;
	this->y = ty;
	this->z = tz;
	this->w = tw;
}

// --- End of File ---


float Vect4D::SqrtOpt(float k)
{
	float xhalf = 0.5f * k;
	int i = *(int*)&k; // get bits for floating value
	i = 0x5f375a86 - (i >> 1); // gives initial guess y0
	k = *(float*)&i; // convert bits back to float
	k = k * (1.5f - xhalf * k * k); // Newton step, repeating increases accuracy
	return 1.0f / k; // return sqrt root
}

void Vect4D::set(float t)
{
	this->m = _mm_set1_ps(t);
};