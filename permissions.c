#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <syslog.h>
#include <setjmp.h>

void lockfiles(char mode[]){
  int i;
  int exception_int;

  struct stat st;

  char path[100] = "/var/www";

  stat(path, &st);

  i = strtol(mode, 0, 8);
  if (chmod(path, i) < 0){
    openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Failed to set mode in lockfiles: %s", strerror(errno));
    closelog();
  }
}