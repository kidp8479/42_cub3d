/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:07:18 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 14:07:20 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Parses and validates a single RGB component
 *
 * Converts a string to an integer and verifies it's in valid range [0-255].
 * Uses ft_safe_atoi to ensure the string represents a valid integer.
 *
 * @param str String representation of the RGB value
 * @param value Pointer to store the parsed integer value
 * @return EXIT_SUCCESS if valid, EXIT_FAILURE otherwise
 */
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

/**
 * @brief Parses an RGB color string in format "R,G,B"
 *
 * Splits the input string by commas and validates each component:
 *   - Must have exactly 3 components
 *   - Each component must be an integer in range [0-255]
 *
 * Example valid input: "220,100,0"
 *
 * @param value Input string containing comma-separated RGB values
 * @param rgb_values Output array to store the 3 parsed integers
 * @return EXIT_SUCCESS if parsing succeeds, EXIT_FAILURE on error
 */
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
