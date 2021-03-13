#pragma once
#include <string>
#include "../sdlutils/SDLUtils.h"

class Inventory;
class ItemInfo {
private:
	ItemInfo(std::string name, std::string description, int width, int height, Texture* texture) :
		_name(name), _description(description), _width(width), _height(height), texture(texture) {};
	std::string _name;
	std::string _description;
	int _width;
	int _height;
	Texture* texture;

public:
	inline std::string name() { return _name; };
	inline std::string description() { return _description; };
	inline int width() { return _width; };
	inline int height() { return _height; };

	static ItemInfo* bottleOfWater();
};

class Item
{
	friend Inventory;
public:
	Item(ItemInfo* info, int xPos = 0, int yPos = 0);
	~Item();
private:
	ItemInfo* info;
	int x, y;
	int width, height;
};


