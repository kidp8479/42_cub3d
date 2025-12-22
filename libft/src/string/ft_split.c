/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: diade-so <diade-so@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 09:00:49 by diade-so          #+#    #+#             */
/*   Updated: 2025/04/26 23:12:24 by diade-so         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Counts the number of substrings in a string separated by a delimiter.
 *
 * @param s The input string.
 * @param c The delimiter character.
 * @return The number of substrings (tokens) found.
 */
static size_t	count_substr(const char *s, char c)
{
	size_t	count;
	int		in_substr;

	count = 0;
	in_substr = 0;
	if (!s || s[0] == '\0')
		return (0);
	while (*s)
	{
		if (*s != c && in_substr == 0)
		{
			count++;
			in_substr = 1;
		}
		else if (*s == c)
			in_substr = 0;
		s++;
	}
	return (count);
}

/**
 * @brief Allocates and copies a single substring from a string.
 *
 * Advances the input pointer to the character following the substring.
 *
 * @param s Pointer to the input string pointer (will be updated).
 * @param c The delimiter character.
 * @return A newly allocated substring, or NULL if allocation fails or
 * no substring found.
 */
static char	*allocate_copy_substr(const char **s, char c )
{
	const char	*start;
	char		*substr;
	size_t		i;
	size_t		len;

	while (**s == c)
		(*s)++;
	if (**s == '\0')
		return (NULL);
	start = *s;
	len = 0;
	while ((*s)[len] && (*s)[len] != c)
		len++;
	substr = malloc((len + 1) * sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len)
	{
		substr[i] = start[i];
		i++;
	}
	substr[i] = '\0';
	*s += len;
	return (substr);
}

/**
 * @brief Frees a NULL-terminated array of strings.
 *
 * @param array The array of strings to free.
 */
static void	free_split(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

/**
 * @brief Splits a string into an array of substrings using a delimiter.
 *
 * Allocates a new array of strings. Each substring is dynamically allocated
 * and the array is NULL-terminated.
 *
 * @param s The input string.
 * @param c The delimiter character.
 * @return A NULL-terminated array of substrings, or NULL on allocation
 * failure.
 *
 * @note The caller is responsible for freeing the returned array using
 * free_split(). The function does not trim any spaces.
 */
char	**ft_split(char const *s, char c)
{
	size_t	i;
	size_t	count;
	char	**array;

	if (!s)
		return (NULL);
	count = count_substr(s, c);
	array = malloc((count + 1) * sizeof(*array));
	if (!array)
		return (NULL);
	i = 0;
	while (i < count)
	{
		array[i] = allocate_copy_substr(&s, c);
		if (!array[i])
		{
			free_split(array);
			return (NULL);
		}
		i++;
	}
	array[i] = NULL;
	return (array);
}
