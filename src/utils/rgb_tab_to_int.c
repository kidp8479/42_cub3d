#include "cub3d.h"

int	rgb_tab_to_int(int rgb[RGB_SIZE])
{
	return ((rgb[0] << 16) | (rgb[1] << 8) | rgb[2]);
}
