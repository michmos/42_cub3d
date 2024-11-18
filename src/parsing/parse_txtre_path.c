
#include "../../cub3d.h"

t_error	parse_txtre_path(t_in_stream *stream, char **txtre_path)
{
	size_t		path_len;

	// skip keyword
	stream->idx += 3;
	skip_chars(" ", stream);
	// set path
	path_len = ft_wordlen(cur_ptr(stream));
	*txtre_path = ft_substr(stream->buffer, stream->idx, path_len);
	if (!txtre_path)
	{
		perror("malloc");
		return (-1);
	}
	// update index
	stream->idx += path_len;
	return (0);
}

// TODO: co

