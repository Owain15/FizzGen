
#include "FizzGen.h"

class Sandbox : public FizzGen::Application
{
	public:
	
		Sandbox()
		{
		
		}
	
		~Sandbox()
		{
		
		}
	
};

FizzGen::Application* FizzGen::CreateApplication()
{
	return new Sandbox();
}
