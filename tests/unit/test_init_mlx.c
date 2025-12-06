#include "cub3d.h"

// function that will write a pixel in buffer img
void	write_pxl_in_img_buffer(t_game *data, int x, int y, int color)
{
	char	*dst;

	// calculate pixel's adress
	// - y * line_len: skip previous lines (in BYTES)
	// - x * (bpp / 8): skip previous pixels on the line (bpp is in bits, converted in BYTES)
	dst = data->img_addr + (y * data->img_line_len + x * (data->img_bpp / 8));
	// cast to unsigned int* to write 4 bytes (32 bits) in one go
	// color format: 0x00RRGGBB (hexadecimal)
	*(unsigned int*)dst = color;
}

int	main(void)
{
	void	*mlx; // pointer to mlx connexion (handle to X11 graphical system)
	void	*mlx_win; // pointeur to the created windows
	t_game	test; // struct that will hold buffer image infos
	int		i; // loop iterator
	int		j; // inner loop iterator

	mlx = mlx_init(); // start connexion to X11 graphical systeme, returns a pointer that we will use in all MLX operation
	mlx_win = mlx_new_window(mlx, 400, 600, "Hello !"); // create a 400*600 windows, this windows is handled by X11 graphical system
	test.img = mlx_new_image(mlx, 400, 600); // create a 400*600 image in memory (nothing displayed yet), it's the canva were we will be drawing
	test.img_addr = mlx_get_data_addr(// gets image memory adress + technical infos
		test.img, // image we just created
		&test.img_bpp, // MLX will fill info about bit per pixels (usually 32 bits = 4 octets)
		&test.img_line_len, // MLX will fill info about BYTES per lines (can add padding)
		&test.img_endian // MLX will fill bytes order (we don't care)
	);

// will draw a horizontale line of 20 red pixels starting from (5, 5) position
	i = 0;
	while (i < 50)
	{
		j = 0;
		while (j < 50)
		{
			write_pxl_in_img_buffer(&test, j, i, 0x0000FF00);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(mlx, mlx_win, test.img, 0, 0); //copy buffered img to the windows in pos (0, 0), it's when the img becomes visible
	mlx_loop(mlx); // launch event loop (waits for keyboard/mouse/windows), never returns, infinit loop
	return (0);
}
