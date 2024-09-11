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
			exit(1); /* TODO: Check malloc */
		door->x = ((t_door *)it->content)->x;
		door->y = ((t_door *)it->content)->y;
		door->open = ((t_door *)it->content)->open;
		node = ft_lstnew(door);
		if (!node)
			exit(1); /* TODO: Check malloc */
		ft_lstadd_back(&cube->doors, node);
		it = it->next;
	}
}
