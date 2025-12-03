#include "cub3d.h"

void	my_mlx_pixel_put(t_game *data, int x, int y, int color)
{
	char	*dst;

	dst = data->img_addr + (y * data->img_line_len + x * (data->img_bpp / 8));
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx;
	void	*mlx_win;
	t_game	test;
	int		i;

	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 400, 600, "Hello !");
	test.img = mlx_new_image(mlx, 400, 600);
	test.img_addr = mlx_get_data_addr(test.img, &test.img_bpp, &test.img_line_len, &test.img_endian);

	i = 0;
	while (i < 20)
	{
		my_mlx_pixel_put(&test, 5 + i, 5 + i, 0x00FF0000);
		i++;
	}

	mlx_put_image_to_window(mlx, mlx_win, test.img, 0, 0);
	mlx_loop(mlx);
	return (0);
}
