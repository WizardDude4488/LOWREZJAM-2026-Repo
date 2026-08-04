#pragma once

#include <vector>
#include <string>

#include "raylib.h"

// NOTE: Each entity object should own their Animation object, instead of it being a part of the Game object
class Animation {
protected:

    std::string texture;
    std::vector<Rectangle> frames;
    int current_frame = 0;
public:
    // texture, frame
    Animation() = default;
    Animation(const std::string& t, const std::vector<Rectangle>& f) : texture(t), frames(f) {}

    // Creating a Texture2D is difficult because we have to load it to the cpu, get the sub-region, and load is back on the cpu
    //Texture2D get_frame(int index);
    //Rectangle get_frame_rect(int index);

    // Instead, we can set the frame and render it with a position
    int get_frame() const;
    const Rectangle& get_frame_rect(int frame) const;
    void set_frame(int curr_frame);
    void draw_frame(Vector2 position); // add rotation, scale later if we need it
};