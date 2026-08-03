#include <cmath>

#include "Helper.hpp"

std::vector<Rectangle> Helper::create_spritesheet_frames(int frame_width, int frame_height, int image_width, int image_height) {
	std::vector<Rectangle> rectangles;
	
	// Exclude border space that doesn't take up a full frame
	int max_width = std::floor(static_cast<double>(image_width) / static_cast<double>(frame_width));
	int max_height = std::floor(static_cast<double> (image_height) / static_cast<double>(frame_height));
							// Adjust top-left
	for (int y = 0; y < max_height - frame_height; y += frame_height) {
		for (int x = 0; x < max_width - frame_width; x += frame_width) {
			rectangles.push_back(Rectangle{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(frame_width), static_cast<float>(frame_height)});
		}
	}

	return rectangles;
}

std::vector<Rectangle> Helper::create_spritesheet_frames(int frame_width, int frame_height, int image_width, int image_height, int num_of_frames) {
	std::vector<Rectangle> rectangles;
	
	// Exclude border space that doesn't take up a full frame
	int max_width = std::floor(static_cast<double>(image_width) / static_cast<double>(frame_width));
	int max_height = std::floor(static_cast<double> (image_height) / static_cast<double>(frame_height));
							// Adjust top-left
	int f = 0;
	while (f < num_of_frames) {
		for (int y = 0; y < image_height - frame_height; y += frame_height) {
			for (int x = 0; x < image_width - frame_width; x += frame_width) {
				if (f <= num_of_frames - 1) {
					rectangles.push_back(Rectangle{ static_cast<float>(x), static_cast<float>(y), static_cast<float>(frame_width), static_cast<float>(frame_height)});
					f++;
				} else {
					return rectangles;
				}
				
			}
		}
	}
}