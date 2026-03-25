/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:51:13 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/24 17:21:55 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Checks whether a map cell is passable (not a wall).
Returns 1 if passable, 0 if wall or out of bounds. */
int	is_walkable(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_x >= game->map.width || map_y < 0
		|| map_y >= game->map.height)
		return (0);
	if (game->map.grid[map_y][map_x] == '1'
		|| game->map.grid[map_y][map_x] == '2')
		return (0);
	return (1);
}

/* Rotates the player by applying the 2D rotation matrix to the
direction vector and the camera plane. rot_speed negative = left. */
void	rotate_player(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	old_plane_x = game->player.room_plane_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed)
		+ game->player.dir_y * cos(rot_speed);
	game->player.room_plane_x = game->player.room_plane_x * cos(rot_speed)
		- game->player.room_plane_y * sin(rot_speed);
	game->player.room_plane_y = old_plane_x * sin(rot_speed)
		+ game->player.room_plane_y * cos(rot_speed);
}

/* Moves forward (direction=1) or backward (direction=-1).
Calculates the new position and applies it axis by axis
only if it is passable (collision sliding). */
void	move_forward_back(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_x * MOVE_SPEED * direction;
	new_y = game->player.pos_y + game->player.dir_y * MOVE_SPEED * direction;
	if (is_walkable(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_walkable(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/* Lateral displacement (strafe). direction=-1 = left, 1 = right.
Perpendicular vector: (dir_y, -dir_x). */
void	move_strafe(t_game *game, int direction)
{
	double	new_x;
	double	new_y;

	new_x = game->player.pos_x + game->player.dir_y * MOVE_SPEED * direction;
	new_y = game->player.pos_y - game->player.dir_x * MOVE_SPEED * direction;
	if (is_walkable(game, new_x, game->player.pos_y))
		game->player.pos_x = new_x;
	if (is_walkable(game, game->player.pos_x, new_y))
		game->player.pos_y = new_y;
}

/* Applies movement every frame based on the key flags.
W/S = forward/backward, A/D = straight, arrows = rotation. */
void	move_player(t_game *game)
{
	if (game->keys.w)
		move_forward_back(game, 1);
	if (game->keys.s)
		move_forward_back(game, -1);
	if (game->keys.a)
		move_strafe(game, -1);
	if (game->keys.d)
		move_strafe(game, 1);
	if (game->keys.left)
		rotate_player(game, -ROT_SPEED);
	if (game->keys.right)
		rotate_player(game, ROT_SPEED);
}
