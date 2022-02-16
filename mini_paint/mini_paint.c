#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

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
	float 	radio;
	char	c;
} t_paint;

static int ft_ratio(t_paint *p, int i, int j)
{
	float ratio;
	float absx;
	float absy;

	absx = p->x - j;
	absy = p->y - i;
	if (p->r == 'C')
	{
		ratio = sqrtf(powf(absx, 2) + powf(absy, 2));
		if (ratio <= p->radio)
			return (1);
	}
	else if (p->r == 'c'){
		ratio = sqrtf(powf(absx, 2) + powf(absy, 2));
		if (ratio <= p->radio - 1)
			return (0);
		else if (ratio <= p->radio)
			return (1);
		else
			return (0);
	}
	return (0);
}

static int ft_square(t_paint *p)
{
	int i = -1;
	int j = -1;

	while (++i < p->hg)
	{
		while (++j < p->wd)
		{
			if (ft_ratio(p, i, j))
				p->map[i][j] = p->c;
		}
		j = -1;
	}
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
		read = fscanf(p.fd, "%c %f %f %f %c\n", &p.r, &p.x, &p.y, &p.radio, &p.c);
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
