#include "Rendering.h"

namespace Rendering {

    sf::Sprite tile_sprite;
    sf::Texture tile_mask_txt;
    sf::Sprite tile_mask;

    sf::RenderTexture tileMapChunk;
    sf::RenderTexture tileMap;
    std::vector<sf::RenderTexture*> chunk_textures;
    std::vector<gameSprite> sprites;
    const int tile_size = 64;
    const int width = 1920;
    const int height = 1080;

    sf::Sprite tileMapChunkSprite;
    sf::Texture textureAtlas;

    void init(int chunk_count) {
        tileMap.create(width, height);
        tileMapChunk.create(width, height);
        tile_mask_txt.loadFromFile("../assets/sprites/tile_mask.png");
        tile_mask.setTexture(tile_mask_txt);
        textureAtlas.loadFromFile("../assets/sprites/texture_atlas.png");
    }

    int loadSprite(const std::string& file_path, const std::string& name) {
        gameSprite newSprite;
        newSprite.path = file_path;
        newSprite.name = name;
        newSprite.sprite.loadFromFile(file_path);
        sprites.push_back(newSprite);
        return sprites.size() -1;
    }

    void rotateMatrix(int x, int y, int rotate_count, int& new_x, int& new_y, int matrix_size) {
        int tmp_x = x;
        int tmp_y = y;

        for (int i = 0; i < rotate_count; i++) {
            int old_x = tmp_x;
            tmp_x = matrix_size - 1 - tmp_y;
            tmp_y = old_x;
        }

        new_x = tmp_x;
        new_y = tmp_y;
    }


    void renderVertexChunks(sf::RenderWindow& window, const std::vector<WorldChunk>& chunks, sf::View& camera, int side, int chunk_width) {
        tileMap.clear();
        tileMapChunk.clear();

        for (int x = 0; x < chunk_width; x++) {
            for (int z = 0; z < chunk_width; z++) {
                int offset_x = (x - z) * 16 * tile_size / 2.0f;
                int offset_y = (x + z) * 16 * tile_size / 4.0f;

                sf::Transform offset;
                offset.translate(offset_x, offset_y);
                sf::RenderStates states;
                states.transform = offset;
                states.texture = &textureAtlas;

                int rotated_x = 0;
                int rotated_z = 0;

                rotateMatrix(x, z, side, rotated_x, rotated_z, chunk_width);

                const WorldChunk& chunk = chunks[rotated_x + rotated_z*chunk_width];
                window.draw(chunk.vertices[side][0].data(), chunk.vertices[side][0].size(), sf::Quads, states);
                tileMap.setView(camera);
                tileMap.draw(chunk.vertices[side][1].data(), chunk.vertices[side][1].size(), sf::Quads, states);
                tileMapChunk.setView(camera);
                tileMapChunk.draw(chunk.vertices[side][2].data(), chunk.vertices[side][2].size(), sf::Quads, states);
            }
        }

        tileMap.display();
        tileMapChunk.display();
    }

    void getClickedTile(const int mouse_x, const int mouse_y, int& chunk_index_x, int& chunk_index_z, int& tile_index_x, int& tile_index_y, int& tile_index_z, int& tile_side) {
        auto tileMapImage = tileMap.getTexture().copyToImage();
        auto tileMapImageChunk = tileMapChunk.getTexture().copyToImage();

        auto tile = tileMapImage.getPixel(mouse_x, mouse_y);
        auto chunk = tileMapImageChunk.getPixel(mouse_x, mouse_y);

        chunk_index_x = chunk.r;
        chunk_index_z = chunk.g;
        tile_side = chunk.b;

        tile_index_x = tile.r;
        tile_index_y = tile.g;
        tile_index_z = tile.b;
    }

    void debugRender(sf::RenderWindow& window) {
        tileMapChunkSprite.setTexture(tileMap.getTexture());
        window.draw(tileMapChunkSprite);
    }

    void deinit() {
        for (int i = 0; i < chunk_textures.size(); i++) {
            delete chunk_textures[i];
        }
    }
}