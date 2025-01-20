/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   put_errors.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:29:29 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/20 10:31:23 by mmoser        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

void	put_parsing_err(t_in_stream *stream, const char *msg)
{
	ft_printf_fd(STDERR_FILENO, RED "Error in config file, line %i: %s: ",
		stream->crnt_lne_nbr, msg);
	if (cur_char(stream))
	{
		put_cur_line(STDERR_FILENO, stream);
	}
	else
	{
		ft_printf_fd(STDERR_FILENO, "EOF\n");
	}
	put_err(RESET_COLOR);
}

void	put_expected_tokens(int input_flags)
{
	put_err(RED "Expected one of the following: \n");
	if (input_flags != (NO | SO | EA | WE | C | F))
	{
		if ((input_flags & NO) == 0)
			put_err(" NO <path_to_texture>\n");
		if ((input_flags & SO) == 0)
			put_err(" SO <path_to_texture>\n");
		if ((input_flags & WE) == 0)
			put_err(" WE <path_to_texture>\n");
		if ((input_flags & EA) == 0)
			put_err(" EA <path_to_texture>\n");
		if ((input_flags & C) == 0)
			put_err(" C <r>, <g>, <b>\n");
		if ((input_flags & F) == 0)
			put_err(" F <r>, <g>, <b>\n");
	}
	else
	{
		put_err(" <map>\n");
	}
	put_err(RESET_COLOR);
}
