/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 13:41:00 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 19:35:42 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Clears the 2D grid and resets all t_map fields. */
void	free_map(t_map *map)
{
	if (!map)
		return ;
	free_str_array(map->grid);
	map->grid = NULL;
	map->width = 0;
	map->height = 0;
	map->player_x = 0;
	map->player_y = 0;
	map->player_dir = 0;
}

/* Destroys the MLX images and frees the paths of the 4 textures.
We clear img.img after mlx_destroy_image to avoid double-free
if free_textures is called twice. */
void	free_textures(t_game *game)
{
	int	i;

	if (!game)
		return ;
	i = 0;
	while (i < 4)
	{
		if (game->textures[i].img.img)
		{
			mlx_destroy_image(game->mlx, game->textures[i].img.img);
			game->textures[i].img.img = NULL;
		}
		safe_free((void **)&game->textures[i].path);
		game->textures[i].width = 0;
		game->textures[i].height = 0;
		i++;
	}
	if (game->door_texture.img.img)
	{
		mlx_destroy_image(game->mlx, game->door_texture.img.img);
		game->door_texture.img.img = NULL;
	}
}

/* Destroys the main rendering buffer. */
void	free_main_image(t_game *game)
{
	if (!game || !game->mlx || !game->img.img)
		return ;
	mlx_destroy_image(game->mlx, game->img.img);
	game->img.img = NULL;
}

/* Frees the entire game in the correct order:
MLX objects before MLX context, context before free(game).
get_next_line(-1) flushes the remaining static GNL buffer,
necessary when error_exit returns before the file
has been completely read.
Any subsequent calls to free_game with the same pointer
are neutralized by the initial !game check. */
void	free_game(t_game *game)
{
	if (!game)
		return ;
	get_next_line(-1);
	free_str_array(game->raw_lines);
	game->raw_lines = NULL;
	free_map(&game->map);
	free_textures(game);
	free_main_image(game);
	free_weapon(game);
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	free(game);
}

/* Frees a NULL-terminated array of strings. */
void	free_str_array(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		arr[i] = NULL;
		i++;
	}
	free(arr);
}
