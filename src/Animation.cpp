#include "Game.hpp"
#include "Animation.hpp"

int Animation::get_frame() const {
	return current_frame;
}

void Animation::set_frame(int curr_frame) {
	current_frame = curr_frame;
}

void Animation::draw_frame(Vector2 position, Color tint) {
	DrawTextureRec(current_game->get_texture(texture), frames[current_frame], position, tint);
}

const Rectangle& Animation::get_frame_rect(int frame) const {
	return frames.at(frame);
}