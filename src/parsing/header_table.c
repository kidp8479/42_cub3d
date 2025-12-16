#include "cub3d.h"

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
		{
			print_errors(HEADER_INVALID, NULL, NULL);
			return (&entries[i]);
		}
		i++;
	}
	return (NULL);
}
