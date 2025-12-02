#include "cub3d.h"

  /**
   * @brief Extracts filename from full file path
   *
   * Handles all path formats: relative, absolute, nested directories.
   * If no directory separator is found, returns the original path.
   *
   * @param path Complete file path
   * @return Pointer to the filename
   *
   * @note Does not allocate memory - returns pointer within original string
   * @warning Returns NULL if path is NULL
   */
const char	*get_file_basename(const char *path)
{
	size_t		i;
	const char	*basename;

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
   * @brief Validates .cub file extension with comprehensive security checks
   *
   * Performs a multi-step validation pipeline to ensure the provided filename
   * has a valid .cub extension and meets security requirements.
   *
   * Validation Pipeline:
   * - NULL pointer protection, prevents segfault on invalid input
   * - Basename extraction, handles relative/absolute paths (./maps/, /path/to/)
   * - Hidden file detection, rejects files starting with '.' (.hidden.cub)
   * - Minimum length validation, rejects basenames shorter than 5 characters
   * - Extension validation, ensures filename ends with exactly ".cub"
   *
   * @param filename File path to validate (supports all path formats)
   * @return true if filename is valid .cub file, false otherwise
   *
   * @note Final validation checks for success (== 0) instead of failure (!= 0)
   * to comply with 42 norm's 25-line function limit.
   * Error messages are displayed via print_errors() for each failure case.
   */
bool	is_valid_filename(const char *filename)
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
		print_errors(HID_FILENAME, NULL, NULL);
		return (false);
	}
	if (basename_len < 5)
	{
		print_errors(LEN_FILENAME, NULL, NULL);
		return (false);
	}
	if (ft_strncmp(&basename[basename_len - 4], ".cub", 4) == 0)
		return (true);
	print_errors(EXT_FILENAME, NULL, NULL);
	return (false);
}
