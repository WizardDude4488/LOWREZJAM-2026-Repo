#include "Game.hpp"
#include "Animation.hpp"

int Animation::get_frame() {
	return current_frame;
}

void Animation::set_frame(int curr_frame) {
	current_frame = curr_frame;
}

void Animation::draw_frame(Vector2 position) {
	DrawTextureRec(current_game->get_texture(texture), frames[current_frame], position, WHITE);
}