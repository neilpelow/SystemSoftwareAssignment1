#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_config_file(char* config_filename, char* return_value) {
  FILE *fp;
  char buff[100];

  if ((fp=fopen(config_filename, "r")) == NULL) {
    fprintf(stderr, "Failed to open config file %s", config_filename);
    //exit(EXIT_FAILURE);
    strcat(return_value, "0");
  }
  while(! feof(fp)) {
    fgets(buff,100 , fp);
    if (strstr(buff, "Backup ")) {
      char prm_name[10];
      sscanf(buff, "%s %s\n", prm_name, return_value);
    }
  }
}
