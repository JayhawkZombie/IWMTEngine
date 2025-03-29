#pragma once

#define LED_PIN     8
#define LEDS_MATRIX_X 8
#define LEDS_MATRIX_Y 8
#define NUM_LEDS    LEDS_MATRIX_X * LEDS_MATRIX_Y
#define BRIGHTNESS  55
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB

#include <stdint.h>
// #include <FastLED.h>
#include <vector>

using void_ftn_ptr = void(*)(void);

using index_vector8 = std::vector<int>;
using index_vector32 = std::vector<int>;

// fl::FixedVector<int, LEDS_MATRIX_Y>
using index_vector_matrix_y = std::vector<int>;
// fl::FixedVector<int, LEDS_MATRIX_X>
using index_vector_matrix_x = std::vector<int>;

static int CoordsToIndex(int x, int y)
{
    return y * LEDS_MATRIX_X + x;
}
