//---------------------------------------------------------------
// Copyright 2021, Ed Keenan, all rights reserved.
//---------------------------------------------------------------

#ifndef PARTICLEEMITTER_H
#define PARTICLEEMITTER_H

#include "Matrix.h"
#include "Vect4D.h"
#include "Particle.h"

#include <list>

class __declspec(align(16)) ParticleEmitter
{
public:
	ParticleEmitter();
	~ParticleEmitter();
	ParticleEmitter(const ParticleEmitter& p) = default;
	

	void SpawnParticle();
	void update();
	void draw();

	void addParticleToList(Particle& const p );
	void removeParticleFromList( Particle& const p );

	void Execute(Vect4D& const pos, Vect4D& const vel, Vect4D& const sc);

private:
	Vect4D	start_position;//24 8 alignment
	Vect4D	start_velocity;//24 8 alignment
	;
	
	const int		max_particles;//4
	int		last_active_particle;
	float	spawn_frequency;
	float	last_spawn;
	float	last_loop;

	// added for speed efficiency
	int bufferCount;
	Particle *headParticle;
	Vect4D	vel_variance;
	Vect4D	pos_variance;
	float	max_life;//4
	float	scale_variance;
	//std::list<Particle> drawBuffer;
	//Particle drawBuffer[1000];
	//Particle* drawBuffer = new Particle[100000];
	Particle* drawBuffer = (Particle*)_aligned_malloc(sizeof(Particle) * 100000, 16);
	//std::list<Particle> particle_list;
	
	Particle* buffer = (Particle*)_aligned_malloc(sizeof(Particle) * 100000, 16);
	Particle* spawn = buffer;
	Particle* walk = buffer;
};

#endif 

// --- End of File ---
