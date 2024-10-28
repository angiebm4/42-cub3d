/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood_fill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:58:58 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:59:00 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

static int	is_invalid_position(int x, int y, char **map)
{
	size_t	st_y;

	st_y = y;
	if (x < 0 || y < 0 || st_y >= (map_length(map)) || x >= ft_strlen(map[y]))
		return (1);
	if (ft_strlen(map[y]) <= x)
		return (1);
	if (map[y][x] == ' ')
		return (1);
	return (0);
}

int	rec_floof_fill(int x, int y, char **map)
{
	int	count;

	if (is_invalid_position(x, y, map))
		return (1);
	if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	count = 0;
	count += rec_floof_fill(x, y - 1, map);
	count += rec_floof_fill(x + 1, y, map);
	count += rec_floof_fill(x, y + 1, map);
	count += rec_floof_fill(x - 1, y, map);
	return (count != 0);
}

static int	search_start_position(char **map, int *x, int *y)
{
	int	i;

	i = -1;
	while (PJ_CHARS[++i])
	{
		if (search_map(map, PJ_CHARS[i], x, y))
			return (1);
	}
	return (0);
}

static int	check_result(char **map)
{
	int	i;
	int	j;

	i = -1;
	while (map[++i])
	{
		j = -1;
		while (map[i][++j])
		{
			if (map[i][j] != '1' && map[i][j] != ' ')
				return (1);
		}
	}
	return (0);
}

int	flood_fill(char **map, t_parsed_data *parsed)
{
	char	**cpy;
	int		x;
	int		y;
	int		result;

	cpy = copy_map(map);
	if (!cpy)
		parse_error(ERROR_MALLOC, parsed, 0);
	result = 0;
	while (!result && \
		(search_start_position(cpy, &x, &y) || search_map(cpy, '0', &x, &y)))
		result = rec_floof_fill(x, y, cpy);
	result += check_result(cpy);
	ft_free_split(cpy);
	return (result);
}
