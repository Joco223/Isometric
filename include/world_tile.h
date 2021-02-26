#ifndef ISOMETRIC_WORLD_TILE_H
#define ISOMETRIC_WORLD_TILE_H

class WorldTile {
public:
    int pos_x, pos_y, pos_z;
    int sprite_index;
    bool visible, selected, top, transparent;
    int type = -1;

    WorldTile() {
      type = -1;
    };

    WorldTile(int x, int y, int z, int s_index, bool v, bool s, bool t, bool tr, int ty) {
        pos_x = x;
        pos_y = y;
        pos_z = z;
        sprite_index = s_index;
        visible = v;
        selected = s;
        top = t;
        type = ty;
        transparent = tr;
    }
};

#endif
