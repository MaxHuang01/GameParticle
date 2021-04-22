//---------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#ifndef PARTICLE_H
#define PARTICLE_H

// include
#include "Vect4D.h"

class __declspec(align(16)) Particle
{
public:
	friend class ParticleEmitter;
	
	Particle();	//default
	~Particle();//des
	Particle(const Particle& p) = delete;//copy
	void operator=(const Particle& p);//assignment

	void Update(const float& time_elapsed);
	void CopyDataOnly( const Particle &p );
private:
	Particle *next;
	Particle *prev;

	Vect4D	prev_Row0;
	Vect4D	prev_Row1;
	Vect4D  prev_Row2;
	Vect4D  prev_Row3;

	Vect4D	position;
	float	life;
	float	rotation;
	Vect4D	velocity;
	Vect4D	scale;
	
	Vect4D  diff_Row0;
	Vect4D  diff_Row1;
	Vect4D  diff_Row2;
	Vect4D  diff_Row3;
	float	rotation_velocity;
	char pad1 = '0';
	char pad2 = '0';
	char pad3 = '0';
	char pad4 = '0';

	
	Vect4D	curr_Row0;
	Vect4D	curr_Row1;
	Vect4D  curr_Row2;
	Vect4D  curr_Row3;
};

#endif 

// --- End of File ---
