/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   SnakeGame.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yourname- <marvin@42.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 4242/42/42 42:42:42 by somename-         #+#    #+#             */
/*   Updated: 4242/42/42 42:42:42 by somename-        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "canvas.h"
#include "game.h"

static t_point	next_position(t_snake *snake)
{
	return ((t_point){snake->coords[0].x + snake->direction.x,
		snake->coords[0].y + snake->direction.y});
}

static void	fix_position(t_game *game)
{
	int	i;

	i = 0;
	while (i < game->snake.len)
	{
		if (game->snake.coords[i].x >= 0)
			game->snake.coords[i].x = game->snake.coords[i].x
				% game_width(game);
		else
			game->snake.coords[i].x = game_width(game);
		if (game->snake.coords[i].y >= 0)
			game->snake.coords[i].y = game->snake.coords[i].y
				% game_height(game);
		else
			game->snake.coords[i].y = game_height(game);
		i++;
	}
}

static void	shift_snake(t_snake *snake)
{
	t_point	new_head;

	new_head = next_position(snake);
	memcpy(snake->coords + 1, snake->coords,
		(snake->len - 1) * sizeof(t_point));
	memcpy(snake->coords, &new_head, sizeof(t_point));
}

static void	update_food(t_game *game)
{
	t_point	head;

	head = game->snake.coords[0];
	if (head.x == game->food.x && head.y == game->food.y
		&& game->snake.len <= MAX_LEN - 1)
	{
		game->food = (t_point){rand() % game_width(game),
			rand() % game_height(game)};
		memcpy(game->snake.coords + game->snake.len,
			game->snake.coords, sizeof(t_point));
		game->snake.len++;
		game->speed -= (game->snake.len / 5);
	}
	draw_square((t_square){game->food.x * game->tile_size,
		game->food.y * game->tile_size, game->tile_size - 1,
		rand() % 2147483647}, game->img);
	if (game->snake.len >= MAX_LEN)
		printf("MAX SIZE REACHED, CAN'T GROW ANYMORE!\n");
}

static void	snake_died(t_game *game)
{
	int		i;
	t_point	head;

	head = game->snake.coords[0];
	i = 0;
	while (++i < game->snake.len - 1)
	{
		if (head.x == game->snake.coords[i].x
			&& head.y == game->snake.coords[i].y)
			exit_game(&game->img);
	}
}

int	update(t_game *game)
{
	static short int	fps = 0;

	if (game->pause || fps-- != 0)
		return (1);
	fps = game->speed * 10;
	remove_snake(game);
	snake_died(game);
	shift_snake(&game->snake);
	fix_position(game);
	update_food(game);
	put_snake(game);
	game->snake.can_change = true;
	return (0);
}

static void	change_direction(t_game *game, int key_pressed)
{
	if (!game->snake.can_change)
		return ;
	if (key_pressed == UP && game->snake.direction.x != 0
		&& game->snake.direction.y != 1)
			game->snake.direction = (t_point){0, -1};
	else if (key_pressed == DOWN && game->snake.direction.x != 0
		&& game->snake.direction.y != -1)
			game->snake.direction = (t_point){0, 1};
	else if (key_pressed == RIGHT && game->snake.direction.x != 1
		&& game->snake.direction.y != 0)
			game->snake.direction = (t_point){1, 0};
	else if (key_pressed == LEFT && game->snake.direction.x != -1
		&& game->snake.direction.y != 0)
			game->snake.direction = (t_point){-1, 0};
	game->snake.can_change = false;
}

int	read_keys(int key_pressed, void *param)
{
	t_game	*game;

	game = (t_game *)param;
	if (key_pressed == ESC || !game->img.img_ptr)
		exit_game(&game->img);
	else if (key_pressed == PAUSE)
		game->pause = !game->pause;
	else if (key_pressed == DOWN || key_pressed == KEY_S)
		change_direction(game, DOWN);
	else if (key_pressed == UP || key_pressed == KEY_W)
		change_direction(game, UP);
	else if (key_pressed == LEFT || key_pressed == KEY_A)
		change_direction(game, LEFT);
	else if (key_pressed == RIGHT || key_pressed == KEY_D)
		change_direction(game, RIGHT);
	else
		return (-1);
	return (0);
}
