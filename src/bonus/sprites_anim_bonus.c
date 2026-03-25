/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprites_anim_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 19:23:32 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 19:32:12 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Simple LCG pseudo-random generator (no rand() allowed by norm). */
static unsigned int	lcg_rand(unsigned int seed)
{
	return (seed * 1664525 + 1013904223);
}

/* Returns a glitch color: cyan, green or white, cyber-themed. */
static int	glitch_color(unsigned int seed)
{
	int	pick;

	pick = seed % 3;
	if (pick == 0)
		return (0x0000FF99);
	if (pick == 1)
		return (0x0000FF44);
	return (0x00AAFFAA);
}

/* Draws random glitch pixels on the 4 screen borders.
 * Border thickness is ANIM_FRAMES pixels.
 * Only ~1 in 4 pixels is drawn to create a sparse glitch look. */
static void	draw_glitch_borders(t_game *game, unsigned int seed)
{
	int	x;
	int	y;

	y = 0;
	while (y < SCREEN_HEIGHT)
	{
		x = 0;
		while (x < SCREEN_WIDTH)
		{
			if (x < ANIM_FRAMES || x >= SCREEN_WIDTH - ANIM_FRAMES
				|| y < ANIM_FRAMES || y >= SCREEN_HEIGHT - ANIM_FRAMES)
			{
				seed = lcg_rand(seed + x * 7 + y * 13);
				if (seed % 4 == 0)
					my_mlx_pixel_put(&game->img, x, y, glitch_color(seed));
			}
			x++;
		}
		y++;
	}
}

/* Entry point: uses anim_frame as seed base so glitch pattern
 * changes every frame, creating a flickering effect. */
void	render_animated_sprites(t_game *game)
{
	unsigned int	seed;

	game->anim_frame = (game->anim_frame + 1)
		% (ANIM_FRAMES * ANIM_FRAME_DELAY);
	seed = (unsigned int)(game->anim_frame * 6271 + 9973);
	draw_glitch_borders(game, seed);
}
