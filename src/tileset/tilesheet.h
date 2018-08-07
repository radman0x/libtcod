
#ifndef LIBTCOD_TILESET_TILESHEET_H_
#define LIBTCOD_TILESET_TILESHEET_H_
#ifdef __cplusplus
#include <string>
#endif // __cplusplus

#include "../color/canvas.h"
#include "tile.h"
#ifdef __cplusplus
namespace tcod {
/**
 *  The layout of tiles on a tile-sheet.
 */
struct TilesheetLayout {
  int tile_width;
  int tile_height;
  int columns;
  int rows;
};
class Tilesheet {
 public:
  Tilesheet() = default;
  explicit Tilesheet(const Canvas& canvas, const TilesheetLayout& layout)
  : canvas_(canvas), layout_(layout) {
    fill_layout();
  }
  Tilesheet(Tilesheet&&) = default;
  Tilesheet& operator=(Tilesheet&&) = default;
  Tilesheet(const Tilesheet&) = default;
  Tilesheet& operator=(const Tilesheet&) = default;
  /**
   *  Return the Tile at `x` and `y`.
   */
  Tile get_tile(int x, int y) const {
    if (!(0 <= x && x < layout_.columns && 0 <= y && y < layout_.rows)) {
      throw std::out_of_range("Tile not in Tilesheet layout.");
    }
    return new_tile(x * layout_.tile_width, y * layout_.tile_height,
                    layout_.tile_width, layout_.tile_height);
  }
  /**
   *  Return the Tile at `n`.
   */
  Tile get_tile(int n) const {
    return get_tile(n % layout_.columns, n / layout_.columns);
  }
 private:
  /**
   *  Automatically fill values which are 0 in layout_.
   */
  void fill_layout() {
    // Find undefined columns/rows from tile size and canvas_ size.
    if (layout_.columns == 0 && layout_.tile_width > 0) {
      layout_.columns = canvas_.width() / layout_.tile_width;
    }
    if (layout_.rows == 0 && layout_.tile_height > 0) {
      layout_.rows = canvas_.height() / layout_.tile_height;
    }
    // Find undefined tile width/height from columns/rows and canvas_ size.
    if (layout_.tile_width == 0 && layout_.columns > 0) {
      layout_.tile_width = canvas_.width() / layout_.columns;
    }
    if (layout_.tile_height == 0 && layout_.rows > 0) {
      layout_.tile_height = canvas_.height() / layout_.rows;
    }
    if (!layout_.columns || !layout_.rows) {
      throw std::logic_error("Tilesheet layout is non-valid.");
    }
  }
  /**
   *  Return a new Tile from the given region on the Tilesheet.
   */
  Tile new_tile(int x, int y, int width, int height) const {
    Canvas tile_canvas = Canvas(width, height);
    for (int pixel_y = 0; pixel_y < height; ++pixel_y) {
      for (int pixel_x = 0; pixel_x < width; ++pixel_x) {
        tile_canvas.at(pixel_x, pixel_y) = canvas_.at(x + pixel_x,
                                                      y + pixel_y);
      }
    }
    return Tile(tile_canvas);
  }
  Canvas canvas_;
  TilesheetLayout layout_;
};
/**
 *  Load a Tilesheet from an image file.
 */
Tilesheet LoadTilesheet(const std::string &filename);
} // namespace tcod
#endif // __cplusplus
#endif /* LIBTCOD_TILESET_TILESHEET_H_ */
