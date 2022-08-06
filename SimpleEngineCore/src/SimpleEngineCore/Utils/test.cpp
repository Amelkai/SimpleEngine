#include <iostream>

#include "SimpleEngineCore/Utils/test.hpp"

namespace SimpleEngine
{
	void SimpleEngine::sayHello()
	{
		std::cout << "Hello Simple Engine core" << std::endl;

		std::cin.get();
	}
}
