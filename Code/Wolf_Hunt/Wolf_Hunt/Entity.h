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
		float Mass;
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
		//Clean up everything
		void Kill();
	};
};