/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils2.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:29:44 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/20 10:31:58 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

// return current character
char	cur_char(t_in_stream *stream)
{
	return (stream->buffer[stream->idx]);
}

// return address of current character
char	*cur_ptr(t_in_stream *stream)
{
	return (&stream->buffer[stream->idx]);
}

// skip whitespaces
void	skip_whitespaces(t_in_stream *stream)
{
	while (cur_char(stream) && ft_is_whitespace(cur_char(stream)))
	{
		if (cur_char(stream) == '\n')
		{
			stream->crnt_lne_nbr++;
		}
		stream->idx++;
	}
}

// skip chars
void	skip_chars(const char *charset, t_in_stream *stream)
{
	while (cur_char(stream) && ft_strchr(charset, cur_char(stream)))
	{
		if (cur_char(stream) == '\n')
		{
			stream->crnt_lne_nbr++;
		}
		stream->idx++;
	}
}

// skip one + or - and digits
void	skip_num(t_in_stream *stream)
{
	if (cur_char(stream) == '-' || cur_char(stream) == '+')
	{
		stream->idx++;
	}
	while (cur_char(stream) && ft_isdigit(cur_char(stream)))
	{
		stream->idx++;
	}
}
