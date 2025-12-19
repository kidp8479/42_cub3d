#include "cub3d.h"

/**
 * @brief Returns wall color based on direction
 *
 * @param wall_dir Wall direction (NORTH/SOUTH/EAST/WEST)
 * @return Color in 0xRRGGBB format
 */
int	get_wall_color(int wall_dir)
{
	if (wall_dir == NORTH)
		return (0xFF0000);
	else if (wall_dir == SOUTH)
		return (0x00FF00);
	else if (wall_dir == EAST)
		return (0x0000FF);
	else
		return (0xFFFF00);
}

int	get_texture_pixel(t_texture *texture, int tex_x, int tex_y)
{
	
}
