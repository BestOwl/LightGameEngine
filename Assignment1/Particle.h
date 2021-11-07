#pragma once
#include "GameObject.h"
#include "NaiveEngineUtil.h"

namespace NaiveEngine
{

	typedef Color ParticleColor;

	class Particle :
		public GameObject
	{
	public:
		/// <summary>
		/// Initialize a Particle object
		/// </summary>
		/// <param name="x">Init x pos</param>
		/// <param name="y">Init y pos</param>
		/// <param name="dissolveTime">After dissolveTime (in ticks), this object will destroty itself</param>
		Particle(GLfloat x, GLfloat y, GLint dissolveTime, ParticleColor color);
		virtual void Draw();
		virtual bool Tick();

	private:
		GLint dissolveTime;
		ParticleColor color;
	};

}

