/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pafroidu <pafroidu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/27 18:13:12 by pafroidu          #+#    #+#             */
/*   Updated: 2025/12/27 18:13:13 by pafroidu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/**
 * @brief Print an error message with optional parts.
 *
 * This function prints "Error" followed by up to three optional
 * message strings.
 *
 * @param p1 First part of the error message (can be NULL).
 * @param p2 Second part of the error message (can be NULL).
 * @param p3 Third part of the error message (can be NULL).
 */
void	print_errors(char *p1, char *p2, char *p3)
{
	write(STDERR_FILENO, "Error\n", 7);
	if (p1)
		write(STDERR_FILENO, p1, ft_strlen(p1));
	if (p2)
		write(STDERR_FILENO, p2, ft_strlen(p2));
	if (p3)
		write(STDERR_FILENO, p3, ft_strlen(p3));
	write(STDERR_FILENO, "\n", 1);
}
