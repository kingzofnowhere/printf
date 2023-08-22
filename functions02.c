#include "main.h"

/**
 * p_char - Print a character.
 * @my_args: va_list containing the character to print.
 * @char_printed: Pointer to the count of characters printed.
 */

void p_char(va_list my_args, int *char_printed)
{
	char c = va_arg(my_args, int);
	write(1, &c, 1);
	(*char_printed)++;
}


/**
 * p_string - Print a string.
 * @my_args: va_list containing the string to print.
 * @char_printed: Pointer to the count of characters printed.
 */

void p_string(va_list my_args, int *char_printed)
{
	char *str = va_arg(my_args, char *);
	int len = 0;

	while (str[len])
	{
		write(1, &str[len], 1);
		len++;
		(*char_printed)++;
	}
}


/**
 * p_integer - Print an integer.
 * @my_args: va_list containing the integer to print.
 * @char_printed: Pointer to the count of characters printed.
 */

void p_integer(va_list my_args, int *char_printed)
{
	int num = va_arg(my_args, int);
	int divisor = 1;
	int digit;

	if (num < 0)
	{
		write(1, "-", 1);
		(*char_printed)++;
		num = -num;
	}

	while (num / divisor > 9)
		divisor *= 10;

	while (divisor != 0)
	{
		digit = num / divisor;
		write(1, &"0123456789"[digit], 1);
		(*char_printed)++;
		num %= divisor;
		divisor /= 10;
	}
}


/**
 * p_binary - Print unsigned integer in binary format.
 * @my_args: va_list that containing the unsigned integer.
 * @char_printed: Pointer to the count of characters printed.
 */

void p_binary(va_list my_args, int *char_printed)
{
	unsigned int num = va_arg(my_args, unsigned int);
	unsigned int mask = 1 << (sizeof(unsigned int) * 8 - 1);
	int flag = 0;

	while (mask)
	{
		if (num & mask)
		{
			write(1, "1", 1);
			(*char_printed)++;
			flag = 1;
		}
		else if (flag)
		{
			write(1, "0", 1);
			(*char_printed)++;
		}
		mask >>= 1;
	}
}


/**
 * _printf - Produces output according to a format.
 * @format: Character string containing directives.
 *
 * Return: Number of characters printed.
 */

int _printf(const char *format, ...)
{
	va_list my_args;
	int char_printed = 0;

	va_start(my_args, format);

	while (*format)
	{
		if (*format == '%')
		{
			format++;

			if (*format == 'c')
				p_char(my_args, &char_printed);
			else if (*format == 's')
				p_string(my_args, &char_printed);
			else if (*format == 'd' || *format == 'i')
				p_integer(my_args, &char_printed);
			else if (*format == 'b')
				p_binary(my_args, &char_printed);
		}
		else
		{
			write(1, format, 1);
			char_printed++;
		}

		format++;
	}

	va_end(my_args);

	return (char_printed);
}
