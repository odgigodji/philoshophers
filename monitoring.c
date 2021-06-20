/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: namerei <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/07 18:37:21 by namerei           #+#    #+#             */
/*   Updated: 2021/06/19 19:53:31 by namerei          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "phils.h"

void	message(t_fil *fil, const char *str, int flag)
{
	if (flag == 1)
	{
		pthread_mutex_lock(&fil->check->utils[0]);
		fil->check->philsAreAlive = 0;
		printf("%ld\t%d\t%s\n"RESET, (get_time() - fil->param->start),
			   fil->id, RED"dead");
		return ;
	}
	pthread_mutex_lock(&fil->check->utils[0]);
	if (fil->check->philsAreAlive)
	{
		printf("%ld\t%d\t%s\n"RESET, (get_time() - fil->param->start),
			   fil->id, str);
	}
	pthread_mutex_unlock(&fil->check->utils[0]);
}

int	fullnessCheck(t_fil *fil, const int i)
{
	static short int	fullnesCounter = 0;

	if (!fil[i].isFull && fil[i].countOfEat == fil[0].param->fullness)
	{
		fil[i].isFull = (short int)1;
		fullnesCounter++;
	}
	if (fullnesCounter == (short int)fil[0].param->numOfFil)
	{
		fil->check->philsAreAlive = 0;
		return (1);
	}
	return (0);
}

void	*monitoring(void *oneFil)
{
	t_fil	*fil;
	int		i;

	fil = (t_fil *)oneFil;
	while (fil->check->philsAreAlive)
	{
		i = -1;
		while (++i < fil[0].param->numOfFil)
		{
			pthread_mutex_lock(&fil->check->utils[i + 1]);
			if (!fil[i].nowIsEating && get_time() > fil[i].toLive)
			{
				message(fil, RED"dead", 1);
				break ;
			}
			pthread_mutex_unlock(&fil->check->utils[i + 1]);
			if (fil->param->fullness && (fullnessCheck(fil, i) == 1))
			{
				fil->check->philsAreAlive = 0;
				break ;
			}
		}
	}
	return (NULL);
}
