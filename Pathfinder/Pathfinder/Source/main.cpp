#include "Graphics/Window.h"
#include "Graphics/Vulkan/VulkanRenderer.h"
#include "Pathfinder.h"
#include "Timer.h"

int main()
{
	// TODO: Move to application layer

	Window appWindow(1200, 720, "Pathfinder");
	VulkanRenderer vulkanRenderer(&appWindow);
	Pathfinder pathfinder{};
	Timer timer{};

	for (size_t i = 0; i < pathfinder.GetGrid().size(); ++i)
	{
		for (size_t j = 0; j < pathfinder.GetGrid()[i].size(); ++j)
		{
			vulkanRenderer.RegisterEntity(pathfinder.GetGrid()[i][j].get());
		}
	}

	while (!appWindow.ShouldWindowClose())
	{
		const double dt = timer.GetDeltaTime();

		vulkanRenderer.DrawFrame();
		pathfinder.DisplayPathAnimated(dt);
		appWindow.Update();
	}
}