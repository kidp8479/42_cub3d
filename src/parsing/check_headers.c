/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_headers.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 13:58:06 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 13:58:09 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Check if a line matches a valid header identifier
 *
 * Skips leading whitespace and verifies the line starts with
 * a known header entry.
 */
static bool	is_header_line(const char *line)
{
	size_t	i;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	return (get_header_entry(line + i) != NULL);
}

/**
 * @brief Count consecutive header lines at the start of a file
 *
 * Stops counting on the first non-header, non-empty line.
 */
static int	count_header_lines(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		if (line_is_empty(line))
		{
			free(line);
			line = get_next_line(fd);
			continue ;
		}
		if (!is_header_line(line))
		{
			free(line);
			break ;
		}
		count++;
		free(line);
		line = get_next_line(fd);
	}
	return (count);
}

/**
 * @brief Validate the number of headers in a .cub file
 *
 * Ensures the file contains exactly HEADER_SIZE identifiers.
 */
int	check_header_count(const char *path)
{
	int		fd;
	int		count;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	count = count_header_lines(fd);
	gnl_clear_fd(fd);
	close(fd);
	if (count < HEADER_SIZE)
	{
		print_errors(HEADER_MISSING, NULL, NULL);
		return (EXIT_FAILURE);
	}
	else if (count > HEADER_SIZE)
	{
		print_errors(HEADER_TOO_MANY, NULL, NULL);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
