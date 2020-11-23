#include <stdio.h>
#include <string.h>

#define FLAG "FLAG{s0me_str1ngs_rem4in_1n_t7e_b1nary}"

int main(void)
{
  char input[50];
  printf("input flag : ");
  scanf("%s", input);

  if (strlen(input) != 39)
  {
    puts("Incorrect");
    return 1;
  }

  if (strncmp(input, FLAG, 39) == 0)
  {
    printf("Correct! Flag is %s\n", input);
  }
  else
  {
    puts("Incorrect");
  }
  return 0;
}
