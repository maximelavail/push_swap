#include "push_swap.h"

void      ft_log(char *err)
{
          mkdir("log", 0777);

          FILE *logfile = fopen("log/log.txt", "a+");

          fprintf(logfile, "%s\n", err);

          fclose(logfile);
}

void      ft_error(int c) 
{
          if (c == 1)
          {
                    ft_log("Error you did not specify any arguments");
          }
          if (c == 2)
          {
                    ft_log("Error you have entered a number greater than int_max or less than int_min");
          }
          printf("Error\n");
          exit(0);
}