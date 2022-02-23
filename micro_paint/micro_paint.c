#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_paint
{
	FILE	*fd;
	char	**map;
	int	wd;
	int	hg;
	char	fill;

	char 	r;
	float 	x;
	float 	y;
	float 	sizex;
	float 	sizey;
	char	c;
} t_paint;


static void ft_round(float *f)
{
	int i;

	i = (int)*f;
	//printf("float is == %f\n", *f);
	if(i < *f)
		*f = i + 1;
	//printf("i + 1 == %d\n", i + 1);
	//printf("floatRounded->%f\n", *f);
}

//check wether we have to make a full square or a empty one,
//if R then we see if we are inside the area of the square and then substitute those with the char of choice
//if r we see if we are inside the area of the square (the first part of the if) and then if we are inside the area of the inner square (the part that must be empty) and the we substitute the borders with the char of choice
static int ft_square(t_paint *p)
{
	int i = -1;
	int j = -1;

	if (p->r == 'R')
	{
		while (++i < p->hg)
		{
			while (++j < p->wd)
			{
				if (j >= p->x && i >= p->y && j <= p->x + p->sizex  && i <= p->y + p->sizey)
					p->map[i][j] = p->c;
			}
			j = -1;
		}
	}
	else if (p->r == 'r')
	{
		while (++i < p->hg)
		{
			while (++j < p->wd)
			{
				if ((j >= p->x && i >= p->y && j <= p->x + p->sizex  && i <= p->y + p->sizey ) && !(j >= p->x +1  && i >= p->y +1  && j < p->x + p->sizex -1 && i < p->y + p->sizey -1))
					p->map[i][j] = p->c;
			}
			j = -1;
		}

	}
	else
		return (1);
	return (0);
}

static void ft_map(t_paint *p)
{
	int i = -1;
	int j = -1;

	while (++i < p->hg)
	{
		while (++j < p->wd)
			p->map[i][j] = p->fill;
		j = -1;
	}
}

static int ft_alloc(t_paint *p)
{
	int i = -1;

	p->map = (char **)malloc(sizeof(char *) * (p->hg + 1));
	while (++i < p->hg)
	{
		p->map[i] = (char *)malloc(sizeof(char) * (p->wd + 1));
		p->map[i][p->wd] = '\0';
	}
	p->map[p->hg] = 0;
	return (0);
}

int main(int argc, char **argv)
{
	t_paint p;
	int read;
	int i = -1;

	if (argc != 2)
		return (1);
	memset(&p, 0, sizeof(p));
	p.fd = fopen(argv[1], "r");
	read = fscanf(p.fd, "%d %d %c\n", &p.wd, &p.hg, &p.fill);
	if (read == -1)
		return (1);
	if (ft_alloc(&p))
		return (1);
	ft_map(&p);
	while (1)
	{
		read = fscanf(p.fd, "%c %f %f %f %f %c\n", &p.r, &p.x, &p.y, &p.sizex, &p.sizey, &p.c);
		ft_round(&p.x);
		ft_round(&p.y);
		//ft_round(&p.sizex);
		//ft_round(&p.sizey);
		if (read == -1)
			break ;
		if (ft_square(&p))
			break ;
	}
	while (p.map[++i])
	{
		printf("%s\n", p.map[i]);
		free(p.map[i]);
	}
	free(p.map);
	
}
