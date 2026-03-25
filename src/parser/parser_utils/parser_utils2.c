/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:41:49 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Checks that the string represents a valid non‑negative unsigned integer.
 * Iterates character by character to avoid ft_atoi accepting
 * values with unusual hyphens, Unicode dashes, or hidden characters.
 * Returns 1 if valid (only digits, not empty), 0 otherwise. */
int	is_valid_uint_str(char *s)
{
	if (!s || !*s)
		return (0);
	while (*s)
	{
		if (*s < '0' || *s > '9')
			return (0);
		s++;
	}
	return (1);
}

/* Counts the elements in a NULL‑terminated string array.
 * Used to check that ft_split returns exactly 3 RGB components
 * and to determine the height of the map. */
int	count_str_array(char **arr)
{
	int	i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
