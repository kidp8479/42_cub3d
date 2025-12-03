#include "cub3d.h"

int	open_cub_file(const char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		perror("cub3d");
	return (fd);
}
