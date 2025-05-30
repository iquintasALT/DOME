// This file is part of the course TPV2@UCM - Samir Genaim

#include <iostream>
#include <memory>

#include "./utils/checkML.h"
#include "./game/Game.h"
#include <GlassHouse.h>
#include <iostream>

void start() {
	Game g(8000);

	GlassHouse::init(SerializerType::Json, PersistorType::Local);
	g.init();
	try {
		g.start();
	}
	catch(...)
	{
		GlassHouse::emergencyClose();
	}
	GlassHouse::close();
}

int main(int, char**) {
	//memory leaks
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	try {
		start();
	} catch (const std::string &e) { // catch exceptions thrown as strings
		std::cerr << e << std::endl;
	} catch (const char *e) { // catch exceptions thrown as char*
		std::cerr << e << std::endl;
	} catch (const std::exception &e) { // catch exceptions thrown as a sub-type of std::exception
		std::cerr << e.what();
	} catch (...) {
		std::cerr << "Caught an exception of unknown type ...";
	}

	return 0;
}

