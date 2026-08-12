#include "game.h"
#include "ui.h"

void UIRender(const Game *game) {

    const Rectangle score_rect = {
        .x = SCORE_POS_X,
        .y = SCORE_POS_Y,
        .width = SCORE_WIDTH,
        .height = SCORE_HEIGHT
    };

    const Rectangle next_piece_rect = {
        .x = NEXT_PIECE_X,
        .y = NEXT_PIECE_Y,
        .width = NEXT_PIECE_WIDTH,
        .height = NEXT_PIECE_HEIGHT
    };

    DrawRectangleRounded(score_rect, UI_RECT_ROUNDNESS, 1, CUSTOM_COLOR_GAME_PLAYFIELD);
    DrawRectangleRounded(next_piece_rect, UI_RECT_ROUNDNESS, 1, CUSTOM_COLOR_GAME_PLAYFIELD);

}
