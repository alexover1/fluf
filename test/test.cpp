#include "test.h"

using namespace tests;

TestMenu::TestMenu(Test*& current_test_ptr)
	: m_current_test(current_test_ptr)
{

}

void TestMenu::on_imgui_render()
{
	for (auto& test : m_tests)
	{
		if (ImGui::Button(test.first.c_str()))
		{
			m_current_test = test.second();
		}
	}
}