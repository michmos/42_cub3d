/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils3.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:29:47 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/20 10:32:02 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// output line until new line character
void	put_cur_line(int fd, t_in_stream *stream)
{
	size_t	len;
	char	*nl_ptr;
	size_t	i;

	i = stream->idx;
	if (stream->crnt_lne_nbr > 1)
	{
		while (stream->buffer[i] != '\n')
			i--;
		i++;
	}
	else
		i = 0;
	nl_ptr = ft_strchr(&stream->buffer[i], '\n');
	if (nl_ptr)
		len = nl_ptr - &stream->buffer[i];
	else
		len = ft_strlen(&stream->buffer[i]);
	write(fd, &stream->buffer[i], len);
	write(fd, "\n", 1);
}

// output word until new line character
void	put_cur_word(int fd, const char *str)
{
	size_t	len;

	len = ft_wordlen(str);
	write(fd, str, len);
	write(fd, "\n", 1);
}

void	replace_spaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
		{
			str[i] = '1';
		}
		i++;
	}
}
