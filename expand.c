#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>

enum Type {
  RANGE_OP,
  UPPERCASE,
  LOWERCASE,
  DIGIT,
};

typedef struct {
  enum Type type;
  char literal;
} Token;

typedef struct {
  Token tokens[100];
  size_t size;
} Lexer;

void syntax_error(char *error)
{
  fprintf(stderr, "Syntax Error: %s\n", error);
  exit(1);
}

bool is_range_op(Token *token)
{
  if(!token) return false;
  return token -> type == RANGE_OP;
}

Token *get_previous_token(Lexer *lexer, size_t currentIndex) {
  if(currentIndex == 0) return NULL;
  return &lexer -> tokens[currentIndex - 1];
}

Token *get_next_token(Lexer *lexer, size_t currentIndex) {
  if(currentIndex > lexer -> size - 1) return NULL;
  return &lexer -> tokens[currentIndex + 1];
}

void parse_lexer(Lexer *lexer, char *res)
{
  size_t res_i = 0;

  for(size_t i = 0; i < lexer -> size; i++) {
    Token *t = &lexer -> tokens[i];

    switch (t -> type) {
      case UPPERCASE: case LOWERCASE: case DIGIT: {
        Token *left_token = get_previous_token(lexer, i);
        Token *right_token = get_next_token(lexer, i);

        if(!is_range_op(left_token) && !is_range_op(right_token)) {
          res[res_i++] = t -> literal;
          res[res_i] = '\0';
        }
      } break;
      case RANGE_OP: {
        char start, end;

        Token *left_token = get_previous_token(lexer, i);
        Token *right_token = get_next_token(lexer, i);

        if(!is_range_op(left_token)) start = left_token -> literal;
        else {
          fprintf(stderr, "Syntax Error: The left and right symbol of the range operator '-' should be alphanumeric\n");
          exit(1);
        }

        if(!is_range_op(right_token)) end = right_token -> literal;
        else {
          fprintf(stderr, "Syntax Error: The left and right symbol of the range operator '-' should be alphanumeric\n");
          exit(1);
        };

        if(right_token -> type != left_token -> type) {
          fprintf(stderr, "Syntax Error: The right and left symbol or the range operator '-' must be of the same type\n");
          exit(1);
        }

        while(start <= end) {
          res[res_i++] = start;
          res[res_i] = '\0';

          start++;
        }
      } break;
      default: {
        fprintf(stderr, "Error: Unreachable code\n");
        exit(1);
      } break;
    }
  }
}

void expand(char *s, char *res)
{
  Lexer lexer = {0};

  for(size_t i = 0; i < strlen(s); i++) {
    enum Type type;

    if(s[i] == '-') type = RANGE_OP;
    else if(islower(s[i])) type = LOWERCASE;
    else if(isupper(s[i])) type = UPPERCASE;
    else if(isdigit(s[i])) type = DIGIT;
    else if(isspace(s[i])) continue;
    else {
      fprintf(stderr, "Error: %c is not a valid symbol\n", s[i]);
      exit(1);
    }

    size_t index = lexer.size;
    lexer.tokens[index].type = type;
    lexer.tokens[index].literal = s[i];
    lexer.size++;
  }

  parse_lexer(&lexer, res);
}

void print_expand(char *s)
{
  char result[2000];
  expand(s, result);
  printf("expand(%s) = %s\n", s, result);
}

int main()
{
  print_expand("a-z A-F 5-5 0-9");
  print_expand("A-Z");
  print_expand("0-9");
  print_expand("a-z");
  print_expand("a a-b");

  return 0;
}
