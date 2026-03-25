/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_floor_ceiling.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 01:16:17 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/24 17:31:46 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Draws the floor and ceiling for the current frame.
Called before raycasting so the walls are drawn on top. */
static void	draw_ceiling(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT / 2)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, game->ceiling_color);
			x++;
		}
		y++;
	}
}

/* Fills the bottom half of the screen with the floor color.
game->floor_color is set by the parser from line F in the .cub. */
static void	draw_floor(t_game *game)
{
	int	x;
	int	y;

	y = SCREEN_HEIGHT / 2;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			my_mlx_pixel_put(&game->img, x, y, game->floor_color);
			x++;
		}
		y++;
	}
}

/* Draws the floor and ceiling for the current frame.
Called before raycasting so the walls are drawn on top. */
void	draw_floor_ceiling(t_game *game)
{
	draw_ceiling(game);
	draw_floor(game);
}
