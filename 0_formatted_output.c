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
