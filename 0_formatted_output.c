#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include "main.h"

/**
 * _printf - Printf function
 * @format: Format string
 * Return: Number of characters printed  
 */
/*
int _printf(const char *format, ...)
{
  va_list args;
  int i, count = 0;
  char *str;

  va_start(args, format);

  for (i = 0; format[i] != '\0'; i++)
    {
      if (format[i] == '%')
        {
          switch (format[i + 1])
            {
            case 'c':
              count += write(1, (void *) (intptr_t) va_arg(args, int), 1);
              break;
            case 's':
              str = va_arg(args, char *);
              count += write(1, str, strlen(str));
              break;
            case '%':
              count += write(1, "%", 1);
              break;
            default:
              count += write(1, "%", 1);
              break;
            }
          i++;
        }
      else
        {
          count += write(1, &format[i], 1);
        }
    }
  va_end(args);
  return (count);
}
*/

void write_char(char c)
{
  fputc(c, stdout);
}

void write_string(const char *s)
{
  int i;
  
  for (i = 0; s[i] != '\0'; i++)
    {
      write_char(s[i]);
    }
}

int _printf(const char *format, ...)
{
  int count = 0;
  const char *traverse = format;

  while (*traverse != '\0')
    {
      if (*traverse == '%')
	{
	  traverse++;
	  switch (*traverse)
	    {
	    case 'c':
	      {
		char c = *((char *)(traverse - 1) + 1);
		write_char(c);
		count++;
		break;
	      }
	    case 's':
	      {
		const char *s = *((const char **)(traverse - 1) + 1);
		write_string(s);
		count += strlen(s);
		break;
	      }
	    case '%':
	      {
		write_char('%');
		count++;
		break;
	      }
	    default:
	      {
		break;
	      }
            }
        }
      else
	{
	  write_char(*traverse);
	  count++;
        }
      traverse++;
    }

  return count;
}
