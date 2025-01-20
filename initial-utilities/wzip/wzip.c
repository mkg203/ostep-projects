#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void write(int count, char c) {
  char b1 = count & 0xFF;
  count >>= 8;
  char b2 = count & 0xFF;
  count >>= 8;
  char b3 = count & 0xFF;
  count >>= 8;
  char b4 = count & 0xFF;
  
  char tmp[5] = {b1, b2, b3, b4, c};

  fwrite(tmp, 1, 5, stdout);
}

int main(int argc, char *argv[]) {
  if (argc == 1) {
    printf("wzip: file1 [file2 ...]\n");
    exit(1);
  }

  char buffer[1000] = {'\0'};
  char out[1000] = {'\0'};

  for (int i = 1; i < argc; i++) {
    FILE *fp = fopen(argv[i], "r");

    if (fp == NULL) {
      printf("wzip: cannot open file\n");
      exit(1);
    }

    while (fgets(buffer, sizeof buffer, fp) != NULL) {
      int count = 0;
      for (int j = 0; j < sizeof buffer; j++) {
        if (buffer[j] == '\0') {
          write(count, buffer[j - 1]);
          break;
        }

        if (j == 0 || buffer[j - 1] == buffer[j]) {
          count++;
        } else {
          write(count, buffer[j - 1]);
        }
      }
    }

    if (feof(fp)) {
    } else {
      break;
    }

    fclose(fp);
  }

  /*printf("%s", out);*/

  return 0;
}
