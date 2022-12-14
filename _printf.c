#include "main.h"

/**
 * check_specifiers - checks for valid format specifier
 * @format: format
 *
 * Return: pointer to valid function or NULL
 */
static int (*check_specifiers(const char *format))(va_list)
{
	unsigned int i;
	printer p[] = {
		{"c", print_c},
		{"s", print_s},
		{"i", print_i},
		{"d", print_d},
		{"u", print_u},
		{"b", print_b},
		{"o", print_o},
		{"x", print_x},
		{"X", print_X},
		{"p", print_p},
		{"S", print_S},
		{"r", print_r},
		{"R", print_R},
		{NULL, NULL}
	};

	for (i = 0; p[i].t != NULL; i++)
	{
		if (*(p[i].t) == *format)
		{
			break;
		}
	}
	return (p[i].f);
}

/**
 * _printf - prints all
 * @format: format of arguments to print
 *
 * Return: total number of printed characters
 */
int _printf(const char *format, ...)
{
	unsigned int i = 0, total = 0;
	va_list valist;
	int (*f)(va_list);

	if (format == NULL)
		return (-1);
	va_start(valist, format);
	while (format[i])
	{
		for (; format[i] != '%' && format[i]; i++)
		{
			_putchar(format[i]);
			total++;
		}
		if (!format[i])
			return (total);
		f = check_specifiers(&format[i + 1]);
		if (f != NULL)
		{
			total += f(valist);
			i += 2;
			continue;
		}
		if (!format[i + 1])
			return (-1);
		_putchar(format[i]);
		total++;
		if (format[i + 1] == '%')
			i += 2;
		else
			i++;
	}
	va_end(valist);
	return (total);
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int _putchar(char c)
{
	return (write(1, &c, 1));
}
