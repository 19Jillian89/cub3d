/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 01:06:46 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/24 17:20:42 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3d.h"

/* Calculate delta_dist_x and delta_dist_y: the distance the ray
travels between two consecutive cell edges on the same axis.
Formula: |1 / rayDir|. If rayDir is 0, the ray is parallel
to that axis and will never intersect it, so INF is used. */
static void	init_delta(t_game *game, t_dda *d)
{
	if (game->player.ray_dir_x == 0)
		d->delta_dist_x = INF;
	else
		d->delta_dist_x = fabs(1.0 / game->player.ray_dir_x);
	if (game->player.ray_dir_y == 0)
		d->delta_dist_y = INF;
	else
		d->delta_dist_y = fabs(1.0 / game->player.ray_dir_y);
}

/* Calculate step and side_dist for both axes.
step is the direction of advancement through the map (+1 or -1).
side_dist is the distance from the player to the first cell edge
on the corresponding axis (the first intersection with the grid).*/
static void	init_steps(t_game *game, t_dda *d)
{
	if (game->player.ray_dir_x < 0)
	{
		d->step_x = -1;
		d->side_dist_x = (game->player.pos_x - d->map_x) * d->delta_dist_x;
	}
	else
	{
		d->step_x = 1;
		d->side_dist_x = (d->map_x + 1.0 - game->player.pos_x)
			* d->delta_dist_x;
	}
	if (game->player.ray_dir_y < 0)
	{
		d->step_y = -1;
		d->side_dist_y = (game->player.pos_y - d->map_y) * d->delta_dist_y;
	}
	else
	{
		d->step_y = 1;
		d->side_dist_y = (d->map_y + 1.0 - game->player.pos_y)
			* d->delta_dist_y;
	}
}

/* Initializes the struct t_dda with the player's starting cell,
then delegates the delta and step calculations to the dedicated functions. */
static void	init_dda(t_game *game, t_dda *d)
{
	d->map_x = (int)game->player.pos_x;
	d->map_y = (int)game->player.pos_y;
	init_delta(game, d);
	init_steps(game, d);
}

/* Advances cell by cell along the ray until it hits a wall.
At each step, it chooses the axis with the smallest side_dist (the one that
reaches the cell edge first), advances one cell on that axis,
and updates side_dist by adding delta_dist.
Saves hit_side: 0 = hit E/W side, 1 = hit N/S side. */
static void	dda_loop(t_game *game, t_dda *d)
{
	int	hit;

	hit = 0;
	while (!hit)
	{
		if (d->side_dist_x < d->side_dist_y)
		{
			d->side_dist_x += d->delta_dist_x;
			d->map_x += d->step_x;
			game->player.hit_side = 0;
		}
		else
		{
			d->side_dist_y += d->delta_dist_y;
			d->map_y += d->step_y;
			game->player.hit_side = 1;
		}
		if (game->map.grid[d->map_y][d->map_x] == '1'
			|| game->map.grid[d->map_y][d->map_x] == '2')
			hit = 1;
	}
}

/* Main DDA function. Initializes, loops,
saves the coordinates of the affected wall for texture mapping,
and returns the perpendicular distance to the wall.
The perpendicular distance (non-Euclidean) avoids the fish-eye effect:
side 0 -> side_dist_x - delta_dist_x
side 1 -> side_dist_y - delta_dist_y */
double	perform_dda(t_game *game, int x)
{
	t_dda	d;

	(void)x;
	init_dda(game, &d);
	dda_loop(game, &d);
	game->player.wall_map_x = d.map_x;
	game->player.wall_map_y = d.map_y;
	if (game->player.hit_side == 0)
		return (d.side_dist_x - d.delta_dist_x);
	return (d.side_dist_y - d.delta_dist_y);
}
