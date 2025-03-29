// #pragma once
//
// #include <FastLED.h>
// #include "../Globals.h"
//
// void DrawColumnOrRow(CRGB *leds, const index_vector_matrix_y &vec, const CRGB &color)
// {
//     for (const auto &idx : vec) {
//         leds[idx] = color;
//     }
// }
//
// index_vector_matrix_y GetIndicesForColumn(int column)
// {
//     index_vector_matrix_y indices;
//     for (int y = 0; y < LEDS_MATRIX_Y; ++y) {
//         indices.push_back(CoordsToIndex(column, y));
//     }
//     return indices;
// }
//
// index_vector_matrix_x GetIndicesForRow(int row)
// {
//     index_vector_matrix_x indices;
//     for (int x = 0; x < LEDS_MATRIX_X; ++x)
//     {
//         indices.push_back(CoordsToIndex(x, row));
//     }
//     return indices;
// }
