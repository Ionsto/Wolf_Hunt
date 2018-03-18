#include "bitmap_image.hpp"
#include <iostream>
#include <Wolf_Hunt\RenderComponents.h>
#include <Wolf_Hunt\SystemRender.h>
struct Colour {
	float R, G, B;
	Colour(float r = 0, float g = 0, float b = 0) : R(r), G(g), B(b) {};
};

Colour RayToRGB(Sim::ComponentRenderRay & ray)
{
	static const Colour ColourMapping[5] = { Colour(255,255,255),Colour(0,0,0),Colour(255,0,0),Colour(0,255,0),Colour(0,0,255) };
	auto rawcolour = ColourMapping[ray.Colour];
	static const auto maxcolour = ColourMapping[0];
	float blendfactor = ray.Distance / ray.MaxDistance;
	return Colour(((rawcolour.R*(1 - blendfactor)) + (maxcolour.R*blendfactor)),
		((rawcolour.G*(1 - blendfactor)) + (maxcolour.G*blendfactor)),
		((rawcolour.B*(1 - blendfactor)) + (maxcolour.B*blendfactor)));
}

void DrawCamera(Sim::ComponentRenderCamera & camera,std::string output)
{
	static const int Size = 1000;
	static const int DistMultiply = (Size/2)/ Sim::ComponentRenderRay::MaxDistance *0.95;
	cartesian_canvas canvas(Size, Size);
	canvas.pen_color(0, 0, 0);
	canvas.fill_rectangle(-Size /2, -Size / 2, Size /2, Size /2);

	static const float SampleSlice = Sim::ComponentRenderCamera::FOV / (Sim::ComponentRenderCamera::SampleCount);
	static const float HalfSampleCount = (Sim::ComponentRenderCamera::SampleCount - 1) / 2.0;
	float RayAngle = camera.Rotation - HalfSampleCount;
	Sim::Vector<float> CameraPos = camera.Position;
	for (int s = 0; s < Sim::ComponentRenderCamera::SampleCount; ++s)
	{
		RayAngle += SampleSlice;
		Sim::Vector<float> RayLocation = camera.Position + (Sim::Vector<float>(cos(RayAngle), sin(RayAngle))*camera.Rays[s].Distance)*DistMultiply;
		Colour col = RayToRGB(camera.Rays[s]);
		canvas.pen_color(col.R, col.G, col.B);
		canvas.fill_circle(RayLocation.X, RayLocation.Y, 2);
	}
	canvas.image().save_image(output);
}
int main(int argc, char **args)
{
	Sim::SystemRender render = Sim::SystemRender();
	auto camera = render.AddCamera(Sim::ComponentRenderCamera());
	render.AddCircle(Sim::ComponentRenderCircle(Sim::Vector<float>(5, 0), 2));
	render.AddCircle(Sim::ComponentRenderCircle(Sim::Vector<float>(-5,2), 2));
	render.AddCircle(Sim::ComponentRenderCircle(Sim::Vector<float>(0, 10), 2));
	render.AddCircle(Sim::ComponentRenderCircle(Sim::Vector<float>(5, 5), 2));
	for (int i = 0; i < 60;++i)
	{
		render.RenderScene();
		render.GetCamera(camera).Rotation += 6 * (3.14 / 180.0);
		DrawCamera(render.GetCamera(camera),"./Render/image_"+std::to_string(i)+".bmp");
		std::cout << i << std::endl;
	}
	return 0;
}