/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 06:25:17 by wait-bab          #+#    #+#             */
/*   Updated: 2024/07/06 02:53:31 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialization(t_info *info, t_philos *ph, char **av)
{
	int	i;

	i = -1;
	info->num_philos = ft_itol(av[1]);
	info->t_die = ft_itol(av[2]);
	info->t_eat = ft_itol(av[3]);
	info->t_sleep = ft_itol(av[4]);
	info->limit_meal = -1;
	if (av[5] != NULL)
		info->limit_meal = ft_itol(av[5]);
	info->should_exit = false;
	info->die_id = -1;
	while (++i < info->num_philos)
		pthread_mutex_init(&info->forks[i], NULL);
	pthread_mutex_init(&info->print, NULL);
	pthread_mutex_init(&info->is_die_mutex, NULL);
	init_philos(info, ph);
	return (0);
}

int	st_similation(t_info *info, t_philos *ph, char **args)
{
	int	i;

	i = -1;
	initialization(info, ph, args);
	if (check_(info, ph) == 1)
		printf("%lld %d %s\n", get_time() - info->stat_simi, info->die_id,
			R "died" NC);
	pthread_mutex_lock(&info->is_die_mutex);
	info->should_exit = true;
	pthread_mutex_unlock(&info->is_die_mutex);
	while (++i < info->num_philos)
		pthread_join(info->thread[i].philo, NULL);
	free_resources(info);
	return (1);
}
