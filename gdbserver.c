#include <stdio.h>

int main(int argc, char **argv) {
  int i;
  FILE *file = fopen("C:/CooCox/CoIDE_V2Beta/bin/GdbConfig.cfg", "w");
  for(i = 0; i < argc; i++) {
    printf("%s\n", argv[i]);
    fprintf(file, "%s\n", argv[i]);
  }
}