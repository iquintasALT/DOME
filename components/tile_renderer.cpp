#include "tile_renderer.h"
#include "../classes/camera.h"

TileRenderer::TileRenderer(Texture* tset, int x, int y, int tx, int ty, int w, int h)
	: sheet(tset), x(x), y(y), tx(tx), ty(ty), width(w), height(h) { }

void TileRenderer::render() {
	if (sheet != nullptr) {
		bool shouldRender = true;
		Vector2D worldPos(x, y);
		Vector2D pos = Camera::mainCamera->renderRect(worldPos, width, height, shouldRender);
		float scale = Camera::mainCamera->getScale();
		if (!shouldRender) return;

		SDL_Rect src;
		src.x = tx; src.y = ty;
		src.w = width; src.h = height;

		SDL_Rect dest;
		dest.x = floor(pos.getX() * scale); 
		dest.y = floor(pos.getY() * scale);
		dest.w = ceil(src.w * scale); 
		dest.h = ceil(src.h * scale);

		sheet->render(src, dest);
	}
}