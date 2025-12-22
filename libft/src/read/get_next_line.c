/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 13:56:26 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/18 17:54:47 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"

/**
 * @brief Appends read_buffer to buffer and frees buffer.
 *
 * Joins the two strings into a newly allocated string, then frees
 * the original buffer to avoid memory leaks.
 *
 * @param buffer        Existing buffer to be extended.
 * @param read_buffer   Newly read data to append.
 *
 * @return Newly allocated joined string, or NULL on failure.
 */
static char	*strjoin_and_free(char *buffer, char *read_buffer)
{
	char	*joined_str;

	joined_str = ft_strjoin(buffer, read_buffer);
	free(buffer);
	buffer = NULL;
	return (joined_str);
}

/**
 * @brief Extracts a single line from the buffer.
 *
 * Allocates and returns a string containing the first line in the
 * buffer, including the trailing newline if present.
 *
 * @param buffer Source buffer containing file data.
 *
 * @return Newly allocated line, or NULL if buffer is empty or on
 *         allocation failure.
 */
static char	*extract_line(char *buffer)
{
	char	*line;
	int		i;

	i = 0;
	if (buffer[0] == '\0')
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = ft_calloc(i + 1, sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

/**
 * @brief Extracts remaining data after the first line from buffer.
 *
 * Removes the consumed line (up to and including the first newline)
 * and returns a newly allocated string containing any leftover data.
 *
 * @param buffer Buffer containing the extracted line and remaining data.
 *
 * @return Newly allocated string with leftover content, or NULL if
 *         no data remains or on allocation failure.
 */
static char	*leftover(char *buffer)
{
	char	*leftover;
	int		i;
	int		j;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	if (buffer[i] == '\0')
		return (free(buffer), buffer = NULL, NULL);
	j = 0;
	while (buffer[i + j] != '\0')
		j++;
	leftover = ft_calloc((j + 1), sizeof (char));
	if (!leftover)
		return (NULL);
	while (j--)
		leftover[j] = buffer[i + j];
	return (free(buffer), buffer = NULL, leftover);
}

/**
 * @brief Reads from fd and appends data to the buffer until a newline
 *        is found or EOF is reached.
 *
 * Continues reading in chunks of BUFFER_SIZE while no newline is
 * present in the existing buffer. The buffer is dynamically grown
 * and replaced as needed.
 *
 * @param fd     File descriptor to read from.
 * @param buffer Existing buffer containing unread data.
 *
 * @return Updated buffer containing at least one full line or NULL
 *         on read or allocation error.
 */
static char	*read_from_file(int fd, char *buffer)
{
	char	*read_buffer;
	ssize_t	bytes_read;

	read_buffer = ft_calloc(BUFFER_SIZE + 1, sizeof (char));
	if (!read_buffer)
		return (free(buffer), buffer = NULL, NULL);
	bytes_read = 1;
	while (bytes_read > 0 && ft_strchr(buffer, '\n') == NULL)
	{
		bytes_read = read(fd, read_buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (free(read_buffer), free(buffer),
				read_buffer = NULL, buffer = NULL, NULL);
		read_buffer[bytes_read] = '\0';
		buffer = strjoin_and_free(buffer, read_buffer);
		if (!buffer)
			return (free(read_buffer), read_buffer = NULL, NULL);
	}
	return (free(read_buffer), read_buffer = NULL, buffer);
}

/**
 * @brief Reads and returns the next line from a file descriptor.
 *
 * Maintains a static buffer per file descriptor to allow successive
 * calls to return one line at a time. The returned line includes the
 * trailing newline if present.
 *
 * @param fd File descriptor to read from.
 *
 * @return Pointer to the next line, or NULL on EOF or error.
 */
char	*get_next_line(int fd)
{
	static char	*buffer[OPEN_MAX];
	char		*line;

	if (handle_cleanup_mode(fd, buffer))
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= OPEN_MAX)
		return (NULL);
	if (!buffer[fd])
		buffer[fd] = ft_calloc(1, sizeof(char));
	if (!buffer[fd])
		return (NULL);
	buffer[fd] = read_from_file(fd, buffer[fd]);
	if (!buffer[fd])
		return (NULL);
	line = extract_line(buffer[fd]);
	buffer[fd] = leftover(buffer[fd]);
	if (!buffer[fd])
		free(buffer[fd]);
	return (line);
}
