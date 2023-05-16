/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/09 11:15:00 by aasselma          #+#    #+#             */
/*   Updated: 2023/05/15 13:17:55 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_routin(t_philo *philo)
{
	int		right_id;
	int		checker;
	
	right_id = philo->id + 1;
	if (philo->id + 1 == philo->data->ph_num)
		right_id = 0;
	checker = ft_printf("is thinking\n", philo);
	pthread_mutex_lock(&philo->forks[philo->id]);
	checker = ft_printf("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->forks[philo->id]);
	pthread_mutex_lock(&philo->forks[right_id]);
	checker = ft_printf("has taken a fork\n", philo);
	pthread_mutex_unlock(&philo->forks[right_id]);
	checker = ft_printf("is eating\n", philo);
	pthread_mutex_lock(philo->data->counter);
	philo->num_ot_eat--;
	pthread_mutex_unlock(philo->data->counter);
	pthread_mutex_lock(philo->lock_last);
	philo->last_eat = t_now();
	pthread_mutex_unlock(philo->lock_last);
	usleep(philo->data->eat_time * 1000);
	checker = ft_printf("is sleeping\n", philo);
	usleep(philo->data->sleep_time * 1000);
	return (checker);
}

void	check_death(t_philo *thread)
{
	int	i;

	i = 0;
	while(1)
	{
		// lock mutex 
		if (thread[i].data->done == thread[i].data->ph_num)
			return	*(NULL);
		// unlock mutex
		pthread_mutex_lock(thread[i].lock_last);
		if ((t_now() - thread[i].last_eat) >= thread[i].data->die_time)
		{
			pthread_mutex_unlock(thread[i].lock_last);
			pthread_mutex_lock(thread[i].data->lock_death);
			thread[i].data->dead = 1;
			pthread_mutex_unlock(thread[i].data->lock_death);
			printf("%ld %d died\n",  t_now() - thread[i].data->tm , thread[i].id + 1);
			return	*(NULL);
		}
		pthread_mutex_unlock(thread[i].lock_last);
		if (i == thread[i].data->ph_num - 1)
			i = 0;
		i++;
	}
}