/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 06:24:51 by wait-bab          #+#    #+#             */
/*   Updated: 2024/07/05 09:14:32 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_info *info, t_philos *ph)
{
	if (ph->l_fork == ph->r_fork)
	{
		pthread_mutex_lock(ph->l_fork);
		printer(info, ph, "has taken a fork");
		info->should_exit = true;
		pthread_mutex_unlock(ph->l_fork);
		return (1);
	}
	return (0);
}

void	eating__(t_philos *ph, t_info *info)
{
	if (if_dead(info, ph) == 1 || one_philo(info, ph) == 1)
		return ;
	pthread_mutex_lock(ph->l_fork);
	printer(info, ph, "has taken a fork");
	pthread_mutex_lock(ph->r_fork);
	printer(info, ph, "has taken a fork");
	printer(info, ph, "is eating");
	pthread_mutex_lock(&ph->time_mutix);
	ph->ls_meal = get_time();
	pthread_mutex_unlock(&ph->time_mutix);
	sleeping(info->t_eat);
	pthread_mutex_lock(&ph->m_eat);
	ph->num_meals += 1;
	pthread_mutex_unlock(&ph->m_eat);
	pthread_mutex_unlock(ph->l_fork);
	pthread_mutex_unlock(ph->r_fork);
}

int	ft_itol(char *num)
{
	int	i;
	int	nega;
	int	rlt;

	i = 0;
	nega = 1;
	rlt = 0;
	while ((num[i] >= 9 && num[i] <= 13) || num[i] == 32)
		i++;
	if (num[i] == '+' || num[i] == '-')
	{
		if (num[i] == '-')
			return (-1);
		i++;
	}
	while (num[i] >= 48 && num[i] <= 57)
	{
		rlt = rlt * 10 + (num[i] - 48);
		i++;
	}
	if (num[i] != '\0')
		return (-1);
	return (rlt * nega);
}
