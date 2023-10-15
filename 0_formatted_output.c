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
  char buffer[1024]; /*Task 4:Local buffer for output*/
  
  va_start(args, format);

  while (*format)
    {
      if (*format == '%')
        {
	  format++;
	  if (*format == 'c')
            {
	      char c = va_arg(args, int);
	      /*write(1, &c, 1);*/
	      buffer[count] = c; /*Task 4*/
	      count++;
            }
	  else if (*format == 's')
            {
	      char *str = va_arg(args, char *);
	      if (str == NULL)
		str = "(null)";
	      while (*str)
                {
		  /*write(1, str, 1);*/
		  buffer[count] = *str; /*Task 4*/
		  str++;
		  count++;
                }
            }
	  /* Added section for Task 1: handling 'd' and 'i' specifiers */
	  else if (*format == 'd' || *format == 'i')
            {
	      int num = va_arg(args, int);
	      /*char num_str[20];*/
	      int len = sprintf(buffer + count, "%d", num);
	      /*write(1, num_str, len);*/
	      count += len;
            }
	  /* End of task 1 */

	  /*Added section for task 2: handling 'b' specifier */
	  else if (*format == 'b')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      /*char binary_str[64];*/
	      int len = sprintf(buffer + count, "%u", num);
	      /*write(1, binary_str, len);*/
	      count += len;
            }
	  /* End of Task 2 */

	  /* Added section for task 3: handling 'u', 'o', 'x', 'X' specifiers */
	  /* handling 'u' specifier */
	  else if (*format == 'u')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      /*char num_str[20];*/
	      int len = sprintf(buffer + count, "%u", num);
	      /*write(1, num_str, len);*/
	      count += len;
            }
	  /* handling 'o' specifier */
	  else if (*format == 'o')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      /* char num_str[20];*/
	      int len = sprintf(buffer + count, "%o", num);
	      /*write(1, num_str, len);*/
	      count += len;
            }
	  /* handling 'x' specifier */
	  else if (*format == 'x')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      /*char num_str[20];*/
	      int len = sprintf(buffer + count, "%x", num);
	      /*write(1, num_str, len);*/
	      count += len;
            }
	  /* handling 'X' specifier */
	  else if (*format == 'X')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      /*char num_str[20];*/
	      int len = sprintf(buffer + count, "%X", num);
	      /* write(1, num_str, len);*/
	      count += len;
            }
	  /* End of Task 3 */

	  /*Added section for Task 5: handling 'S' specifier */
	  else if (*format == 'S')
            {
	      char *str = va_arg(args, char *);
	      if (str == NULL)
                {
		  str = "(null)";
                }
	      while (*str)
                {
		  if ((*str < 32 && *str > 0) || *str >= 127)
                    {
		      buffer[count] = '\\';
		      count++;
		      buffer[count] = 'x';
		      count++;
		      sprintf(buffer + count, "%02X", *str);
		      count += 2;
                    }
		  else
                    {
		      buffer[count] = *str;
		      count++;
                    }
		  str++;
                }
            }
	  /*End of Task 5*/

	  /* Added section for Task 6: handling 'p' specifier */
	  else if (*format == 'p')
            {
	      void *ptr = va_arg(args, void *);
	      sprintf(buffer + count, "%p", ptr);
	      count += 10;
            }
	  /*End of Task 6*/

	  
	  else if (*format == '%')
            {
	      /*write(1, "%", 1);*/
	      buffer[count] = '%';
	      count++;
            }
        }
      else
        {
	  /* write(1, format, 1);*/
	  buffer[count] = *format;
	  count++;
        }
      format++;

  /* Task 4: Check if the buffer is full, then write its content*/
      if (count >= 1024)
	{
	  write(1, buffer, count);
	  count = 0;
	}
    }
  if (count > 0)
    {
      write(1, buffer, count);
    }

  va_end(args);
  return count;
}
