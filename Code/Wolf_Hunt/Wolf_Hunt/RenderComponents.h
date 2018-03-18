#pragma once
#include "Vector.h"
#include <array>
#include <math.h>
#include "ComponentID.h"
namespace Sim {
	struct ComponentRenderCircle {
		ComponentRenderCircle() {};
		ComponentRenderCircle(Vector<float> pos, float Radius = 1, short colour = 2) {
			Position = pos;
			RadiusSquared = Radius * Radius;
			Colour = colour;
		};
		Vector<float> Position;
		float RadiusSquared;
		short Colour;
	};

	struct ComponentRenderRay
	{
		static constexpr float MaxDistance = 350;
		float Distance;
		int Colour;
	};

	struct ComponentRenderCamera {
		static constexpr int SampleCount = 50;
		static constexpr float FOV = 100.0f*(3.14f/180.0f);
		Vector<float> Position;
		float Rotation;
		std::array<ComponentRenderRay, SampleCount> Rays;
	};
}