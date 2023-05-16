/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/29 16:19:15 by aasselma          #+#    #+#             */
/*   Updated: 2023/05/15 13:24:43 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *ph_managment(void *th)
{
	t_philo			*philo;
	pthread_mutex_t *times_of_eat;

	philo = (t_philo *)th;
	times_of_eat = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(times_of_eat , NULL);
	philo->data->counter = times_of_eat;
	philo->num_ot_eat = philo->data->times_eat;
	while (1)
	{
		pthread_mutex_lock(philo->data->counter);
		if (philo->num_ot_eat != 0)
		{
			pthread_mutex_unlock(philo->data->counter);
			if ( ft_routin(philo) == 1)
				return (NULL);
		}
		else
		{
			pthread_mutex_unlock(philo->data->counter);
			// lock mutex
			philo->data->done++;
			// unlock mutex
			return	(NULL);
		}
	}
    return (NULL);
}

void	ft_contune(t_philo *thread, pthread_mutex_t *mutex, t_data *data)
{
	int				i;
	pthread_mutex_t	*last_eat_lock;

	i = 0;
	last_eat_lock = malloc(sizeof(pthread_mutex_t));
	while (i != data->ph_num)
		pthread_mutex_init(&(mutex[i++]), NULL);
	pthread_mutex_init(last_eat_lock , NULL);
	i = 0;
	while (i <= data->ph_num)
	{
		thread[i].id = i;
		thread[i].permission = 0;
		thread[i].num_ot_eat = 0;
		thread[i].forks = mutex;
		thread[i].lock_last = last_eat_lock;
		thread[i].data = data;
		pthread_create(&thread[i].philo , NULL, ph_managment, &thread[i]);
		usleep(10);
		i = i + 2;
	}
	i = 1;
	while (i <= data->ph_num)
	{
		thread[i].id = i;
		thread[i].permission = 0;
		thread[i].num_ot_eat = 0;
		thread[i].forks = mutex;
		thread[i].lock_last = last_eat_lock;
		thread[i].data = data;
		pthread_create(&thread[i].philo , NULL, ph_managment, &thread[i]);
		usleep(10);
		i = i + 2;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*thread;
	t_data			*data;
	pthread_mutex_t	*mutex;
	pthread_mutex_t	*death_lock;
	int				i;

	i = 0;
	if (argc == 6)
	{
		data = malloc(sizeof(t_data));
		death_lock = malloc(sizeof(pthread_mutex_t));
		pthread_mutex_init(death_lock , NULL);
		data->dead = 0;
		data->done = 0;
		data->lock_death = death_lock;
		data->ph_num = ft_atoi(argv[1]);
		data->die_time = ft_atoi(argv[2]);
		data->eat_time = ft_atoi(argv[3]);
		data->sleep_time = ft_atoi(argv[4]);
		data->times_eat = ft_atoi(argv[5]);
		data->tm = t_now();
		thread = malloc(data->ph_num * sizeof(t_philo));
		mutex = malloc(data->ph_num * sizeof(pthread_mutex_t));
		ft_contune(thread, mutex, data );
		check_death(thread);
		while (i != thread->data->ph_num)
		{
			pthread_join(thread[i].philo, NULL);
			i++;
		}
	}
	return (0);
}
