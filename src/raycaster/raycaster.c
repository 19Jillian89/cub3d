/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/16 00:14:52 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/24 17:24:59 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Performs ray casting for a complete frame.
For each column x from 0 to SCREEN_WIDTH-1:
1. camera_x: position in the camera plane, from -1 (left) to +1 (right)
2. ray_dir: ray direction = dir + plane * camera_x
3. perform_dda: advances to the wall, returns perpendicular distance
4. draw_wall: draws the vertical column with proportional height
The center column (x = SCREEN_WIDTH/2) corresponds to the exact direction
of the player (camera_x = 0). */
void	raycast(t_game *game)
{
	int		x;
	double	camera_x;
	double	perp_wall_dist;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2.0 * x / (double)SCREEN_WIDTH - 1.0;
		game->player.ray_dir_x = game->player.dir_x
			+ game->player.room_plane_x * camera_x;
		game->player.ray_dir_y = game->player.dir_y
			+ game->player.room_plane_y * camera_x;
		perp_wall_dist = perform_dda(game, x);
		draw_wall(game, x, perp_wall_dist, game->player.hit_side);
		x++;
	}
}
