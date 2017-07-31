#pragma once
#include "Vector.h"
namespace Sim {
	class World;
	class Entity
	{
	public:
		float LinearDamp;
		Vector<float> Pos;
		Vector<float> PosOld;
		Vector<float> Acceleration;
		float Mass = 1;
		float Size = 10;
		float Rot;
		float RotOld;
		float RotAcc;
		bool Alive;
		//Global ID refrence
		int Id;
		World * WorldObj;
		//
		Vector<int> GridID;
		Entity(World * wrld);
		~Entity();
		virtual void Update();
		void Intergrate();
		void EnforceBoundry();
		virtual void SetLocation(Vector<float> pos);
		void ApplyForce(Vector<float> force);
		//Clean up everything
		void Kill();
	};
};