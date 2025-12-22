#include "cub3d.h"

static int	parse_rgb_component(const char *str, int *value)
{
	int	rgb_value;

	if (!ft_safe_atoi(str, &rgb_value))
		return (EXIT_FAILURE);
	if (rgb_value < 0 || rgb_value > 255)
		return (EXIT_FAILURE);
	*value = rgb_value;
	return (EXIT_SUCCESS);
}

int	parse_rgb(const char *value, int rgb_values[RGB_SIZE])
{
	char	**rgb_strs;
	int		i;

	rgb_strs = ft_split(value, ',');
	if (!rgb_strs)
		return (print_errors(RGB_SPLIT_FAIL, NULL, NULL), EXIT_FAILURE);
	i = 0;
	while (i < RGB_SIZE)
	{
		if (!rgb_strs[i] || parse_rgb_component(rgb_strs[i], &rgb_values[i]))
		{
			print_errors(RGB_INVALID_FORMAT, NULL, NULL);
			return (free_strings_array(rgb_strs), EXIT_FAILURE);
		}
		i++;
	}
	if (rgb_strs[RGB_SIZE] != NULL)
	{
		print_errors(RGB_TOO_MANY, NULL, NULL);
		free_strings_array(rgb_strs);
		return (EXIT_FAILURE);
	}
	free_strings_array(rgb_strs);
	return (EXIT_SUCCESS);
}
