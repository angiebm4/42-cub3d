/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abarrio- <abarrio-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 13:04:06 by abarrio-          #+#    #+#             */
/*   Updated: 2024/10/28 13:04:10 by abarrio-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	doors_init(t_cube *cube, t_parsed_data *parsed)
{
	t_list	*it;
	t_list	*node;
	t_door	*door;

	it = parsed->doors;
	while (it)
	{
		door = ft_calloc(1, sizeof(t_door));
		if (!door)
			cube_destroy(cube, 1);
		door->x = ((t_door *)it->content)->x;
		door->y = ((t_door *)it->content)->y;
		door->open = ((t_door *)it->content)->open;
		node = ft_lstnew(door);
		if (!node)
			cube_destroy(cube, 1);
		ft_lstadd_back(&cube->doors, node);
		it = it->next;
	}
}
