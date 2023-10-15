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
/* 
void handle_conversion(const char *format, va_list args, char *buffer)
{
  char *temp = buffer;

  while (*format != '\0')
    {
      if (*format == '%')
        {
	  format++;
	  if (*format == 'c')
            {
	      char c = (char)va_arg(args, int);
	      *temp++ = c;
            }
	  else if (*format == 's')
            {
	      char *s = va_arg(args, char *);
	      strcpy(temp, s);
	      temp += strlen(s);
            }
	  else if (*format == '%')
            {
	      *temp++ = '%';
            }
	  else if (*format == 'd' || *format == 'i')
            {
	      int d = va_arg(args, int);
	      sprintf(temp, "%d", d);
	      temp += strlen(temp);
            }
	  else if (*format == 'u')
            {
	      unsigned int u = va_arg(args, unsigned int);
	      sprintf(temp, "%u", u);
	      temp += strlen(temp);
            }
	  else if (*format == 'o')
            {
	      unsigned int o = va_arg(args, unsigned int);
	      sprintf(temp, "%o", o);
	      temp += strlen(temp);
            }
	  else if (*format == 'x' || *format == 'X')
            {
	      unsigned int x = va_arg(args, unsigned int);
	      sprintf(temp, "%x", x);
	      temp += strlen(temp);
            }
	  else if (*format == 'p')
            {
	      void *p = va_arg(args, void *);
	      sprintf(temp, "%p", p);
	      temp += strlen(temp);
            }
	  else if (*format == '\0')
            {
	      break;
            }
	  else
            {
	      *temp++ = '%';
	      *temp++ = *format;
            }
        }
      else
        {
	  *temp++ = *format;
        }
      format++;
    }
  *temp = '\0';
}

int _printf(const char *format, ...)
{
  va_list args;
  char buffer[4096];
  int length;

  va_start(args, format);
  handle_conversion(format, args, buffer);
  va_end(args);

  length = strlen(buffer);
  fwrite(buffer, sizeof(char), length, stdout);
  return (length);
}
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
