/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhacman <vhacman@student.42roma.it>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:22:36 by vhacman           #+#    #+#             */
/*   Updated: 2026/03/24 17:43:21 by vhacman          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/* Converts the 3 strings R/G/B into a packed 32‑bit color.
 * We validate with is_valid_uint_str BEFORE calling ft_atoi:
 * ft_atoi does not distinguish "-0" from "0" and does not report overflow,
 * so it is better to reject any string that is not plain digits early.
 * The check rgb[i] > 255 catches values like "256" or "999".
 * Returns the packed color (>= 0), -1 if any field is invalid. [web:32] */
static int	parts_to_color(char **parts)
{
	int	rgb[3];
	int	i;

	i = 0;
	while (i < 3)
	{
		if (!is_valid_uint_str(parts[i]))
			return (-1);
		rgb[i] = ft_atoi(parts[i]);
		if (rgb[i] < 0 || rgb[i] > 255)
			return (-1);
		i++;
	}
	return (create_color(rgb[0], rgb[1], rgb[2]));
}

/* Extracts and validates the "R,G,B" string that follows the identifier (F/C).
 * We use ft_split(',') to separate the components: more robust than sscanf,
 * which is not in the allowed functions.
 * The check !parts[3] rejects "255,0,0,0" (4 components): ft_split with
 * comma as delimiter returns NULL in the fourth slot if there are
 * exactly 3 values. If any of the first three is NULL, we have less than 3
 * expected values: this is also an error.
 * free_str_array frees the ft_split array before returning. [web:105]
 * Returns the packed color (>= 0), -1 if the format is incorrect. */
static int	extract_color(char *line)
{
	char	**parts;
	char	*rgb_str;
	int		color;

	rgb_str = skip_whitespace(line + 2);
	trim_newline(rgb_str);
	parts = ft_split(rgb_str, ',');
	if (!parts)
		return (-1);
	color = -1;
	if (parts[0] && parts[1] && parts[2] && !parts[3])
		color = parts_to_color(parts);
	free_str_array(parts);
	return (color);
}

/* Parses a color line (F = floor, C = ceiling) and stores it in t_game.
 * We use -1 as a sentinel "not set": pure black (0x000000)
 * is a valid color, so we cannot use 0 as default value.
 * The struct is zeroed by calloc at startup, so we explicitly initialize
 * floor_color and ceiling_color to -1 in init_game.
 * We check for duplicates before parsing the value for the same reason
 * as parse_texture: to avoid unnecessary work on invalid input.
 * Returns: 0 on success, 1 on error. [web:105] */
int	parse_color(t_game *game, char *line)
{
	int		*target;
	int		color;

	if (line[0] == 'F')
		target = &game->floor_color;
	else
		target = &game->ceiling_color;
	if (*target != -1)
	{
		error_exit(game, "Duplicate color definition");
		return (1);
	}
	color = extract_color(line);
	if (color == -1)
	{
		error_exit(game, "Invalid color format (expected R,G,B with 0-255)");
		return (1);
	}
	*target = color;
	return (0);
}
