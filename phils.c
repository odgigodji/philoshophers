/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:34:25 by namerei           #+#    #+#             */
/*   Updated: 2021/06/19 19:53:19 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	ft_usleep(long time)
{
	long	start;

	start = get_time();
	while (get_time() - start < time)
		usleep(30);
}

void	takenForks(t_fil *fil)
{
	if (((fil->id - 1 ) % 2) == 0)
	{
		pthread_mutex_lock(&fil->param->forks[fil->left]);
		message(fil, "has taken a fork", 0);
		pthread_mutex_lock(&fil->param->forks[fil->right]);
		message(fil, "has taken a fork", 0);
	}
	else
	{
		pthread_mutex_lock(&fil->param->forks[fil->right]);
		message(fil, "has taken a fork", 0);
		pthread_mutex_lock(&fil->param->forks[fil->left]);
		message(fil, "has taken a fork", 0);
	}
	fil->nowIsEating = 1;
}

void	puttingForks(t_fil *fil)
{
	if (((fil->id - 1 ) % 2) == 0)
	{
		pthread_mutex_unlock(&fil->param->forks[fil->right]);
		pthread_mutex_unlock(&fil->param->forks[fil->left]);
	}
	else
	{
		pthread_mutex_unlock(&fil->param->forks[fil->left]);
		pthread_mutex_unlock(&fil->param->forks[fil->right]);
	}
	fil->nowIsEating = 0;
}

void	*func(void *arg)
{
	t_fil	*fil;

	fil = (t_fil *)arg;
	while (fil[0].check->philsAreAlive)
	{
		takenForks(fil);
		fil->toLive = get_time() + fil->param->timeToDie;
		message(fil, GRN"is eating"RESET, 0);
		if (fil->param->timeToDie < 420 )
			ft_usleep(fil->param->timeToEatt);
		else
			usleep(fil->param->timeToEatt * 1000);
		fil->countOfEat++;
		puttingForks(fil);
		message(fil, "is sleeping", 0);
		ft_usleep(fil->param->timeToSleep);
		message(fil, "is thinking", 0);
	}
	return (NULL);
}

int	main(int ac, char **av)
{
	t_fil		fil[200];
	t_param		param;
	t_check		check;
	pthread_t	th[202];
	int			i;

	if (parser(&param, &check, av, ac) == 1)
	{
		printf(RED"Error: incorrect arguments\n"RESET);
		return (1);
	}
	initFils(fil, &check, &param);
	pthread_create(&th[201], NULL, monitoring, (void *)fil);
	i = -1;
	while (++i < param.numOfFil)
		pthread_create(&th[i], NULL, func, (void *) &fil[i]);
	i = -1;
	while (++i < param.numOfFil)
		pthread_detach(th[i]);
	i = -1;
	while (++i < param.numOfFil)
		pthread_mutex_destroy(&fil->param->forks[i]);
	pthread_join(th[201], (void *) NULL);
	return (0);
}
