#include "Entity.h"
#include "World.h"
#include <math.h>

Sim::Entity::Entity()
{
	Type = EntityTypes::Other;
	this->WorldObj = nullptr;
	Acceleration = Vector<float>();
	Alive = true;
	DeathCallbacks = std::vector<std::function<void(Entity*)>*>();
}

Sim::Entity::Entity(World * wrld) : Entity()
{
	this->WorldObj = wrld;
	IDRenderObject = wrld->WorldRender.AddCircle(Sim::ComponentRenderCircle(Pos, Size, 2));
	if (!IDRenderObject.Valid)
	{
		ValidObject = false;
	}
}

Sim::Entity::~Entity()
{
	//clean up
	//WorldObj->WorldGrid[GridID.X][GridID.Y].RemoveEntity(this);
	for (auto & callback : DeathCallbacks)
	{
		(*callback)(this);
	}
	if (IDRenderObject.Valid)
	{
		std::cout << "Delete circle from: " << (unsigned int)this << "\n";
		WorldObj->WorldRender.RemoveCircle(IDRenderObject);
	}
}

void Sim::Entity::SetLocation(Vector<float> pos)
{
	Pos = pos;
	PosOld = pos;
	Vector<int> NewGridID = WorldObj->GetGridIDs(Pos);
	if (NewGridID != GridID)
	{
		//Update Grid
		WorldObj->WorldGrid[NewGridID.X][NewGridID.Y].AddEntity(this);
		WorldObj->WorldGrid[GridID.X][GridID.Y].RemoveEntity(this);
		GridID = NewGridID;
	}
	auto & Object = WorldObj->WorldRender.GetCircle(IDRenderObject);
	Object.Position = Pos;
}

void Sim::Entity::ApplyFriction()
{
	if (OnFloor)
	{
		auto Velocity = GetVelocity();
		float Mag = sqrt(Velocity.DotXY(Velocity));
		//Cubic friction
		float FrictionFactor = 0.1;// pow(LinearDamp, WorldObj->DeltaTime)/50;
		//Acceleration = Acceleration * (fmaxf(0, (2 - exp(Mag / 50))));
		this->PosOld += (this->Pos - this->PosOld) * FrictionFactor;
		if (Mag < 0.01)
		{
			//this->Pos = this->PosOld;
		}
		//RotAcc -= RotVel * abs(RotVel) * AngularDamp;
		RotVel *= pow(AngularDamp,WorldObj->DeltaTime);
	}
}
void Sim::Entity::Update()
{
	ApplyFriction();
	Acceleration.Z -= WorldObj->Gravity;
	Intergrate();
	EnforceBoundry();
	UpdateRenderObject();
}
void Sim::Entity::UpdateRenderObject()
{
	auto & Object = WorldObj->WorldRender.GetCircle(IDRenderObject);
	Object.Position = Pos;
}
void Sim::Entity::EnforceBoundry()
{
	if (Pos.X < 0)
	{
		Pos.X = 0;
		PosOld.X = 0;
	}
	if (Pos.Y < 0)
	{
		Pos.Y = 0;
		PosOld.Y = 0;
	}
	if (Pos.X > WorldObj->WorldSize)
	{
		Pos.X = WorldObj->WorldSize;
		PosOld.X = WorldObj->WorldSize;
	}
	if (Pos.Y > WorldObj->WorldSize)
	{
		Pos.Y = WorldObj->WorldSize;
		PosOld.Y = WorldObj->WorldSize;
	}
	if (Pos.Z <= 0)
	{
		Pos.Z = 0;
		OnFloor = true;
	}
	else
	{
		OnFloor = false;
	}
}
void Sim::Entity::Intergrate()
{
	//Linear intergration
	Vector<float> NewOld = this->Pos;
	Pos += (Pos - PosOld) + (Acceleration * WorldObj->DeltaTime * WorldObj->DeltaTime);
	PosOld = NewOld;
	Rot += RotVel * WorldObj->DeltaTime;
	RotVel += RotAcc * WorldObj->DeltaTime;
	while (abs(Rot) > PI)
	{
		int dir = 2 * (Rot / abs(Rot));
		Rot -= PI * dir;
	}
	RotAcc = 0;
	Acceleration = Vector<float>();
}
void Sim::Entity::Kill()
{
	//Do death stuff
	Alive = false;
}
void Sim::Entity::ApplyForce(Vector<float> force)
{
	this->Acceleration += force / Mass;
}

float Sim::Entity::NormaliseAngle(float angle)
{
	while (abs(angle) > PI)
	{
		angle -= PI * 2 * (angle / abs(angle));
	}
	return angle;
}

void Sim::Entity::ApplyMoment(float moment)
{
	//Model moment of inertia as mass
	RotAcc += moment / Mass;
}

//Aprox
Sim::Vector<float> Sim::Entity::GetVelocity()
{
	return (Pos - PosOld) / WorldObj->DeltaTime;
}
void Sim::Entity::Collision(Entity * ent)
{
	
}
void Sim::Entity::RegisterDeath(std::function<void(Entity*)> * func)
{
	this->DeathCallbacks.push_back(func);
}
void Sim::Entity::UnRegisterDeath(std::function<void(Entity*)> * func)
{
	auto location = std::find(this->DeathCallbacks.begin(), this->DeathCallbacks.end(), func);
	if (location != this->DeathCallbacks.end())
	{
		this->DeathCallbacks.erase(location);
	}
}