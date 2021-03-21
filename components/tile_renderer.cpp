#include "tile_renderer.h"
#include "../classes/camera.h"

TileRenderer::TileRenderer(Texture* tset, int x, int y, int tx, int ty, int w, int h)
	: sheet(tset), x(x), y(y), tx(tx), ty(ty), width(w), height(h) { }

void TileRenderer::render() {
	if (sheet != nullptr) {
		bool shouldRender = true;
		Vector2D worldPos(x, y);
		Vector2D pos = Camera::mainCamera->renderRect(worldPos, width, height, shouldRender);
		
		if (!shouldRender) return;

		SDL_Rect src;
		src.x = tx; src.y = ty;
		src.w = width; src.h = height;

		SDL_Rect dest;
		dest.x = pos.getX(); dest.y = pos.getY();
		dest.w = src.w; dest.h = src.h;

		sheet->render(src, dest);
	}
}