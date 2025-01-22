/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_rgb.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: mmoser <mmoser@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2025/01/20 10:29:22 by mmoser        #+#    #+#                 */
/*   Updated: 2025/01/22 11:22:30 by dode-boe      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../cub3d.h"

static int	skip_separators(t_in_stream *stream)
{
	skip_chars(" ", stream);
	if (cur_char(stream) != ',')
	{
		put_parsing_err(stream, "Missing separator");
		put_err(RED "Expected: \",\"\n" RESET_COLOR);
		return (-1);
	}
	stream->idx++;
	skip_chars(" ", stream);
	return (0);
}

static t_error	parse_rgb_component(t_in_stream *stream, u_int8_t *comp)
{
	int	temp;

	if (safe_atoi(cur_ptr(stream), &temp) == -1 || temp < 0 || temp > 255)
	{
		put_parsing_err(stream, "Invalid number");
		put_err(RED "Number must be between 0 and 255" RESET_COLOR);
		return (-1);
	}
	*comp = temp;
	skip_num(stream);
	return (0);
}

t_error	parse_rgb(t_in_stream *stream, t_rgb *rgb)
{
	const char	*keyword_pos;

	keyword_pos = cur_ptr(stream);
	stream->idx += 2;
	skip_chars(" ", stream);
	if (parse_rgb_component(stream, &rgb->r) == -1)
		return (-1);
	if (skip_separators(stream) == -1)
		return (-1);
	if (parse_rgb_component(stream, &rgb->g) == -1)
		return (-1);
	if (skip_separators(stream) == -1)
		return (-1);
	if (parse_rgb_component(stream, &rgb->b) == -1)
		return (-1);
	rgb->a = 0xFF;
	return (0);
}
