# include "../../include/cub3d.h"

void    parse_file(t_parsed_data *parsed)
{
    char    *buffer;
    char    **spl;
    int     placeholder;

    buffer = get_next_line(parsed->fd);
    while (buffer)
    {

        /* Check conditions to skip the line */
        if (
            !line_is_empty(buffer, EMPTY_SET) &&
            ft_strlen(buffer) != 1 &&
            !line_is_comment(buffer, COMMENT_SET)
        )
        {
            /* Split the line on the space charcater */
            spl = ft_split(buffer, ' ');

            /* Check if there is a placeholder on the line */
            placeholder = line_is_placeholder(spl[0]);

            ft_free_split(spl);

            if (placeholder < 0)
                break ;
        }

        /* Iterate on the map*/
        free(buffer);

        buffer = get_next_line(parsed->fd);
    }

    while (buffer) {
        free(buffer);
        buffer = get_next_line(parsed->fd);
    }

    /* The information should be saved */
}
