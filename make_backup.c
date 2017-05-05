//Back up website.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <setjmp.h>

#include "date.h"
#include "make_backup.h"

void makeBackup(){
  char datebuffer [80];
  char * date = returnDate(datebuffer);

  char * path_beginning = "cp -R var/www/ Users/neilpelow/Documents/SystemsSoftware/assignment1/backup/";
  int newSize = strlen(path_beginning) + strlen(date) + 1;
  char * newBuffer = (char *)malloc(newSize);
  strcpy(newBuffer, path_beginning);
  strcat(newBuffer, date);

  if (system(newBuffer) < 0){
    openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Failed to backup: %s", strerror(errno));
    closelog();
  }
  free(newBuffer);
}
