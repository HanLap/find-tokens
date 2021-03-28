#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int parse_fix(char input, char *fix) {
  if (input == *fix) {
    for (unsigned long i = 1; i < strlen(fix); i++) {
      char c = fgetc(stdin);
      if (!c || c == -1 || c != fix[i]) {
        ungetc(c, stdin);
        return 0;
      }
    }
    return 1;
  }

  return 0;
}

void find_tokens(char *prefix, char *postfix) {
  int reading_token = 0;

  char token[100] = {0}; 
  int token_pos = 0;

  char c = fgetc(stdin);
  while (c && c != -1) {
    // printf("%c\n", c);

    if (reading_token) {
      if (parse_fix(c, postfix)) {
        reading_token = 0;

        printf("%s\n", token);
        memset(token, 0, sizeof(token));
        token_pos = 0;
      } else {
        // printf("in token ");
        token[token_pos++] = c;
      }
    } 
    else if (parse_fix(c, prefix)){
      // printf("in token");
      reading_token = 1;
    }

    c = fgetc(stdin);
  }

}

int main(int argc, char *argv[]) {
  
  // char *input = "hewwo <%{WHO}%> is so cutee! <%{YAY}%>";
  char *prefix  = 0;
  char *postfix = 0;

  for (int i = 1; i < argc; i++) {
    char *arg = argv[i];

         if (strcmp(arg, "-p"      ) == 0
          || strcmp(arg, "--prefix") == 0) {
        prefix = argv[++i];
    } 
    else if (strcmp(arg, "-P"       ) == 0
          || strcmp(arg, "--postfix") == 0) {
        postfix = argv[++i];
    } else {
      printf("unkonw option %s", arg);
      return 1;
    }
  }

  if (prefix == 0 || postfix == 0) {
    printf ("missing options");
    return 1;
  }

  

  find_tokens(prefix, postfix);

  return 0;
}