#include <stdio.h>
#include <string.h>

enum Type {
  RANGE,
  RANGE_EX,
  LITERAL
};

typedef struct {
  enum Type type;
  char content[5];
} Token;

typedef struct {
  Token token[100];
  int index;
} Tokenizer;

int add_to_res(char start, char end, char *res, int res_index)
{
  while(start <= end) {
    res[res_index] = start;
    res[++res_index] = '\0';

    start++;
  }

  return res_index;
}

void expand(char *s, char *res)
{
  Tokenizer tokenizer = {
    index: 0
  };

  tokenizer.tokens[tokenizer.index]

  char start, end;

  for(int i = 0; i < strlen(s); i++) {
    
  }
}

void print_expand(char *s)
{
  char result[100];
  expand(s, result);
  printf("expand(%s) = %s\n", s, result);
}

int main()
{

  print_expand("-");
  // print_expand("A-Z");
  // print_expand("0-9");
  // print_expand("a-z");
  // print_expand("-a-e-");
  // print_expand("a-b-c");

  return 0;
}
