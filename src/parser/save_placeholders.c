/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_placeholders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:59:40 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:59:43 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

/******************************************************/

void	move_arguments(char **buffer, int replace)
{
	while (buffer[replace])
	{
		buffer[replace] = buffer[replace + 1];
		replace++;
	}
}

void	trim_arguments(t_parsed_data *parsed, char **buffer)
{
	int		i;
	char	*trimmed;

	i = 1;
	while (buffer[i])
	{
		trimmed = ft_strtrim(buffer[i], EMPTY_SET);
		if (!trimmed)
			parse_error(ERROR_MALLOC, parsed, 0);
		if (!trimmed[0])
		{
			free(trimmed);
			free(buffer[i]);
			move_arguments(buffer, i);
			continue ;
		}
		free(buffer[i]);
		buffer[i] = trimmed;
		i++;
	}
}

/******************************************************/

void	save_texture(t_parsed_data *parsed, char *filename, int ph)
{
	if (check_extension(filename, TEXTURE_EXTENSION))
		parsed->textures_name[ph] = ft_strdup(filename);
}

static void	save_pixel(t_parsed_data *parsed, char *buffer, int ph)
{
	char	**pixel_spl;
	int		index;

	index = ph - TEXTURES_COUNT;
	pixel_spl = ft_split(buffer, PIXEL_SEPARATOR);
	if (!pixel_spl)
		parse_error(ERROR_MALLOC, parsed, 0);
	if (map_length(pixel_spl) == 3)
	{
		if (ft_isnumber(pixel_spl[0]))
			parsed->default_pixels[index].red = ft_atoi(pixel_spl[0]);
		if (ft_isnumber(pixel_spl[1]))
			parsed->default_pixels[index].green = ft_atoi(pixel_spl[1]);
		if (ft_isnumber(pixel_spl[2]))
			parsed->default_pixels[index].blue = ft_atoi(pixel_spl[2]);
	}
	ft_free_split(pixel_spl);
}

int	save_placeholder(t_parsed_data *parsed, char **buffer, int ph)
{
	trim_arguments(parsed, buffer);
	if (ph < 0 || map_length(buffer) != 2)
		return (0);
	if (ph < TEXTURES_COUNT)
		save_texture(parsed, buffer[1], ph);
	else
		save_pixel(parsed, buffer[1], ph);
	return (1);
}
