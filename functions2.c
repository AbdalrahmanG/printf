#include "main.h"

/**----------------- PRINT POINTER ------------------**/

/**
 * print_pointer - Prints the value of a pointer variable
 *
 * @types: arguments list
 * @buffer: array of buffer
 * @flags: for calculating the active flags
 * @width: the width
 * @precision: specification Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_c = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1;

	/* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(width);
	UNUSED(size);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_c = '+', length++;
	else if (flags & F_SPACE)
		extra_c = ' ', length++;

	ind++;

	/*return (write(1, &buffer[i], BUFF_SIZE - i - 1));*/
	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_c, padd_start));
}

/**------------------- PRINT NON PRINTABLE --------------------**/

/**
 * print_non_printable - for printing ascii codes in hexa of
 * non-printable chars
 *
 * @types: arguments list
 * @buffer: array of buffer
 * @flags: for calculating the active flags
 * @width: the width
 * @precision: specification Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[j] != '\0')
	{
		if (is_printable(str[j]))
			buffer[j + offset] = str[j];
		else
			offset += append_hexa_code(str[j], buffer, j + offset);

		j++;
	}

	buffer[j + offset] = '\0';

	return (write(1, buffer, j + offset));
}

/**---------------------- PRINT REVERSE -----------------------**/

/**
 * print_reverse - for printing the reversed string.
 *
 * @types: arguments list
 * @buffer: array of buffer
 * @flags: for calculating the active flags
 * @width: the width
 * @precision: specification Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int j, count = 0;

	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(size);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (j = 0; str[j]; j++)
		;

	for (j = j - 1; j >= 0; j--)
	{
		char z = str[j];

		write(1, &z, 1);
		count++;
	}
	return (count);
}

/**------------------ PRINT A STRING IN ROT13 -----------------------**/

/**
 * print_rot13string - for printing the string in rot13.
 *
 * @types: arguments list
 * @buffer: array of buffer
 * @flags: for calculating the active flags
 * @width: the width
 * @precision: specification Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char c;
	char *str;
	unsigned int a, i;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	UNUSED(precision);
	UNUSED(size);

	if (str == NULL)
		str = "(AHYY)";
	for (a = 0; str[a]; a++)
	{
		for (i = 0; in[i]; i++)
		{
			if (in[i] == str[a])
			{
				c = out[i];
				write(1, &c, 1);
				count++;
				break;
			}
		}
		if (!in[i])
		{
			c = str[a];
			write(1, &c, 1);
			count++;
		}
	}
	return (count);
}
