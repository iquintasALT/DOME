#include "map.h"

Tile::Tile(Texture* tset, int x, int y, int tx, int ty, int w, int h)
	: sheet(tset), x(x), y(y), tx(tx), ty(ty), width(w), height(h) { }

void Tile::draw() {
    if (sheet != nullptr) {
        SDL_Rect src;
        src.x = tx;
        src.y = ty;
        src.w = width;
        src.h = height;

        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        dest.w = src.w;
        dest.h = src.h;

        sheet->render(src, dest);
    }
}