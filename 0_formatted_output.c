#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include "main.h"
#include <stdint.h>
#include <inttypes.h>


/**
 * _printf - Printf function
 * @format: Format string
 * Return: Number of characters printed  
 */

int _printf(const char *format, ...)
{
  int count = 0;
  va_list args;

  va_start(args, format);

  while (*format)
    {
      if (*format == '%')
        {
	  format++;
	  if (*format == 'c')
            {
	      char c = va_arg(args, int);
	      write(1, &c, 1);
	      count++;
            }
	  else if (*format == 's')
            {
	      char *str = va_arg(args, char *);
	      if (str == NULL)
		str = "(null)";
	      while (*str)
                {
		  write(1, str, 1);
		  str++;
		  count++;
                }
            }
	  /* Added section for Task 1: handling 'd' and 'i' specifiers */
	  else if (*format == 'd' || *format == 'i')
            {
	      int num = va_arg(args, int);
	      char num_str[20];
	      int len = sprintf(num_str, "%d", num);
	      write(1, num_str, len);
	      count += len;
            }
	  /* End of task 1 */

	  /*Added section for task 2: handling 'b' specifier */
	  else if (*format == 'b')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      char binary_str[64];
	      int len = sprintf(binary_str, "%u", num);
	      write(1, binary_str, len);
	      count += len;
            }
	  /* End of Task 2 */
	  
	  else if (*format == '%')
            {
	      write(1, "%", 1);
	      count++;
            }
        }
      else
        {
	  write(1, format, 1);
	  count++;
        }
      format++;
    }

  va_end(args);
  return count;
}
