#include "cub3d.h"

/**
 * @brief Returns a static lookup table of all valid header identifiers
 *
 * The table maps header keys (NO, SO, WE, EA, F, C) to their
 * corresponding t_header_type enum values and key lengths.
 *
 * @return Pointer to static array of t_header_entry structures
 */
static const t_header_entry	*get_header_table(void)
{
	static const t_header_entry	header[] = {
	{"NO", ID_NO, 2},
	{"SO", ID_SO, 2},
	{"WE", ID_WE, 2},
	{"EA", ID_EA, 2},
	{"F", ID_FLOOR, 1},
	{"C", ID_CEILING, 1},
	};

	return (header);
}

/**
 * @brief Matches a line against known header identifiers
 *
 * Searches the header lookup table to find a matching entry for
 * the given line. A match occurs when:
 *   - The line starts with a known header key (NO, SO, WE, EA, F, C)
 *   - The character immediately after the key is whitespace
 *
 * @param line Input line to match against header table
 * @return Pointer to matching t_header_entry, or NULL if no match found
 */
const t_header_entry	*get_header_entry(const char *line)
{
	size_t					i;
	const t_header_entry	*entries;

	entries = get_header_table();
	i = 0;
	while (i < HEADER_SIZE)
	{
		if (!ft_strncmp(line, entries[i].key, entries[i].len)
			&& ft_isspace(line[entries[i].len]))
			return (&entries[i]);
		i++;
	}
	return (NULL);
}
