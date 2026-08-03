#pragma once

#include <vector>

#include "raylib.h"

namespace Helper {
	// Go left to right, top to bottom creating rects representing regions of the spritesheet
	std::vector<Rectangle> create_spritesheet_frames(int frame_width, int frame_height, int image_width, int image_height);

    std::vector<Rectangle> create_spritesheet_frames(int frame_width, int frame_height, int image_width, int image_height, int num_of_frames);

}