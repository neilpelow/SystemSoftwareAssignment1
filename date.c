#include <stdio.h>
#include <time.h>

char* returnDate(char * buffer){
  time_t rawtime;
  struct tm * timeinfo;
  time (&rawtime);
  timeinfo = localtime(&rawtime);
  strftime(buffer,80,"%d_%m_%Y", timeinfo);

  return buffer;
}
