#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/stat.h>
#include <syslog.h>
#include <setjmp.h>

#include "make_backup.h"
#include "filewatch.h"
#include "permissions.h"
#include "updatewebsite.h"
#include "configuration.h"

void main (int argc, char **argv) {
  printf("\nProgram is running.");
  // BEGIN_WEBSITE_FILEWATCH
  char * start_filewatch = "auditctl -w /var/www/ -p rwxa";
  if (system(start_filewatch) < 0){
    openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Failed to start AUDITD: %s", strerror(errno));
    closelog();
  } else {
    printf("\nWebsite filewatch is active...");
  }
  // END_WEBSITE_FILEWATCH

  int pid = fork();
  if (pid < 0){
    openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
    syslog(LOG_INFO, "Failed to fork: %s", strerror(errno));
    closelog();
  }
  //Step1: Create Orphan by killing parent
  if (pid > 0){
    printf("\nParent");
    sleep(1);
    exit(EXIT_SUCCESS);
  }
  else if(pid == 0){
    //Step2: Set sessionId
    if(setsid() < 0){
      openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
      syslog(LOG_INFO, "Failed to set SID: %s", strerror(errno));
      closelog();
      exit(EXIT_FAILURE);
    }
    //Step3: File privileges to read and write
    umask(0);
    //Step4: Change file directory
    if (chdir("/") < 0) {
      openlog("systemsoftware_log", LOG_PID|LOG_CONS, LOG_USER);
      syslog(LOG_INFO, "Failed to CHDIR: %s", strerror(errno));
      closelog();
      exit(EXIT_FAILURE);
    }
    //Step5: Close file descriptors
    int x;
    for ( x = sysconf(_SC_OPEN_MAX); x >= 0; x--) {
      close(x);
    }
    while(1) {
      char do_backup[10] = "";
      read_config_file("./config.txt", do_backup);

      // Start sleep until given time.
      struct tm newyear;
      time_t now = time(NULL);
      int diff;
      newyear = *localtime(&now);
      newyear.tm_hour = atoi(argv[1]);
      newyear.tm_min = atoi(argv[2]);
      newyear.tm_sec = 0;
      diff = difftime(mktime(&newyear), now);
      sleep(diff);
      // End sleep.

      //Begin backup process. Block any changes during backup. 
      lockfiles("1111");
      // Creating the AUDITD record.
      makeAuditRecord();
      // Creating the website backup.
      makeBackup();
      //Update website from the intranet site.
      updateWebsite();
      lockfiles("0777");
    }
  }
}
