/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:23:27 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:45:00 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Builds 2D grid as array of strdup lines (originals freed soon).
 * Tracks max width (rows may differ, right-trailing spaces stripped).
 * calloc sets grid[height]=NULL sentinel. Returns: 0 ok, 1 malloc fail. */
static int	build_grid(t_game *game, char **lines, int height)
{
	int	i;
	int	len;

	game->map.grid = calloc(height + 1, sizeof(char *));
	if (!game->map.grid)
		return (1);
	game->map.height = height;
	game->map.width = 0;
	i = 0;
	while (i < height)
	{
		trim_newline(lines[i]);
		game->map.grid[i] = ft_strdup(lines[i]);
		if (!game->map.grid[i])
			return (1);
		len = ft_strlen(game->map.grid[i]);
		if (len > game->map.width)
			game->map.width = len;
		i++;
	}
	game->map.grid[height] = NULL;
	return (0);
}

/* Finds player spawn (N/S/E/W) in grid, saves pos/dir in map.
 * Called AFTER build_grid (complete grid ready).
 * Keeps char in grid for validate_map. Returns: 0 found, 1 none. */
static int	find_player(t_game *game)
{
	int	i;
	int	j;

	i = 0;
	while (game->map.grid[i])
	{
		j = 0;
		while (game->map.grid[i][j])
		{
			if (ft_strchr("NSEW", game->map.grid[i][j]))
			{
				game->map.player_x = j;
				game->map.player_y = i;
				game->map.player_dir = game->map.grid[i][j];
				return (0);
			}
			j++;
		}
		i++;
	}
	return (1);
}

/* Parses map: count rows → build_grid → find_player.
 * Calls validate_map externally after success.
 * count_str_array skips NULLs. Returns: 0 ok, 1 error. */
int	parse_map(t_game *game, char **lines)
{
	int	height;

	height = count_str_array(lines);
	if (height == 0)
	{
		error_exit(game, "Empty map");
		return (1);
	}
	if (build_grid(game, lines, height))
	{
		error_exit(game, "Failed to build map grid");
		return (1);
	}
	if (find_player(game))
	{
		error_exit(game, "No player start position (N/S/E/W) in map");
		return (1);
	}
	return (0);
}
