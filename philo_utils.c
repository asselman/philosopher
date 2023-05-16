/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aasselma <aasselma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/03 06:45:39 by aasselma          #+#    #+#             */
/*   Updated: 2023/05/15 10:18:10 by aasselma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include    "philo.h"

int	ft_atoi(char *s)
{
	int	r;
	int	sign;
	int	i;

	r = 0;
	sign = 1;
	i = 0;
	while ((s[i] >= 9 && s[i] <= 13) || s[i] == 32)
		i++;
	if (s[i] == '-' || s[i] == '+')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (s[i] >= '0' && s[i] <= '9')
		r = r * 10 + s[i++] - '0';
	return (r * sign);
}

long	t_now()
{
	struct timeval	tv;
    long			befor;

    gettimeofday(&tv, NULL);
	befor = ((tv.tv_sec) * 1000 + (tv.tv_usec) / 1000);
	return (befor);
}

int	ft_printf(char *str, t_philo *philo)
{
	long	tm;

	tm = philo->data->tm;
	pthread_mutex_lock(philo->data->lock_death);
	if (philo->data->dead == 0)
	{
		printf("%ld %d %s", t_now() - tm ,philo->id + 1, str);
		pthread_mutex_unlock(philo->data->lock_death);
	}
	else
	{
		pthread_mutex_unlock(philo->data->lock_death);
		return (1);
	}
	return (0);
}
