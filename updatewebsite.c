//Update the website fron the intranet site
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <syslog.h>
#include <setjmp.h>

//#include "date.h"
#include "updatewebsite.h"

void updateWebsite(){
  char * update_exec_path = "rsync -r /Users/neilpelows/Documents/SystemsSoftware/assignment1/LIVEWEBSITE /var/www";

  if (system(update_exec_path) < 0){
    openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Failed to update live website: %s", strerror(errno));
    closelog();
  }
}
