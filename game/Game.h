// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <memory>

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;

class Game {
public:
	Game(int totaltime); 
	virtual ~Game();
	void init();
	void start();
	void timerupdate();
private:
	std::unique_ptr<Manager> mngr_;
	int lefttime;
	int starttime;
	int updatetime;
};

