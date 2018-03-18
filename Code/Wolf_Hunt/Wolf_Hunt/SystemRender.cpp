#include "SystemRender.h"



Sim::SystemRender::SystemRender()
{
	SListCircle = SwapList<ComponentRenderCircle>();
	SListCamera = SwapList<ComponentRenderCamera>();
}


Sim::SystemRender::~SystemRender()
{
}
void Sim::SystemRender::RenderScene()
{
#pragma omp parallel for
	for (int i = 0; i < SListCamera.ActiveItems; ++i)
	{
		RenderCamera(i);
	}
}
void Sim::SystemRender::RenderCamera(int camid)
{
	static const float SampleSlice = ComponentRenderCamera::FOV / (ComponentRenderCamera::SampleCount);
	static const float HalfSampleCount = (ComponentRenderCamera::SampleCount - 1) / 2.0;
	auto & camera = SListCamera.ItemPool[camid];//remove
	float RayAngle = camera.Rotation - (SampleSlice*HalfSampleCount);
	Sim::Vector<float> CameraPos = camera.Position;
	for (int s = 0; s < ComponentRenderCamera::SampleCount; ++s)
	{
		camera.Rays[s].Distance = ComponentRenderRay::MaxDistance;
		camera.Rays[s].Colour = 0;
		RayAngle += SampleSlice;
		Sim::Vector<float> RayDir = Sim::Vector<float>(cos(RayAngle),sin(RayAngle));
		//Minimise yo cache misses
		for (int i = 0; i < SListCircle.ActiveItems; ++i)
		{
			Sim::Vector<float> TCircle = SListCircle.ItemPool[i].Position - CameraPos;
			float a = 1;
			float b = -2*RayDir.DotXY(TCircle);
			float c = TCircle.DotXY(TCircle) - SListCircle.ItemPool[i].RadiusSquared;
			float Disc = ((b*b) - 4*c);
			if (Disc > 0)
			{
				float Distance = 0.5*(-b - std::sqrtf(Disc));
				//Intersection
				if (Distance > 0 && Distance < camera.Rays[s].Distance)
				{
					camera.Rays[s].Distance = Distance;
					camera.Rays[s].Colour = SListCircle.ItemPool[i].Colour;
				}
			}
		}
	}
}