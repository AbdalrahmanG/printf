#include "main.h"

/**------------------- PRINT UNSIGNED NUMBER -----------------------**/

/**
 * print_unsigned - for printing the unsigned number
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculating active flags
 * @width: the width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_unsigned(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = (num % 10) + '0';
		num /= 10;
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/**----------------- PRINT UNSIGNED NUMBER IN OCTAL ---------------**/

/**
 * print_octal - for printing the unsigned num. in octal notation
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculating active flags
 * @width: the width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[j--] = '0';

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}

/**--------------PRINT UNSIGNED NUMBER IN HEXADECIMAL --------------**/

/**
 * print_hexadecimal - for printing the unsigned num. in hexadecimal notation
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculating active flags
 * @width: the width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/**----------- PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL ------------**/

/**
 * print_hexa_upper - for printing unsigned number in hexadecimal notation
 *
 * @types: arguments list
 * @buffer: array buffer
 * @flags: for calculating active flags
 * @width: the width
 * @precision: Precision
 * @size: the size of specifier
 *
 * Return: number of char
 */

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/**-------------- PRINT HEXX NUM IN LOWER OR UPPER ------------------**/

/**
 * print_hexa - for printing the hexadecimal number in lower or upper
 *
 * @types: arguments list
 * @map_to: values array to map the number
 * @buffer: array buffer
 * @flags: for calculating active flags
 * @flag_ch: for calculating active flags
 * @width: the width
 * @precision: Precision
 * @size: specifier size
 * @size: specification size
 *
 * Return: number of char
 */

int print_hexa(va_list types, char map_to[], char buffer[],
	int flags, char flag_ch, int width, int precision, int size)
{
	int j = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[j--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[j--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[j--] = flag_ch;
		buffer[j--] = '0';
	}

	j++;

	return (write_unsgnd(0, j, buffer, flags, width, precision, size));
}
