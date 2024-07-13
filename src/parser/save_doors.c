#include "../../include/cub3d.h"

void	save_doors(t_parsed_data *parsed)
{
	int		x;
	int		y;
	t_door	*door;
	t_list	*node;

	while (search_map(parsed->map, 'D', &x, &y))
	{
		door = calloc(1, sizeof(t_door));
		if (!door)
			parse_error(ERROR_MALLOC, parsed, 0);
		door->x = x;
		door->y = y;
		door->open = 0;

		node = ft_lstnew(door);
		if (!node)
		{
			free(door);
			parse_error(ERROR_MALLOC, parsed, 0);
		}
		ft_lstadd_back(&parsed->doors, node);
		parsed->map[y][x] = '0';
	}
}
