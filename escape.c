#include <stdio.h>
#include <string.h>
#include <stdbool.h>

// 1 for \0 and the other two for characters
#define ESCAPE_LEN 3

bool escape(char *s, char *t, int t_size)
{
  int t_i = 0;

  for(int i = 0; i < strlen(s); i++) {
    if(t_i + ESCAPE_LEN >= t_size) return false;

    switch (s[i]) {
      case '\n':
        t[t_i] = '\\';
        t[++t_i] = 'n';
        break;
      case ' ':
        t[t_i] = '\\';
        t[++t_i] = 's';
        break;
      case '\t':
        t[t_i] = '\\';
        t[++t_i] = 't';
        break;
      default:
        t[t_i] = s[i];
        break;
    }

    t[++t_i] = '\0';
  }

  return true;
}

int main()
{
  int t_size = 1000, s_size = 500;
  char s[s_size], t[t_size];

  fgets(s, s_size, stdin);

  if(escape(s, t, t_size)) {
    char last_char = s[strlen(s) - 1];
    if(last_char != '\n') putchar('\n');

    printf("The escaped text is: %s\n", t);
  } else {
    fprintf(stderr, "Error: escape could not process %s\n", s);
  }

  return 0;
}
