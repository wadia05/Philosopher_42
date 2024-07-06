/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 06:24:58 by wait-bab          #+#    #+#             */
/*   Updated: 2024/07/04 06:26:40 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	sleeping(size_t milliseconds)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < milliseconds)
		usleep(500);
	return (0);
}

int	if_dead(t_info *info, t_philos *ph)
{
	(void)ph;
	pthread_mutex_lock(&info->is_die_mutex);
	if (info->should_exit == true)
	{
		pthread_mutex_unlock(&info->is_die_mutex);
		return (1);
	}
	pthread_mutex_unlock(&info->is_die_mutex);
	return (0);
}

void	printer(t_info *info, t_philos *ph, char *msg)
{
	pthread_mutex_lock(&info->print);
	if (if_dead(info, ph) == 1)
	{
		pthread_mutex_unlock(&info->print);
		return ;
	}
	printf("%lld %d %s\n", get_time() - info->stat_simi, ph->id, msg);
	pthread_mutex_unlock(&info->print);
}

void	sleeping__(t_philos *ph, t_info *info)
{
	if (if_dead(info, ph) == 1)
		return ;
	printer(info, ph, "is sleeping");
	sleeping(info->t_sleep);
}

void	thinking__(t_philos *ph, t_info *info)
{
	if (if_dead(info, ph) == 1)
		return ;
	printer(info, ph, "is thinking");
}
