#include "main.h"

/**
 * is_printable - check if char is able to be printed
 * @k: evalute Character
 *
 * Return: 1 if k is printable, 0 otherwise
 */
int is_printable(char k)
{
	if (k >= 32 && k < 127)
		return (1);

	return (0);
}

/**
 * append_hexa_code - ascci-appended in hexa code to be buffered
 * @buffer: character of array
 * @k: Index where to start appending.
 * @ascii_code: ASSCI CODE
 * Return: Always 3
 */
int append_hexa_code(char ascii_code, char buffer[], int k)
{
	char map_to[] = "0123456789ABCDEF";
	/* The hexa format code is always 2 digits long */
	if (ascii_code < 0)
		ascii_code *= -1;

	buffer[k++] = '\\';
	buffer[k++] = 'x';

	buffer[k++] = map_to[ascii_code / 16];
	buffer[k] = map_to[ascii_code % 16];

	return (3);
}

/**
 * is_digit - check if character is digit
 * @y: evaluate Character
 *
 * Return: 1 if y is a digit, 0 otherwise
 */
int is_digit(char y)
{
	if (y >= '0' && y <= '9')
		return (1);

	return (0);
}

/**
 * convert_size_number - Cast number to determined size
 * @numb: Number to cast
 * @size: Number indicates to type to b cast
 *
 * Return: Cast value of num
 */
long int convert_size_number(long int numb, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((short)num);

	return ((int)num);
}

/**
 * convert_size_unsgnd - Cnumber-cast to size
 * @num: Number to cast
 * @size: Number indicates type to cast
 *
 * Return: Casted value of num
 */
long int convert_size_unsgnd(unsigned long int num, int size)
{
	if (size == S_LONG)
		return (num);
	else if (size == S_SHORT)
		return ((unsigned short)num);

	return ((unsigned int)num);
}

