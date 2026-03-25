/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:26:12 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 19:32:19 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	get_cell(t_game *game, int x, int y)
{
	if (y < 0 || y >= game->map.height)
		return (' ');
	if (x < 0 || x >= (int)ft_strlen(game->map.grid[y]))
		return (' ');
	return (game->map.grid[y][x]);
}

static int	check_surroundings(t_game *game, int x, int y)
{
	if (get_cell(game, x, y - 1) == ' ')
		return (1);
	if (get_cell(game, x, y + 1) == ' ')
		return (1);
	if (get_cell(game, x - 1, y) == ' ')
		return (1);
	if (get_cell(game, x + 1, y) == ' ')
		return (1);
	return (0);
}

static int	is_valid_map_char(char c)
{
	return (ft_strchr("012 NSEW", c) != NULL);
}

int	validate_map(t_game *game)
{
	int		y;
	int		x;
	char	c;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			c = game->map.grid[y][x];
			if (!is_valid_map_char(c))
				error_exit(game, "Invalid character in map");
			if (ft_strchr("0NSEW2", c) && check_surroundings(game, x, y))
				error_exit(game, "Map not closed/surrounded by walls");
			x++;
		}
		y++;
	}
	return (0);
}
