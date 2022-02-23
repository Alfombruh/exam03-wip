/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eperaita <eperaita@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 11:28:24 by eperaita          #+#    #+#             */
/*   Updated: 2022/02/23 21:26:44 by jofernan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>

typedef struct s_matrix{
	int w;
	int h;
	char ch;
	char *matrix;
} t_matrix;

typedef struct s_paint{
	char type;
	float rad;
	float x;
	float y;
	char fill;
} t_paint;


static void ft_print(t_matrix *canvas)
{
	int j;

	j = 0;
	while (canvas->matrix[j])
	{
		write(1, &canvas->matrix[j], canvas->w);
    	write(1, "\n", 1);
    	j += canvas->w;
	}
}

static int ft_check_void(float dist, t_paint *mini)
{
	if (mini->rad - dist < 1)
		return (1);
	else
		return (0);
}

static int ft_check_point(int i, int j, t_matrix *canvas, t_paint *mini)
{
	float dist;

	dist = sqrtf(pow(i - mini->x, 2) + pow(j - mini->y, 2));
	if(dist > mini->rad)
		return (0);
	else
	{
		if(mini->type == 'C')
			return (1);
		else
			return (ft_check_void(dist, mini));
	}
}


static void ft_paint(t_matrix *canvas, t_paint *mini)
{
	int j;
	int i;

	j = 0;
	while (j < canvas->h)
	{
		i = 0;
		while ( i < canvas->w)
		{
			if(ft_check_point(i, j, canvas, mini))
				canvas->matrix[i + j * canvas->w] = mini->fill;
			i++;
		}
		j++;
	}
}

static int ft_check_variables(t_paint *mini)
{
	if (mini->rad <= 0)
		return (1);
	if (mini->type != 'c' && mini->type != 'C')
		return (1);
	return (0);
}

static int ft_mini(FILE *fd, t_matrix *canvas, t_paint *mini)
{
	int read;

	while(1)
	{
		read = fscanf(fd, "%c %f %f %f %c\n", &mini->type, &mini->x, &mini->y, &mini->rad, &mini->fill);
		if (read == -1)
			return (0);
		if (read != 5)
			return (1);
		if(ft_check_variables(mini))
			return (1);
		ft_paint(canvas, mini);
	}
}

static int ft_canvas(FILE *fd, t_matrix *canvas)
{
	int read;

	read = fscanf(fd, "%d %d %c\n", &canvas->w, &canvas->h, &canvas->ch);
	if (read != 3)
		return (1);
	if (canvas->w > 300 || canvas->h > 300 || canvas->w <= 0 || canvas->h <= 0)
		return (1);
	canvas->matrix = (char *)malloc(canvas->w * canvas->h + 1);
	if(!canvas->matrix)
		return (1);
	memset(canvas->matrix, canvas->ch, canvas->w * canvas->h);
	canvas->matrix[canvas->w * canvas->h] = '\0';
	return (0);
}

static int op_status(FILE *fd, t_matrix *canvas, int status)
{
	if (status == 1)
		write(1, "Error: argument\n", 16);
	else if (status == 2)
		write(1, "Error: Operation file corrupted\n", 32);
	if (canvas->matrix)
		free(canvas->matrix);
	if (fd)
		fclose(fd);
	if(status)
		return (1);
	else
		return (0);
	
}

int main(int argc, char **argv)
{
	t_matrix canvas;
	t_paint mini;
	FILE *fd;

	fd = NULL;
	canvas.matrix = NULL;
	if (argc != 2) //gestion de args
		return (op_status(fd, &canvas, 1));
	fd = fopen(argv[1], "r");//abrir el canal
	if (!fd)
		return (op_status(fd, &canvas, 2));
	if(ft_canvas(fd, &canvas)) //crear lienzo, si devuleve 1 error. 
		return (op_status(fd, &canvas, 2));
	if(ft_mini(fd, &canvas, &mini))//sustituir chars correspondientes por cada llamada a minipaint (bucle de paint). Puede dar error????
		return (op_status(fd, &canvas, 2));
	ft_print(&canvas); // printea todo el array, cada canvas->w mete un salto de linea
	return (op_status(fd, &canvas, 0));


}
