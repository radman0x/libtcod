
#ifndef LIBTCOD_TILESET_TILE_H_
#define LIBTCOD_TILESET_TILE_H_
#include <stdint.h>
#ifdef __cplusplus
#include <algorithm>
#include <vector>
#endif

#include "../libtcod_portability.h"
#include "../color/canvas.h"
#ifdef __cplusplus
namespace tcod {
class Tile {
 public:
  Tile();
  Tile(int width, int height): canvas_(width, height) {};
  Tile(const Canvas &canvas): canvas_(canvas) {};

  Tile(Tile&&) = default;
  Tile& operator=(Tile&&) = default;
  Tile(const Tile&) = default;
  Tile& operator=(const Tile&) = default;

  int width(void) const { return canvas_.width(); }
  int height(void) const { return canvas_.height(); }
 private:
  Canvas canvas_;
};
} // namespace tcod
#endif // __cplusplus
#endif // LIBTCOD_TILESET_TILE_H_
