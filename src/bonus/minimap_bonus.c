/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 00:00:00 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:38:02 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** WHY: Bonus — display a 2D map overlay on top of the 3D scene.
**      The minimap is drawn onto the image buffer before it is sent
**      to the window, so it appears on top of the 3D rendering.
**      Each cell is a square of MINIMAP_SCALE x MINIMAP_SCALE pixels.
**      The player is shown as a red point with a yellow direction arrow.
** CALLED FROM: render() in src/bonus/render_bonus.c, every frame.
*/

#include "cub3d.h"

/* Draws a cell as a square of MINIMAP_SCALE x MINIMAP_SCALE pixels.
 * px/py = top‑left corner of the cell on the screen buffer. */
static void	draw_mm_cell(t_game *g, int mx, int my, int color)
{
	int	px;
	int	py;
	int	x;
	int	y;

	px = MINIMAP_MARGIN + mx * MINIMAP_SCALE;
	py = MINIMAP_MARGIN + my * MINIMAP_SCALE;
	y = py;
	while (y < py + MINIMAP_SCALE)
	{
		x = px;
		while (x < px + MINIMAP_SCALE)
		{
			my_mlx_pixel_put(&g->img, x, y, color);
			x++;
		}
		y++;
	}
}

/* Returns the minimap color for a grid character.
 * '1' = wall (white), '2' = closed door (orange), anything else = floor. */
static int	get_mm_color(char c)
{
	if (c == '1')
		return (MINIMAP_WALL_COLOR);
	if (c == '2')
		return (MINIMAP_DOOR_COLOR);
	return (MINIMAP_FLOOR_COLOR);
}

/* Draws all cells of the map onto the minimap.
 * Loops over the grid row by row; stops at the '\0' of each row
 * because rows can have different lengths. */
static void	draw_mm_grid(t_game *game)
{
	int	x;
	int	y;

	y = 0;
	while (y < game->map.height)
	{
		x = 0;
		while (game->map.grid[y][x])
		{
			draw_mm_cell(game, x, y, get_mm_color(game->map.grid[y][x]));
			x++;
		}
		y++;
	}
}

/* Draws the player on the minimap: a 2×2 red square at the current position,
 * plus a yellow segment MINIMAP_SCALE pixels long in the player’s
 * direction (dir_x/dir_y scaled by MINIMAP_SCALE). */
static void	draw_mm_player(t_game *game)
{
	int	px;
	int	py;
	int	i;

	px = MINIMAP_MARGIN + (int)(game->player.pos_x * MINIMAP_SCALE);
	py = MINIMAP_MARGIN + (int)(game->player.pos_y * MINIMAP_SCALE);
	my_mlx_pixel_put(&game->img, px, py, MINIMAP_PLAYER_COLOR);
	my_mlx_pixel_put(&game->img, px + 1, py, MINIMAP_PLAYER_COLOR);
	my_mlx_pixel_put(&game->img, px, py + 1, MINIMAP_PLAYER_COLOR);
	my_mlx_pixel_put(&game->img, px + 1, py + 1, MINIMAP_PLAYER_COLOR);
	i = 1;
	while (i <= MINIMAP_SCALE)
	{
		my_mlx_pixel_put(&game->img,
			px + (int)(game->player.dir_x * i),
			py + (int)(game->player.dir_y * i),
			MINIMAP_DIR_COLOR);
		i++;
	}
}

/* Entry point for the minimap: draws the grid then overlays the player. */
void	render_minimap(t_game *game)
{
	draw_mm_grid(game);
	draw_mm_player(game);
}
