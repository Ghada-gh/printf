#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include "main.h"
#include <stdint.h>
#include <inttypes.h>

#define BUFFER_SIZE 1024

int power(int base, int exponent);

/**
 * _printf - Custom printf function that handles a group of conversion specifiers.
 * @format: Format string
 * Return: Number of characters printed (excluding the null byte)
 */
int _printf(const char *format, ...)
{
  va_list args;
  char buffer[BUFFER_SIZE];
  int i = 0, j = 0, count = 0;
  int k ;
  
  va_start(args, format);

  while (format && format[i])
    {
      if (format[i] != '%')
	{
	  buffer[j++] = format[i++];
	  if (j == BUFFER_SIZE)
	    {
	      write(1, buffer, j);
	      count += j;
	      j = 0;
	    }
	}
      else
	{
	  i++;
	  if (format[i] == '\0')
	    break;

	  switch (format[i])
	    {
	      /* %c: Print a character */
	    case 'c':
	      buffer[j++] = va_arg(args, int);
	      break;
	      
	      /* %s: Print a string */
	    case 's':
	      {
		char *str = va_arg(args, char *);
		if (str == NULL)
		  str = "(null)";
		while (str && str[j])
		  buffer[j] = str[j];
		j++;
	      }
	      break;
	      
	      /* %%: Print a '%' character */
	    case '%':
	      buffer[j++] = '%';
	      break;

	      /* %d, %i: Print an integer as decimal */
	    case 'd':
	    case 'i':
	      {
		int num = va_arg(args, int);
		int num_copy = num;
		int digits = 0;
		
		if (num < 0)
		  {
		    buffer[j++] = '-';
		    num_copy = -num_copy;
		  }
		
		/* Count the number of digits in the integer */
		do {
		  digits++;
		  num_copy /= 10;
		} while (num_copy);
		
		/* Convert and store the digits in reverse order */
		while (digits > 0)
		  {
		    buffer[j++] = (num / power(10, digits - 1)) + '0';
		    num %= power(10, digits - 1);
		    digits--;
		  }
	      }
	      break;
	      
	      /* %b: Print an unsigned int as binary */
	    case 'b':
	      {
		unsigned int num = va_arg(args, unsigned int);
		int bits = 0;
		unsigned int num_copy = num;
		
		if (num == 0)
		  buffer[j++] = '0';
		else
		  {
		    /* Count the number of bits in the integer */
		    do {
		      bits++;
		      num_copy >>= 1;
		    } while (num_copy);
		    
		    /* Convert and store the bits in reverse order */
		    while (bits > 0)
		      {
			buffer[j++] = ((num >> (bits - 1)) & 1) + '0';
			bits--;
		      }
		  }
	      }
	      break;
	      
	      /* %u: Print an unsigned integer as decimal */
	    case 'u':
	      {
		unsigned int num = va_arg(args, unsigned int);
		int digits = 0;
		unsigned int num_copy = num;
		
		/* Count the number of digits in the integer */
		do {
		  digits++;
		  num_copy /= 10;
		}
		while (num_copy);
		
		/* Convert and store the digits in reverse order */
		while (digits > 0)
		  {
		    buffer[j++] = (num / power(10, digits - 1)) + '0';
		    num %= power(10, digits - 1);
		    digits--;
		  }
	      }
	      break;
	      
	      /* %o: Print an unsigned integer as octal */
	    case 'o':
	      {
		unsigned int num = va_arg(args, unsigned int);
		int octal_digits = 0;
		unsigned int num_copy = num;
		
		/* Count the number of octal digits in the integer */
		do
		  {
		    octal_digits++;
		    num_copy /= 8;
		  }
		while (num_copy);
		
		/* Convert and store the octal digits in reverse order */
		while (octal_digits > 0)
		  {
		    buffer[j++] = (num / power(8, octal_digits - 1)) + '0';
		    num %= power(8, octal_digits - 1);
		    octal_digits--;
		  }
	      }
	      break;
	      
	      /* %x: Print an unsigned integer as hexadecimal (lowercase) */
	    case 'x':
	      {
		unsigned int num = va_arg(args, unsigned int);
		int hex_digits = 0;
		unsigned int num_copy = num;
		
		/* Count the number of hexadecimal digits in the integer */
		do
		  {
		    hex_digits++;
		    num_copy /= 16;
		  }
		while (num_copy);
		
		/* Convert and store the hexadecimal digits in reverse order */
		while (hex_digits > 0)
		  {
		    int remainder = num % 16;
		    buffer[j++] = (remainder < 10) ? remainder + '0' : remainder - 10 + 'a';
		    num /= 16;
		    hex_digits--;
		  }
	      }
	      break;
	      
	      /* %X: Print an unsigned integer as hexadecimal (uppercase) */
	    case 'X':
	      {
		unsigned int num = va_arg(args, unsigned int);
		int hex_digits = 0;
		unsigned int num_copy = num;
		
		/* Count the number of hexadecimal digits in the integer */
		do
		  {
		    hex_digits++;
		    num_copy /= 16;
		  }
		while (num_copy);
		
		/* Convert and store the hexadecimal digits in reverse order */
		while (hex_digits > 0)
		  {
		    int remainder = num % 16;
		    buffer[j++] = (remainder < 10) ? remainder + '0' : remainder - 10 + 'A';
		    num /= 16;
		    hex_digits--;
		  }
	      }
	      break;

	      /* %S: Print a string, with non-printable characters as '\x' notation */
	    case 'S':
	      {
		char *str = va_arg(args, char *);
		if (str == NULL)
		  str = "(null)";
		while (str && str[j])
		  {
		    if (str[j] < 32 || str[j] >= 127)
		      {
			buffer[j++] = '\\';
			buffer[j++] = 'x';
			buffer[j] = (str[j] / 16) + '0';
			j++;
			buffer[j] = (str[j] % 16) + '0';
			j++;
		      }
		    else
		      buffer[j] = str[j];
		    j++;
		  }
	      }
	      break;
	      
	      /* %p: Print a pointer address in hexadecimal */
	    case 'p':
	      {
		void *ptr = va_arg(args, void *);
		unsigned long int address = (unsigned long int)ptr;
		buffer[j++] = '0';
		buffer[j++] = 'x';
		for (k = 15; k >= 0; k--)
		  {
		    unsigned long int mask = 15UL << (k * 4);
		    int digit = (address & mask) >> (k * 4);
		    buffer[j++] = (digit < 10) ? digit + '0' : digit - 10 + 'a';
		  }
	      }
	      break;
	      
	      /* %r: Print a string in reverse */
	    case 'r':
	      {
		char *str = va_arg(args, char *);
		int str_len = 0;
		if (str == NULL)
		  str = "(null)";
		while (str && str[str_len])
		  str_len++;
		
		for (k = str_len - 1; k >= 0; k--)
		  buffer[j++] = str[k];
	      }
	      break;
	      
	      /* %R: Print a string in ROT13 encoding */
	    case 'R':
	      {
		char *str = va_arg(args, char *);
		if (str == NULL)
		  str = "(null)";
		while (str && str[j])
		  {
		    char c = str[j];
		    if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		      {
			char base = (c >= 'A' && c <= 'Z') ? 'A' : 'a';
			buffer[j] = (c - base + 13) % 26 + base;
		      }
		    else
		      buffer[j] = c;
		    j++;
		  }
	      }
	      break;
	      
	      /* Add support for other conversion specifiers as needed */
				default:
				  break;
	    }
	  i++;
	}
      
      if (j == BUFFER_SIZE || format[i] == '\0')
	{
	  write(1, buffer, j);
	  count += j;
	  j = 0;
	}
    }
  
  va_end(args);
  
  return count;
}

/**
 * power - Calculate the power of a number
 * @base: Base number
 * @exponent: Exponent
 * Return: Result of base raised to the exponent
 */
int power(int base, int exponent)
{
  int result = 1;
  while (exponent > 0)
    {
      result *= base;
      exponent--;
    }
  return result;
}
