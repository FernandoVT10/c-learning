#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int htoi(const char* s)
{
  int s_length = strlen(s);

  bool has_suffix = s_length > 2 && s[0] == '0' && s[1] == 'x';

  int hex_start_point = 0;
  if(has_suffix) hex_start_point = 2;

  int pow = 1;
  int res = 0;

  for(int i = s_length - 1; i >= hex_start_point; i--) {
    int num = 0;

    if(s[i] >= '0' && s[i] <= '9') {
      num = s[i] - '0';
    } else if(s[i] >= 'a' && s[i] <= 'f') {
      num = s[i] - 'a' + 10;
    } else if(s[i] >= 'A' && s[i] <= 'F') {
      num = s[i] - 'A' + 10;
    } else {
      return -1;
    }

    res += num * pow;
    pow *= 16;
  }

  return res;
}

int main()
{
  char hex_string[9];
  fgets(hex_string, 8, stdin);

  // Allows hitting enter to proceed with the conversion
  char last_char = hex_string[strlen(hex_string) - 1];
  if(last_char == '\n') {
    hex_string[strlen(hex_string) - 1] = '\0';
  }

  int res = htoi(hex_string);

  if(res == -1) {
    fprintf(stderr, "Error: %s hex string is not valid\n", hex_string);
    return -1;
  }

  if(last_char != '\n') putchar('\n');

  printf("The hex value %s is %d in decimal\n", hex_string, res);
  return 0;
}
