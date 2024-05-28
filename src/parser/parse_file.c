# include "../../include/cub3d.h"

static int  line_is_empty(char *line, char *empty_set)
{
    int index;

    index = 0;
    while (line[index])
    {
        if (ft_strchr(empty_set, line[index]) == NULL)
            return 0;
        index++;
    }

    return 1;
}

static int  line_is_comment(char *line, char *comment_set)
{
    if (line == NULL)
        return 0;
    
    return (ft_strchr(comment_set, line[0]) != NULL);
}

static int  line_is_placeholder(char *supposed_ph)
{
    char    **spl;
    int     index;
    int     res;

    /* TODO: malloc error, what do? */
    spl = ft_split(VIEWS_PLACEHOLDERS, SEPARATOR_PLACEHOLDER);
    if (!spl)
        return (-1);

    index = 0;
    res = -1;
    while (spl[index])
    {
        if (ft_strcmp(spl[index], supposed_ph) == 0)
        {
            res = index;
            break ;
        }
        index++;
    }
    ft_free_split(spl);
    return (res);
}


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
            /* Separar por el espacio */
            /* TODO: proteger malloc */
            spl = ft_split(buffer, ' ');

            /* Checkear el primer arg. Si es valido, guardarlo*/
                printf("· Analizando {%s}\n", spl[0]);
            placeholder = line_is_placeholder(spl[0]);
            ft_free_split(spl);
            if (placeholder < 0) {
                printf("\t=> X\n");
                break ;
            }
            printf("\t=> Es placeholder\n");
            
            /* En el momento en el que no sea valido, se empezará a guardar el mapa */
        }

        /* Iterate on the map*/
        free(buffer);
        buffer = get_next_line(parsed->fd);
    }

    if (buffer)
        free(buffer);

    printf("OUT\n");

    /* The information should be saved */
}
