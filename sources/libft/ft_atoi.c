#include "libft.h"

int				ft_atoi(const char *nptr)
{
	long int	num;
	int			minus;

	while ((*nptr == ' ') || (*nptr == '\t') || (*nptr == '\n') ||\
			(*nptr == '\v') || (*nptr == '\r') || (*nptr == '\f'))
		nptr++;
	minus = 1;
	if (*nptr == '-' || *nptr == '+')
	{
		if (*nptr == '-')
			minus = -1;
		nptr++;
	}
	num = 0;
	while ('0' <= *nptr && *nptr <= '9')
	{
		if (num > (INT_MAX - (*nptr - '0')) / 10)
			return (-1);
		num = num * 10 + (*nptr - '0');
		nptr++;
	}
	return (num * minus);
}
