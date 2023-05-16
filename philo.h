/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 23:43:56 by aasselma          #+#    #+#             */
/*   Updated: 2023/05/15 11:58:51 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		PHILO_H
# define	PHILO_H

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>

typedef struct data
{
	int				dead;
	int				done;
	int				ph_num;
	int				times_eat;
	long			die_time;
	long			eat_time;
	long			sleep_time;
	long			tm;
	pthread_mutex_t	*lock_death;
	pthread_mutex_t	*counter;
}	t_data;

typedef struct philo
{
	int				id;
	int				num_ot_eat;
	int				permission;
	long			last_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*lock_last;
	t_data			*data;
	pthread_t	philo;
}	t_philo;

int		ft_printf(char *str, t_philo *philo);
int		ft_routin(t_philo *philo);
void	check_death(t_philo *thread);
int		ft_atoi(char *s);
long	t_now();

#endif