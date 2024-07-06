/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 06:25:50 by wait-bab          #+#    #+#             */
/*   Updated: 2024/07/06 03:32:38 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_resources(t_info *info)
{
	int	i;

	i = -1;
	while (++i < info->num_philos)
	{
		pthread_mutex_destroy(&info->forks[i]);
		pthread_mutex_destroy(&info->thread[i].m_eat);
		pthread_mutex_destroy(&info->thread[i].time_mutix);
	}
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->is_die_mutex);
	free(info->forks);
	free(info->thread);
	free(info);
}

long long	get_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		return (printf("ERROR TIME FUNCTION"));
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}

static int	check_2(t_info *info, t_philos *ph)
{
	pthread_mutex_lock(&ph->m_eat);
	pthread_mutex_lock(&ph->time_mutix);
	pthread_mutex_lock(&info->is_die_mutex);
	if ((get_time() - ph->ls_meal) >= info->t_die)
	{
		info->die_id = ph->id;
		info->should_exit = true;
		pthread_mutex_unlock(&info->is_die_mutex);
		pthread_mutex_unlock(&ph->time_mutix);
		pthread_mutex_unlock(&ph->m_eat);
		return (1);
	}
	return (0);
}

int	check_(t_info *info, t_philos *ph)
{
	int	i;
	int	min;

	while (1)
	{
		min = INT_MAX;
		i = -1;
		while (++i < info->num_philos)
		{
			if (check_2(info, &ph[i]) == 1)
				return (1);
			if (info->limit_meal != -1 && ph[i].num_meals < min)
				min = ph[i].num_meals;
			pthread_mutex_unlock(&info->is_die_mutex);
			pthread_mutex_unlock(&ph[i].time_mutix);
			pthread_mutex_unlock(&ph[i].m_eat);
		}
		if (info->limit_meal != -1 && info->limit_meal <= min)
		{
			info->should_exit = true;
			return (2);
		}
		usleep(500);
	}
	return (0);
}
