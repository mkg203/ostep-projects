#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void read_file(int argc, char* argv[]) {
  char buffer[1000];
  char *search = argv[1];

  for (int i = 2; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wgrep: cannot open file\n");
      exit(1);
    }

    while (fgets(buffer, sizeof buffer, fp) != NULL) {
      if (strstr(buffer, search)) {
        printf("%s", buffer);
      }
    }

    if (feof(fp)) {
    } else {
      break;
    }

    fclose(fp);
  }
}

void read_stdin(int argc, char* argv[]) {
  char buffer[1000];
  char *search = argv[1];
  
  while (fgets(buffer, sizeof buffer, stdin) != NULL) {
    if (strstr(buffer, search)) {
      printf("%s", buffer);
    }
  }
}

int main(int argc, char *argv[]) {

  if (argc > 2) {
    read_file(argc, argv);
  }
  else if (argc == 2) {
    read_stdin(argc, argv);
  }
  else if (argc == 1) {
    printf("wgrep: searchterm [file ...]\n");
    exit(1);
  }

  return 0;
}
