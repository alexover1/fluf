#pragma once
#include <glad.h>
#include <imgui.h>
#include <functional>

namespace tests
{
	class Test
	{
	public:
		Test() {}
		virtual ~Test() {}

		virtual void on_update(float dt) {}
		virtual void on_render() {}
		virtual void on_imgui_render() {}
	};

	class TestMenu : public Test
	{
	public:
		TestMenu(Test*& current_test_ptr);

		virtual void on_imgui_render() override;

		template<typename T>
		void register_test(const std::string& name)
		{
			m_tests.push_back(std::make_pair(name, []() { return new T(); }));
		}

	private:
		Test*& m_current_test;
		std::vector<std::pair<std::string, std::function<Test* ()>>> m_tests;
	};
}