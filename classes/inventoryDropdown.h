#pragma once

#include "../sdlutils/Texture.h"
#include <string>
#include <vector>
#include <functional>

class InventoryDropdown {

public:
	class slot {
	public:
		std::function<void()> function;
		Texture* texture;
		slot(std::string text, std::function<void()> f);
		~slot();
	};

	InventoryDropdown(Texture* texture, std::vector<slot*> slots, float width);
	~InventoryDropdown();
	void render(bool isActive = true);
	bool onClick(Vector2D& const mousePos, bool isActive = true);
	void setPos(Vector2D& pos);
private:
	float width;
	Vector2D position;
	std::vector<slot*> slots;
	Texture* texture;
};
