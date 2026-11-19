/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   atol.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugpolat@student.42istanbul.com.tr          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/08/17 06:06:44 by ugpolat           #+#    #+#             */
/*   Updated: 2026/11/19 19:02:34 by seraydin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	check_max_min(long result, const char a, int sign)
{
	long int	min;

	min = -2147483648;
	if ((result > ((2147483647) - (a - '0')) / 10) && sign == 1)
		return (0);
	if (result > (-min - (a - '0')) / 10 && sign == -1)
		return (0);
	return (1);
}

static int	is_space(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static void	handle_digit(const char **str, int *sign)
{
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
}

int	ft_atoi(const char *str)
{
	long	result;
	int		sign;
	int		has_digit;

	result = 0;
	sign = 1;
	has_digit = 0;
	while (is_space(*str))
		str++;
	if (!*str)
		return (-1);
	handle_digit(&str, &sign);
	while (*str >= '0' && *str <= '9')
	{
		if (!check_max_min(result, *str, sign))
			return (-1);
		result = result * 10 + (*str - '0');
		has_digit = 1;
		str++;
	}
	if (!has_digit || *str != '\0' || sign == -1)
		return (-1);
	return ((int)result);
}
