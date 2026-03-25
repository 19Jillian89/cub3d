/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/23 14:56:49 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 19:30:55 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# include <math.h>

/* SCREEN RESOLUTION — 1280x720 HD, not required in .cub file (2026) */
# define SCREEN_WIDTH			1280
# define SCREEN_HEIGHT			720

/* TEXTURE SIZE — must be square, preferably power of 2 */
# define TEXTURE_WIDTH			64
# define TEXTURE_HEIGHT			64

/* MOVEMENT AND ROTATION SPEED */
# define MOVE_SPEED				0.05
# define ROT_SPEED				0.03

/* KEY CODES — Linux X11 */
# define KEY_ESC				65307
# define KEY_W					119
# define KEY_A					97
# define KEY_S					115
# define KEY_D					100
# define KEY_Z					122
# define KEY_Q					113
# define KEY_UP					65362
# define KEY_DOWN				65364
# define KEY_LEFT				65361
# define KEY_RIGHT				65363
# define KEY_E					101

/* MLX HOOK EVENT CODES */
/* KeyPress=2, KeyRelease=3, DestroyNotify=17 (window X click) */
# define EVENT_KEY_PRESS		2
# define EVENT_KEY_RELEASE		3
# define EVENT_DESTROY_NOTIFY	17

/* MLX EVENT MASKS — KeyPressMask=1, KeyReleaseMask=2 */
# define MASK_KEY_PRESS			1
# define MASK_KEY_RELEASE		2

/* COLORS — format 0x00RRGGBB, built as (r << 16 | g << 8 | b) */
# define COLOR_BLACK			0x00000000
# define COLOR_WHITE			0x00FFFFFF
# define COLOR_RED				0x00FF0000
# define COLOR_GREEN			0x0000FF00
# define COLOR_BLUE				0x000000FF
# define DEFAULT_FLOOR_COLOR	0x00555555
# define DEFAULT_CEILING_COLOR	0x00333333

/* DDA — infinity value used when ray_dir is 0, avoids division by zero */
# define INF					1e30

/* BOOLEAN VALUES */
# define FALSE					0
# define TRUE					1

/* WALL TEXTURE INDICES — maps to textures[4] array in t_game */
# define TEX_NO					0
# define TEX_SO					1
# define TEX_WE					2
# define TEX_EA					3

/* MINIMAP — bonus overlay */
# define MINIMAP_SCALE			6
# define MINIMAP_MARGIN			10
# define MINIMAP_WALL_COLOR		0x00FFFFFF
# define MINIMAP_FLOOR_COLOR	0x00444444
# define MINIMAP_DOOR_COLOR		0x00FF8800
# define MINIMAP_PLAYER_COLOR	0x00FF0000
# define MINIMAP_DIR_COLOR		0x00FFFF00

/* ANIMATED SPRITES — bonus */
# define ANIM_FRAMES			20
# define ANIM_FRAME_DELAY		15

#endif