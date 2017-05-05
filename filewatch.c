//AUDITD logging on the website so the CTO knows who to fire!
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <setjmp.h>

#include "date.h"

void makeAuditRecord(){
  char datebuffer[80];
  char * date = returnDate(datebuffer);
  char * path_beginning = "ausearch -f /var/www/ > /Users/neilpelow/Documents/SystemsSoftware/assignment1/changelogs/";
  char * filetype = ".txt";
  int newSize = strlen(path_beginning) + strlen(date) + strlen(filetype) + 1;
  char * newBuffer = (char *)malloc(newSize);
  strcpy(newBuffer, path_beginning);
  strcat(newBuffer, date);
  strcat(newBuffer, filetype);

  if (system(newBuffer) < 0){
    openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Failed to AUDITD: %s", strerror(errno));
    closelog();
  }
  free(newBuffer);
}
