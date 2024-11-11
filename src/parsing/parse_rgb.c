
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
	// skip keyword
	stream->idx += 2;
	skip_chars(" ", stream);
	// parse r
	if (parse_rgb_component(stream, &rgb->r) == -1)
	{
		return (-1);
	}
	if (skip_separators(stream) == -1)
	{
		return (-1);
	}
	// parse g
	if (parse_rgb_component(stream, &rgb->g) == -1)
	{
		return (-1);
	}
	if (skip_separators(stream) == -1)
	{
		return (-1);
	}
	// parse b
	if (parse_rgb_component(stream,&rgb->b) == -1)
	{
		return (-1);
	}
	return (0);
}
