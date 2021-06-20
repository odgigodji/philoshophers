/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:35:10 by namerei           #+#    #+#             */
/*   Updated: 2021/06/19 19:53:09 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

time_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	initFils(t_fil *fil, t_check *check, t_param *param)
{
	int	i;

	i = -1;
	while (++i < param->numOfFil)
		pthread_mutex_init(&check->utils[i], NULL);
	i = -1;
	while (++i < param->numOfFil)
	{
		fil[i].countOfEat = 0;
		fil[i].check = check;
		fil[i].param = param;
		fil[i].id = i + 1;
		fil[i].isFull = 0;
		fil[i].nowIsEating = 0;
		fil[i].param->start = get_time();
		if (i == 0)
			fil[i].right = param->numOfFil - 1;
		else
			fil[i].right = i - 1;
		fil[i].left = i;
		pthread_mutex_init(&fil->param->forks[i], NULL);
		fil[i].toLive = get_time() + fil->param->timeToDie;
	}
	return (0);
}

int	parser(t_param *param, t_check *check, char **av, int ac)
{
	int	**in;
	int	i;

	if (ac < 5 || ac > 6)
		return (1);
	in = malloc(sizeof(int *) * ac);
	i = 0;
	in[0] = &param->numOfFil;
	in[1] = &param->timeToDie;
	in[2] = &param->timeToEatt;
	in[3] = &param->timeToSleep;
	in[4] = &param->fullness;
	while (++i < ac && av[i])
	{
		in[i - 1][0] = ft_atoi(av[i]);
		if (in[i - 1][0] <= 0 || in[0][0] > 200)
			return (1);
	}
	free(in);
	check->philsAreAlive = 1;
	param->start = get_time();
	return (0);
}
