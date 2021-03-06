#include "test_clear_color.h"

using namespace tests;

TestClearColor::TestClearColor()
	: m_clear_color{0.2f, 0.3f, 0.8f, 1.0f }
{
}

void TestClearColor::on_render()
{
	glClearColor(m_clear_color[0], m_clear_color[1], m_clear_color[2], m_clear_color[3]);
	glClear(GL_COLOR_BUFFER_BIT);
}


void TestClearColor::on_imgui_render()
{
	ImGui::ColorEdit4("Clear Color", m_clear_color);
}