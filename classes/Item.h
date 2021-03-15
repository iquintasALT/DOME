#pragma once
#include <string>
#include "../sdlutils/SDLUtils.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"
#include "../components/Image.h"
#include "../components/Transform.h"
#include "../components/Inventory.h"

class Inventory;
class ItemInfo {
private:
	ItemInfo(std::string name, std::string description, int width, int height, Texture* texture) :
		_name(name), _description(description), _width(width), _height(height), _texture(texture) {};
	std::string _name;
	std::string _description;
	int _width;
	int _height;
	Texture* _texture;

public:
	inline std::string name() { return _name; };
	inline std::string description() { return _description; };
	inline int width() { return _width; };
	inline int height() { return _height; };
	inline Texture* texture() { return _texture; };

	static ItemInfo* bottleOfWater();
};

class Item
{
	friend class Inventory;
public:
	Item(ItemInfo* info, Manager* mnger, Inventory* inventory, int xPos = 0, int yPos = 0);
	~Item();
	void render();
	void update();
private:
	ItemInfo* info;
	int x, y;
	int width, height;
	Entity* image;
};


