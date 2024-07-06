/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wait-bab <wait-bab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 06:25:44 by wait-bab          #+#    #+#             */
/*   Updated: 2024/07/06 03:38:03 by wait-bab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

// Define color codes
# define B "\033[0;34m" // Blue
# define R "\033[1;31m" // Red
# define NC "\033[0m"   // No color (reset)

typedef struct s_info	t_info;

typedef struct s_philos
{
	int					id;
	long long			ls_meal;

	pthread_mutex_t		*l_fork;
	pthread_mutex_t		*r_fork;
	long				num_meals;
	pthread_t			philo;
	t_info				*info;
	pthread_mutex_t		m_eat;
	pthread_mutex_t		time_mutix;

}						t_philos;

typedef struct s_info
{
	t_philos			*thread;
	int					num_philos;
	int					t_eat;
	int					t_die;
	int					t_sleep;
	long				limit_meal;

	long long			stat_simi;

	bool				should_exit;
	int					die_id;

	pthread_mutex_t		*forks;
	pthread_mutex_t		print;
	pthread_mutex_t		is_die_mutex;

}						t_info;
//input check
int						ft_itol(char *num);
int						check_input(int ac, char **av);
//similation
int						allocation(char **args);
int						st_similation(t_info *info, t_philos *ph, char **args);
int						init_philos(t_info *info, t_philos *ph);
// action
int						sleeping(size_t milliseconds);
void					printer(t_info *info, t_philos *ph, char *msg);
int						if_dead(t_info *info, t_philos *ph);
void					sleeping__(t_philos *ph, t_info *info);
void					thinking__(t_philos *ph, t_info *info);
int						one_philo(t_info *info, t_philos *ph);
void					eating__(t_philos *ph, t_info *info);
// monitoring
int						check_(t_info *info, t_philos *ph);
// time
long long				get_time(void);
// free
void					free_resources(t_info *info);
#endif