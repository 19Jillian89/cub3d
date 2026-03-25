/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilnassi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/17 18:14:40 by ilnassi           #+#    #+#             */
/*   Updated: 2026/03/22 14:35:18 by ilnassi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*Iterates over each pixel of the weapon image and draws it
on the screen buffer, skipping black and fully transparent pixels.
start_x and start_y define the top-left corner of the weapon on screen.*/
static void	draw_weapon_pixels(t_game *game, int start_x, int start_y)
{
	int		x;
	int		y;
	int		color;
	char	*pixel;

	y = start_y;
	while (y < SCREEN_HEIGHT)
	{
		x = start_x;
		while (x < (SCREEN_WIDTH + game->weapon.width) / 2)
		{
			pixel = game->weapon.img.addr
				+ ((y - start_y) * game->weapon.img.line_length
					+ (x - start_x) * (game->weapon.img.bpp / 8));
			color = *(int *)pixel;
			if (color != 0 && color != (int)0xFF000000)
				my_mlx_pixel_put(&game->img, x, y, color);
			x++;
		}
		y++;
	}
}

/*Load weapon image from XPM file.
Returns 1 if error, 0 if ok.*/
int	load_weapon(t_game *game)
{
	game->weapon.img.img = mlx_xpm_file_to_image(game->mlx,
			"textures/weapon/weapon_idle.xpm",
			&game->weapon.width,
			&game->weapon.height);
	if (!game->weapon.img.img)
		return (1);
	return (0);
}

/*Computes the weapon position centered horizontally and anchored
to the bottom of the screen, retrieves the image pixel data address,
then calls draw_weapon_pixels() to render it on the screen buffer.*/
void	draw_weapon(t_game *game)
{
	int	start_x;
	int	start_y;

	if (!game->weapon.img.img)
		return ;
	game->weapon.img.addr = mlx_get_data_addr(game->weapon.img.img,
			&game->weapon.img.bpp,
			&game->weapon.img.line_length,
			&game->weapon.img.byte_order);
	start_x = (SCREEN_WIDTH - game->weapon.width) / 2;
	start_y = SCREEN_HEIGHT - game->weapon.height;
	draw_weapon_pixels(game, start_x, start_y);
}

/*Frees the weapon image.
Call from free_game().*/
void	free_weapon(t_game *game)
{
	if (game->weapon.img.img)
		mlx_destroy_image(game->mlx, game->weapon.img.img);
}
