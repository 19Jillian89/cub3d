/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:13:12 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 20:10:06 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Loads the door XPM texture into the game struct.
** Calls error_exit if the texture file cannot be read. */
void	load_door_texture(t_game *game)
{
	if (load_texture(game, &game->door_texture, "textures/wall_floor/door.xpm"))
		error_exit(game, "Failed to load door texture");
}

/* Projects player position 1.5 units forward along the facing direction.
** Returns a pointer to that map cell, or NULL if out of bounds. */
static char	*get_front_cell(t_game *game)
{
	int	door_x;
	int	door_y;

	door_x = (int)(game->player.pos_x + game->player.dir_x * 1.5);
	door_y = (int)(game->player.pos_y + game->player.dir_y * 1.5);
	if (door_y < 0 || door_y >= game->map.height)
		return (NULL);
	if (door_x < 0 || door_x >= (int)ft_strlen(game->map.grid[door_y]))
		return (NULL);
	return (&game->map.grid[door_y][door_x]);
}

/* If the cell in front of the player is a closed door ('2'),
** replaces it with an open floor tile ('0'). */
void	handle_doors(t_game *game)
{
	char	*cell;

	cell = get_front_cell(game);
	if (!cell)
		return ;
	if (*cell == '2')
		*cell = '0';
}
