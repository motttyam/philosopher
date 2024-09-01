/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prac_thread.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:45:29 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/31 15:44:55 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prac.h"

pthread_mutex_t mu_1;
static int num = 0;

void *th_func(void *arg)
{
    pthread_mutex_lock(&mu_1);
    puts("thread1 crated");
    for (int i = 0; i < 5; i++)
    {
        printf("num:%d\n", ++num);
    }
    puts("thread1 was over");
    pthread_mutex_unlock(&mu_1);
    return (NULL);
}

void *th_func2(void *arg)
{
    pthread_mutex_lock(&mu_1);
    puts("thread2 crated");
    for (int i = 0; i < 5; i++)
    {
        printf("num:%d\n", ++num);
    }
    puts("thread2 was over");
    pthread_mutex_unlock(&mu_1);
    return (NULL);
}

// int main(void)
// {
//     pthread_t th1;
//     pthread_t th2;

//     pthread_mutex_init(&mu_1, NULL);
//     if (pthread_create(&th1, NULL, th_func, NULL) == 0)
//     {
//         pthread_join(th1, NULL);
//     }
//     if (pthread_create(&th2, NULL, th_func2, NULL) == 0)
//     {
//         pthread_join(th1, NULL);
//     }
//     return (0);
// }
