#pragma once
#include "Vector.h"
#include <vector>
#include <functional>
namespace Sim {
	class World;
	class Entity
	{
	public:
		const float PI = 3.14159;
		float LinearDamp;
		float AngularDamp;
		Vector<float> Pos;
		Vector<float> PosOld;
		Vector<float> Acceleration;
		float Mass = 1;
		float Size = 10;
		float Rot = 0;
		float RotVel = 0;
		float RotAcc = 0;
		bool Alive = true;
		bool OnFloor = true;
		std::vector<std::function<void(Entity*)>*> DeathCallbacks;
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
		void ApplyMoment(float moment);
		virtual void ApplyFriction();
		//Clean up everything
		virtual void Kill();
		float NormaliseAngle(float angle);
		Vector<float> GetVelocity();
		virtual void Collision(Entity * ent);
		void RegisterDeath(std::function<void(Entity*)>*);
		void UnRegisterDeath(std::function<void(Entity*)>*);
	};
};