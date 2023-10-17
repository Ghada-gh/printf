#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include "main.h"
#include <stdint.h>
#include <inttypes.h>

#define BUFFER_SIZE 1024


int _printf(const char *format, ...);
int _puts(char *str);
int _putchar(char c);

/**
 * _printf - Custom printf function that handles a group of conversion specifiers.
 * @format: Format string
 * Return: Number of characters printed (excluding the null byte)
 */

int _putchar(char c)
{
  return write(1, &c, 1);
}

int _puts(char *str)
{
  int i;

  for (i = 0; str[i]; i++)
    {
      if (_putchar(str[i]) == -1)
	return -1;
    }
  return i;
}

int _printf(const char *format, ...)
{
  va_list args;
  int count = 0;
  char buffer[BUFFER_SIZE];
  int i = 0;
  int j ;

  va_start(args, format);

  while (format && format[i])
    {
      if (count >= BUFFER_SIZE - 1)
        {
	  buffer[count] = '\0';
	  _puts(buffer);
	  count = 0;
        }

      if (format[i] != '%')
        {
	  buffer[count] = format[i];
	  count++;
        }
      else
        {
	  i++;
	  if (format[i] == '\0')
	    return -1;
	  switch (format[i])
            {
            case 'c':
	      buffer[count] = va_arg(args, int);
	      count++;
	      break;
            case 's':
	      count += _puts(va_arg(args, char *));
	      break;
            case '%':
	      buffer[count] = '%';
	      count++;
	      break;
            case 'd':
            case 'i':
	      count += sprintf(buffer + count, "%d", va_arg(args, int));
	      break;
            case 'u':
	      count += sprintf(buffer + count, "%u", va_arg(args, unsigned int));
	      break;
            case 'o':
	      count += sprintf(buffer + count, "%o", va_arg(args, unsigned int));
	      break;
            case 'x':
	      count += sprintf(buffer + count, "%x", va_arg(args, unsigned int));
	      break;
            case 'X':
	      count += sprintf(buffer + count, "%X", va_arg(args, unsigned int));
	      break;
            case 'p':
	      count += sprintf(buffer + count, "%p", va_arg(args, void *));
	      break;
            case 'S':
            {
	      char *str = va_arg(args, char *);
	      buffer[count] = 'S';
	      count++;
	      buffer[count] = '[';
	      count++;
	      
	      for (j = 0; str[j]; j++)
                {
		  if (str[j] < 32 || str[j] >= 127)
                    {
		      count += sprintf(buffer + count, "\\x%02X", (unsigned char)str[j]);
                    }
		  else
                    {
		      buffer[count] = str[j];
		      count++;
                    }
                }
	      buffer[count] = ']';
	      count++;
	      break;
            }
            default:
	      buffer[count] = '%';
	      count++;
	      buffer[count] = format[i];
	      count++;
            }
        }
      i++;
    }
  va_end(args);
  buffer[count] = '\0';
  _puts(buffer);
  return count;
}
