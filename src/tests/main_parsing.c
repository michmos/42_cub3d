
#include "../../cub3d.h"

static void	test_put_map(t_map *map)
{
	printf("map width: %zu\n", map->width);
	printf("map height: %zu\n", map->height);
	for (int j =  0; j < map->height - 1; ++j) {
		printf("%33.33s\n", &map->map[33 * j]);
	}
}

static void	test_put_input(t_input *input)
{
	printf("map:\n");
	test_put_map(&input->map);
	printf("\nnorth_txtre: %s\n", input->north_txtre);
	printf("\nsouth_txtre: %s\n", input->south_txtre);
	printf("\nwest_txtre: %s\n", input->west_txtre);
	printf("\neast_txtre: %s\n", input->east_txtre);
	printf("\nfloor: r: %i g: %i b: %i\n", input->floor.r, input->floor.g, input->floor.b);
	printf("\nceiling: r: %i g: %i b: %i\n", input->ceiling.r, input->ceiling.g, input->ceiling.b);
}

int	main(int argc, char *argv[])
{
	t_cub3d	cub3d;
	t_input	input;

	if (argc != 2)
	{
		put_err(USAGE);
		return (1);
	}
	if (parse_file(&input, argv[1]) == -1)
		return 1;
	test_put_input(&input);
	free_input(&input);
	return (0);
}
