#include "main.h"

/**
 * get_width - width is calculatd to print
 * @format: string-format to print the ars.
 * @x: print args-list to be 
 * @list: args-list.
 *
 * Return: width.
 */
int get_width(const char *format, int *x, va_list list)
{
	int curr_i;
	int width = 0;

	for (curr_i = *x + 1; format[curr_i] != '\0'; curr_i++)
	{
		if (is_digit(format[curr_i]))
		{
			width *= 10;
			width += format[curr_i] - '0';
		}
		else if (format[curr_i] == '*')
		{
			curr_i++;
			width = va_arg(list, int);
			break;
		}
		else
			break;
	}

	*x = curr_i - 1;

	return (width);
}
