/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:58:53 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:58:55 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	clean_map(char **map)
{
	size_t	size;

	size = map_length(map);
	while (size > 0)
	{
		size--;
		if (!line_is_empty(map[size], EMPTY_SET))
			break ;
		ft_mfree(1, &map[size]);
	}
}
