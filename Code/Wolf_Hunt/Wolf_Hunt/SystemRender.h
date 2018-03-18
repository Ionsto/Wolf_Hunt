#pragma once
#include "Vector.h"
#include <iostream>
#include <array>
#include <math.h>
#include "ComponentID.h"
#include "SwapList.h"
#include "RenderComponents.h"
namespace Sim {
	class SystemRender
	{
	private:
		static const int MaxCicles = 1000;
		static const int MaxCameras = 1000;
		SwapList<ComponentRenderCircle> SListCircle;
		SwapList<ComponentRenderCamera> SListCamera;
	public:
		SystemRender();
		~SystemRender();
		ComponentIDRenderObject AddCircle(ComponentRenderCircle circle) { 
			std::cout << "Added circle\n";
			return ComponentIDRenderObject(SListCircle.AddItem(circle));
		};
		ComponentIDRenderCamera AddCamera(ComponentRenderCamera camera) {
			std::cout << "Added camera\n";
			return ComponentIDRenderCamera(SListCamera.AddItem(camera));
		};
		void RemoveCircle(ComponentIDRenderObject id) {
			std::cout << "remove circle\n";
			SListCircle.RemoveItem(id.swpId); };
		void RemoveCamera(ComponentIDRenderCamera id) {
			std::cout << "remove camera\n";
			SListCamera.RemoveItem(id.swpId); };
		void RenderScene();
		inline void RenderCamera(int camera);
		inline ComponentRenderCamera & GetCamera(ComponentIDRenderCamera ids)
		{
			return SListCamera.GetItem(ids.swpId);
		}
		inline ComponentRenderCircle & GetCircle(ComponentIDRenderObject ids)
		{
			return SListCircle.GetItem(ids.swpId);
		}
	};
}
