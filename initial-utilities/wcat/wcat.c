#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {
  int status = 0;

  char buffer[1000];
  
  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wcat: cannot open file\n");
      exit(1);
    }
    
    while (fgets(buffer, sizeof buffer, fp) != NULL) {
      printf("%s", buffer);
    }
    
    if (feof(fp)) {
      status = 0;
    }
    else {
      status = 1;
      fclose(fp);
      break;
    }

    fclose(fp);
  }
  
  return status;
}

