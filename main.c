   #include <stdio.h>
   #include <string.h>
   #include "sed_operations.h"

   int main(int argc, char *argv[]) {
       if (argc < 3) {
           fprintf(stderr, "Usage: %s <filename> <operation> [args...]\n", argv[0]);
           return 1;
       }

       const char *filename = argv[1];
       const char *operation = argv[2];

       // Обработка операций
       if (strcmp(operation, "-r") == 0) {
           replace_text(filename, argv[3], argv[4]);
       } else if (strcmp(operation, "-d") == 0) {
           delete_lines(filename, argv[3]);
       } else if (strcmp(operation, "-i") == 0) {
           int at_beginning = strcmp(argv[3], "-f") == 0;
           insert_text(filename, argv[4], at_beginning);
       } else {
           fprintf(stderr, "Unknown operation: %s\n", operation);
       }

       return 0;
   }
   

