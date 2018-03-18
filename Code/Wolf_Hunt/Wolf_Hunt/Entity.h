#pragma once
#include "Vector.h"
#include <vector>
#include <functional>
#include "ComponentID.h"
namespace Sim {
	class World;
	class Entity
	{
	protected:
	public:
		ComponentIDRenderObject IDRenderObject;
		ComponentIDCollision IDCollision;
		enum EntityTypes {
			Other, Wolf, Sheep, Corpse, Fox
		} Type;
		const float PI = 3.14159;
		static constexpr float LinearDamp = 1e-10;
		static constexpr float AngularDamp = .005;
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
		Entity();
		Entity(World * wrld);
		virtual ~Entity();
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