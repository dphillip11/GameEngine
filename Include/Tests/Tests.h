#pragma once
namespace TestSuite
{
	class Test {
	private:
		static std::vector<Test*> tests;
		std::string m_name;
		std::function<bool()> m_test;

	public:
		Test(std::string name, std::function<bool()> test) : m_name(name), m_test(test) {
			tests.push_back(this);
		}

		bool Run() {
			return m_test();
		}

		static void RunTests() {
			for (auto test : tests) {
				auto status = test->Run() ? "PASSED " : "FAILED ";
				std::cout << status << test->m_name << " test" << std::endl;
			}
		}
	};

	extern void RunTests();
};

