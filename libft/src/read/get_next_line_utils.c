/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/18 15:48:46 by diade-so          #+#    #+#             */
/*   Updated: 2025/12/18 17:55:15 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	gnl_clear_fd(int fd)
{
	if (fd < 0 || fd >= OPEN_MAX)
		return ;
	get_next_line(-(fd + 2));
}

int	handle_cleanup_mode(int fd, char **buffer)
{
	int	clear_fd;

	if (fd >= -1)
		return (0);
	clear_fd = -(fd + 2);
	if (clear_fd >= 0 && clear_fd < OPEN_MAX && buffer[clear_fd])
	{
		free(buffer[clear_fd]);
		buffer[clear_fd] = NULL;
	}
	return (1);
}
