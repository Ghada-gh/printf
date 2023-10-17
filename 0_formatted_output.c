#include <unistd.h>
#include <stdio.h>
#include <stdarg.h>
#include <limits.h>
#include <string.h>
#include "main.h"
#include <stdint.h>
#include <inttypes.h>


/**
 * _printf - Custom printf function that handles a group of conversion specifiers.
 * @format: Format string
 * Return: Number of characters printed (excluding the null byte)
 */

int _printf(const char *format, ...)
{
  int count = 0;
  va_list args;
  int len ;
  int i ;

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
	  else if (*format == 'd' || *format == 'i')
            {
	      int num = va_arg(args, int);
	      char num_str[20];
	      int len = sprintf(num_str, "%d", num);
	      write(1, num_str, len);
	      count += len;
            }
	  else if (*format == 'b')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      char binary_str[32];
	      int len = sprintf(binary_str, "%u", num);
	      write(1, binary_str, len);
	      count += len;
            }
	  else if (*format == 'u')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      char num_str[20];
	      int len = sprintf(num_str, "%u", num);
	      write(1, num_str, len);
	      count += len;
            }
	  else if (*format == 'o')
	    {
	      unsigned int num = va_arg(args, unsigned int);
	      char num_str[20];
	      int len = sprintf(num_str, "%o", num);
	      write(1, num_str, len);
	      count += len;
	    }
	  else if (*format == 'x')
            {
	      unsigned int num = va_arg(args, unsigned int);
	      char num_str[20];
	      int len = sprintf(num_str, "%x", num);
	      write(1, num_str, len);
	      count += len;
            }
	  else if (*format == 'X')
	    {
	      unsigned int num = va_arg(args, unsigned int);
	      char num_str[20];
	      int len = sprintf(num_str, "%X", num);
	      write(1, num_str, len);
	      count += len;
	      }
	  else if (*format == 'S')
	      {
                char *str = va_arg(args, char *);
                if (str == NULL)
		  str = "(null)";
                while (*str)
		  {
                    if (*str < 32 || *str >= 127)
		      {
                        char hex[5];
                        sprintf(hex, "\\x%02X", (unsigned char)*str);
                        write(1, hex, 4);
                        count += 4;
		      }
                    else
		      {
                        write(1, str, 1);
                        count++;
		      }
                    str++;
		  }
	      }
	  else if (*format == 'p')
	    {
	      void *ptr = va_arg(args, void *);
	      char ptr_str[20];
	      sprintf(ptr_str, "%p", ptr);
	      write(1, ptr_str, strlen(ptr_str));
	      count += strlen(ptr_str);
	    }
	  else if (*format == 'R')
	      {
                char *str = va_arg(args, char *);
                if (str == NULL)
                    str = "(null)";
                for ( i = 0; str[i]; i++)
		  {
                    char rot13 = str[i];
                    if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
		      {
                        char base = (str[i] >= 'a' && str[i] <= 'z') ? 'a' : 'A';
                        rot13 = base + (str[i] - base + 13) % 26;
		      }
                    write(1, &rot13, 1);
                    count++;
		  }
	      }
	  else if (*format == 'r')
	    {
	      char *str = va_arg(args, char *);
	      if (str == NULL)
		str = "(null)";
	      len = strlen(str);
	      for (i = len - 1; i >= 0; i--)
		{
		  write(1, &str[i], 1);
		  count++;
		}
	    }
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
