/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:58:44 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:58:46 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	check_door(t_parsed_data *parsed)
{
	if (!parsed->doors)
		return (0);
	return (parsed->textures_name[DOOR_TEXTURE] == NULL);
}

int	check_player(char **map)
{
	int		i;
	int		j;
	size_t	count;

	i = 0;
	count = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (ft_strchr(PJ_CHARS, map[i][j]))
				count++;
			j++;
		}
		i++;
	}
	return (count != 1);
}

void	check_map(t_parsed_data *parsed)
{
	int	count;

	count = 0;
	if (!parsed->map)
		parse_error(ERROR_MAP, parsed, 1);
	count += map_check_characters(parsed->map, VALID_MAP_CHARS);
	count += check_player(parsed->map);
	count += flood_fill(parsed->map, parsed);
	count += check_door(parsed);
	if (count != 0)
		parse_error(ERROR_MAP, parsed, 1);
}
