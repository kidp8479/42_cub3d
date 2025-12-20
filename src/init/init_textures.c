#include "cub3d.h"

/**
  * @brief Loads a single texture from an .xpm file
  *
  * Uses MLX to load the texture image and retrieve pixel data address.
  * Validates texture dimensions (must be TEXTURE_WIDTH x TEXTURE_HEIGHT).
  * Fills the provided t_texture structure with all necessary data.
  *
  * @param game Pointer to game structure (contains MLX connection)
  * @param texture Pointer to texture structure to fill
  * @param path Path to .xpm file
  * @return EXIT_SUCCESS on success, EXIT_FAILURE on error
*/
static int	load_texture(t_game *game, t_texture *texture, char *path)
{
	texture->img = mlx_xpm_file_to_image(game->mlx, path, &texture->width,
			&texture->height);
	if (!texture->img)
	{
		print_errors(TEXTURE_LOAD, NULL, NULL);
		return (EXIT_FAILURE);
	}
	if (texture->width != TEXTURE_WIDTH || texture->height != TEXTURE_HEIGHT)
	{
		print_errors(TEXTURE_DIMENSION, NULL, NULL);
		return (EXIT_FAILURE);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bpp,
			&texture->line_len, &texture->endian);
	if (!texture->addr)
	{
		print_errors(TEXTURE_DATA, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
  * @brief Loads all 4 wall textures (NO, SO, WE, EA)
  *
  * Iterates through tex_paths array and loads each texture using load_texture().
  * Uses t_header_type enum values for array indexing.
  *
  * @param game Pointer to game structure
  * @return EXIT_SUCCESS if all textures loaded, EXIT_FAILURE on any error
*/
int	init_textures(t_game *game)
{
	int	i;

	i = 0;
	while (i < TEX_SIZE)
	{
		if (load_texture(game, &game->textures[i], game->map.tex_paths[i])
			!= EXIT_SUCCESS)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}
