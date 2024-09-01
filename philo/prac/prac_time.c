/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prac_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ktsukamo <ktsukamo@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 15:44:58 by ktsukamo          #+#    #+#             */
/*   Updated: 2024/08/31 15:52:51 by ktsukamo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "prac.h"

static int show_now_date()
{
    struct timeval tv ={0};
    int rc;

    rc = gettimeofday(&tv, NULL);
    if (rc < 0)
    {
        printf("Error: gettimeofday() %s\n", strerror(errno));
        return (-1);
    }
    printf("Seconds since Epoch: %ld\n", tv.tv_sec);
    printf("Microseconds: %ld\n", tv.tv_usec);
    printf("%s\n", ctime(&tv.tv_sec));
    return (0);
}

int main (void)
{
    if (show_now_date() != 0)
        exit(EXIT_FAILURE);
    exit(EXIT_SUCCESS);
    return (0);
}