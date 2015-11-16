#ifndef SCRIPT_HPP
#define SCRIPT_HPP

#include <string>

#include "LuaCpp/LuaCpp.hpp"

class Script
{
	public:
		Script();
		~Script() = default;
		
		// loads a script from a file, and runs it to initialize the script
		// true if loading and running succesful, false otherwise
		// should log errors
		bool openFile(const std::string& file);
		
		// given the name of a function in the Lua script, will call it
		template<typename... Args>
		void call(const std::string& function, Args&&... args);
		
	protected:
		lna::State luaState;
};

template<typename... Args>
void Script::call(const std::string& function, Args&&... args)
{
	luaState[function](args...);
	
	// ignore any returns
	luaState.clean();
}

#endif
