#include "cub3d.h"

/**
   * @brief Extracts filename from full file path
   *
   * Handles all path formats: relative, absolute, nested directories.
   * If no directory separator '/' is found, returns the original path.
   *
   * @param path Complete file path
   * @return Pointer to the filename
   *
   * @note Does not allocate memory - returns pointer within original string or
   * the original string directly if there is no '/'
   * @warning Returns NULL if path is NULL
   */
static const char	*get_file_basename(const char *path)
{
	size_t		i;
	const char	*basename;

	if (!path)
		return (NULL);
	i = 0;
	basename = path;
	while (path[i])
	{
		if (path[i] == '/')
			basename = &path[i + 1];
		i++;
	}
	return (basename);
}

/**
   * @brief Validates .cub extension, rejects hidden files and short names
   *
   * Checks: NULL protection, basename extraction, no hidden files,
   * length >= 5, extension must be ".cub"
   *
   * @param filename File path to validate
   * @return true if valid, false otherwise
   * @note Final check uses (== 0) instead of (!= 0) for 42 Norm lines limit
   */
static bool	is_valid_filename(const char *filename)
{
	size_t		basename_len;
	const char	*basename;

	if (!filename)
	{
		print_errors(NULL_FILENAME, NULL, NULL);
		return (false);
	}
	basename = get_file_basename(filename);
	basename_len = ft_strlen(basename);
	if (basename[0] == '.')
	{
		print_errors(HIDDEN_FILENAME, NULL, NULL);
		return (false);
	}
	if (basename_len < 5)
	{
		print_errors(LENGTH_FILENAME, NULL, NULL);
		return (false);
	}
	if (ft_strncmp(&basename[basename_len - 4], ".cub", 4) == 0)
		return (true);
	print_errors(EXTENSION_FILENAME, NULL, NULL);
	return (false);
}

/**
   * @brief Checks if file exists, is readable, and is not a directory
   *
   * Opens the file and attempts to read 1 byte to verify it's a regular file.
   * Directories will fail the read test with errno EISDIR.
   *
   * @param filename Path to the file to check
   * @return true if file is accessible and readable, false otherwise
   * @note File descriptor is closed immediately after the check
   */
static bool	check_file_access(const char *filename)
{
	int		fd;
	ssize_t	bytes_read;
	char	buffer[1];

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		perror(RED "Error\nopen" RESET);
		return (false);
	}
	bytes_read = read(fd, buffer, 1);
	close(fd);
	if (bytes_read < 0)
	{
		perror(RED "Error\nread" RESET);
		return (false);
	}
	return (true);
}

int	validate_argument(char *filename)
{
	if (is_valid_filename(filename) == false)
		return (EXIT_FAILURE);
	if (check_file_access(filename) == false)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
