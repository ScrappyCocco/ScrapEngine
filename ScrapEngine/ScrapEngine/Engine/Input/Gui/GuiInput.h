#pragma once

namespace ScrapEngine
{
	namespace Input
	{
		class GuiInput
		{
		public:
			static void update_mouse_location(double x, double y);
			static void update_mouse_click(bool left, bool right);
			static void update_delta_time(float time);
		};
	}
}
