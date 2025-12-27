/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 14:07:06 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/27 18:30:39 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Skip consecutive empty lines in a file while reading.
 *
 * Frees each empty line and reads the next line from the file.
 * Updates the line counter. Returns false if EOF is reached.
 *
 * @param line Pointer to the current line buffer.
 * @param fd   File descriptor to read from.
 * @param i    Pointer to current line index (will be incremented).
 * @return true if a non-empty line is found, false if EOF reached.
 */
static bool	skip_empty_lines(char **line, int fd, int *i)
{
	while (*line && line_is_empty(*line))
	{
		free(*line);
		*line = get_next_line(fd);
		(*i)++;
	}
	if (*line == NULL)
		return (false);
	return (true);
}

/**
 * @brief Check if all required map headers have been set.
 *
 * Iterates over the header flags and returns true only if all headers
 * are marked as set in the map structure.
 *
 * @param map Pointer to the map structure.
 * @return true if all headers are set, false otherwise.
 */
static bool	all_headers_set(t_map *map)
{
	int	i;

	i = 0;
	while (i < HEADER_SIZE)
	{
		if (map->id_set[i] == false)
			return (false);
		i++;
	}
	return (true);
}

/**
 * @brief Set the starting line index of the map in the .cub file.
 *
 * This function is called during header parsing once all required
 * headers have been successfully parsed. It skips any empty lines
 * following the headers and records the current line index as the
 * first line of the map.
 *
 * @param map  Pointer to the map structure to update.
 * @param line Address of the current line buffer.
 * @param fd   File descriptor of the opened .cub file.
 * @param i    Pointer to the current line index in the file.
 *
 * @return true if the map start line was set successfully,
 *         false if headers are incomplete or an error occurs
 *         while skipping empty lines.
 */
static bool	set_map_start_line(t_map *map, char **line, int fd, int *i)
{
	if (!all_headers_set(map))
		return (false);
	if (!skip_empty_lines(line, fd, i))
		return (false);
	map->map_start_line = (*i);
	return (true);
}

/**
 * @brief Parses all header entries from a .cub file.
 *
 * Reads the file line by line and parses texture paths and RGB
 * color definitions until all required headers are set. Empty
 * lines are skipped as needed. Once headers are complete, the
 * start line of the map is detected and stored in map_start_line.
 *
 * The function stops parsing when the map section begins.
 *
 * @param path Path to the .cub file.
 * @param map Pointer to the map structure to populate.
 *
 * @return EXIT_SUCCESS on success, EXIT_FAILURE on error.
 */
int	parse_header(const char *path, t_map *map)
{
	int		i;
	int		fd;
	char	*line;

	fd = open_cub_file(path);
	if (fd < 0)
		return (EXIT_FAILURE);
	gnl_clear_fd(fd);
	line = get_next_line(fd);
	i = 0;
	while (line)
	{
		if (!skip_empty_lines(&line, fd, &i))
			return (gnl_clear_fd(fd), close(fd), EXIT_FAILURE);
		if (parse_header_line(map, line) == EXIT_FAILURE)
			return (gnl_clear_fd(fd), free(line), close(fd), EXIT_FAILURE);
		next_line(&line, fd, &i);
		if (set_map_start_line(map, &line, fd, &i))
		{
			free(line);
			break ;
		}
	}
	gnl_clear_fd(fd);
	return (close(fd), EXIT_SUCCESS);
}
