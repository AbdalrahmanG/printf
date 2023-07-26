#include "main.h"

/**-------------------- PRINT CHAR ------------------**/

/**
 * print_char - for printing chars
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculateing the active flags
 * @width: the width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_char(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char i = va_arg(types, int);

	return (handle_write_char(i, buffer, flags, width, precision, size));
}

/**-------------------- PRINT A STRING ----------------------**/

/**
 * print_string - for Printing string
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculating the active flags
 * @width: width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, j;
	char *str = va_arg(types, char *);

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
	{
		str = "(null)";
		if (precision >= 6)
			str = "      ";
	}
	while (str[length] != '\0')
		length++;
	if (precision >= 0 && precision < length)
		length = precision;
	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (j = width - length; j > 0; j--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/**------------------ PRINT PERCENT SIGN --------------------**/

/**
 * print_percent - for printing the percent
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculateing the active flags
 * @width: the width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);
	return (write(1, "%%", 1));
}

/**--------------------- PRINT INT -----------------------**/
/**
 * print_int - for printing the int
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculateing the active flags
 * @width: the width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int a = BUFF_SIZE - 2;
	int is_negative = 0;
	long int l = va_arg(types, long int);
	unsigned long int num;

	l = convert_size_number(l, size);

	if (l == 0)
		buffer[a--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)l;

	if (l < 0)
	{
		num = (unsigned long int)((-1) * l);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[a--] = (num % 10) + '0';
		num /= 10;
	}

	a++;

	return (write_number(is_negative, a, buffer, flags, width, precision, size));
}

/**---------------------- PRINT BINARY ---------------------**/

/**
 * print_binary - for Printing the unsigned number
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculateing the active flags
 * @width: the width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, j, l, sum;
	unsigned int a[32];
	int count;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	x = va_arg(types, unsigned int);
	j = 2147483648; /* (2 ^ 31) */
	a[0] = x / j;
	for (l = 1; l < 32; l++)
	{
		j /= 2;
		a[l] = (x / j) % 2;
	}
	for (l = 0, sum = 0, count = 0; l < 32; l++)
	{
		sum += a[l];
		if (sum || l == 31)
		{
			char z = '0' + a[l];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}

