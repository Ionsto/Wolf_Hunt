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
		static constexpr float MaxDistance = 200;
		float Distance;
		int Colour;
	};

	struct Colour {
		float R, G, B;
		Colour(float r = 0, float g = 0, float b = 0) : R(r), G(g), B(b) {};
		Colour(Sim::ComponentRenderRay & ray)
		{
			static const Colour ColourMapping[6] = { Colour(1,1,1),Colour(0,0,0),Colour(1,0,0),Colour(0,1,0),Colour(0,0,1),Colour(1,0,1) };
			auto rawcolour = ColourMapping[ray.Colour];
			static const auto maxcolour = ColourMapping[0];
			float blendfactor = ray.Distance / ray.MaxDistance;
			R = ((rawcolour.R*(1 - blendfactor)) + (maxcolour.R*blendfactor));
			G = ((rawcolour.G*(1 - blendfactor)) + (maxcolour.G*blendfactor));
			B = ((rawcolour.B*(1 - blendfactor)) + (maxcolour.B*blendfactor));
		}

	};

	struct ComponentRenderCamera {
		static constexpr int SampleCount = 50;
		static constexpr float FOV = 150.0f*(3.14f/180.0f);
		Vector<float> Position;
		float Rotation;
		std::array<ComponentRenderRay, SampleCount> Rays;
	};
}