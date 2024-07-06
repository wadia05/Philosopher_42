/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 06:25:25 by wait-bab          #+#    #+#             */
/*   Updated: 2024/07/06 03:17:18 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *args)
{
	t_philos	*ph;
	t_info		*info;

	ph = (t_philos *)args;
	info = (t_info *)ph->info;
	if (ph->id % 2 != 0 && info->num_philos != 1)
		sleeping__(ph, info);
	while (1)
	{
		if (if_dead(info, ph) == 1)
			break ;
		thinking__(ph, info);
		eating__(ph, info);
		sleeping__(ph, info);
	}
	return (NULL);
}

int	init_philos(t_info *info, t_philos *ph)
{
	int	i;

	i = -1;
	info->stat_simi = get_time();
	while (++i < info->num_philos)
	{
		ph[i].id = i + 1;
		ph[i].l_fork = &info->forks[i];
		ph[i].r_fork = &info->forks[(i + 1) % info->num_philos];
		ph[i].info = info;
		ph[i].ls_meal = get_time();
		ph[i].num_meals = 0;
		pthread_mutex_init(&ph[i].m_eat, NULL);
		pthread_mutex_init(&ph[i].time_mutix, NULL);
		pthread_create(&ph[i].philo, NULL, routine, &ph[i]);
	}
	return (0);
}

int	allocation(char **args)
{
	t_info		*info;
	t_philos	*ph;

	info = malloc(sizeof(t_info));
	if (info == NULL)
		return (-1);
	ph = malloc(sizeof(t_philos) * atof(args[1]));
	if (ph == NULL)
		return (free(info), -1);
	info->forks = malloc(atof(args[1]) * sizeof(pthread_mutex_t));
	if (info->forks == NULL)
		return (free(info), free(ph), -1);
	info->thread = ph;
	ph->info = info;
	if (st_similation(info, ph, args) == 1)
		return (1);
	return (0);
}

int	check_input(int ac, char **av)
{
	if (ac < 5 || ac > 6)
		return (printf(B "ERROR INPUT" NC));
	if (ft_itol(av[1]) < 0 || 200 < ft_itol(av[1]))
		return (printf(B "ERROR INPUT" NC));
	if (ft_itol(av[2]) < 60)
		return (printf(B "ERROR INPUT" NC));
	if (ft_itol(av[3]) < 60)
		return (printf(B "ERROR INPUT" NC));
	if (ft_itol(av[4]) < 60)
		return (printf(B "ERROR INPUT" NC));
	if (ac == 6 && ft_itol(av[5]) <= 0)
		return (printf(B "ERROR INPUT" NC));
	return (0);
}

int	main(int argc, char **argv)
{
	if (check_input(argc, argv) != 0)
		return (1);
	if (allocation(argv) != 0)
		return (1);
	return (0);
}
