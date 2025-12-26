#include "cub3d.h"

/**
 * @brief Converts an RGB color array to a 32-bit integer color value
 *
 * Combines three 8-bit color components (R, G, B) into a single
 * 32-bit integer using bitwise operations. The format is 0x00RRGGBB.
 *
 * Formula: (R << 16) | (G << 8) | B
 *
 * @param rgb Array of 3 integers containing RGB values (0-255 each)
 *            rgb[0] = Red, rgb[1] = Green, rgb[2] = Blue
 * @return 32-bit integer representation of the color
 *
 * @note This format is compatible with MLX pixel manipulation functions
 * @note Alpha channel is always 0 (fully opaque)
 */
int	rgb_tab_to_int(int rgb[RGB_SIZE])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
