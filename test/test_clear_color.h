#pragma once
#include "test.h"

namespace tests
{
	class TestClearColor : public Test
	{
	private:
		float m_clear_color[4];

	public:
		TestClearColor();

		void on_render() override;
		void on_imgui_render() override;
	};
}