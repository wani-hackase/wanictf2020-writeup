#include <stdio.h>
#include <string.h>

####

int check(const int i, const unsigned char *flag)
{
  int res;
  switch (i)
  {
$$$$
  }
}

int main(void)
{
  char input[0x2b];
  char flag[0x25];
  int result;
  printf("input flag : ");
  scanf("%s", input);

  if (strlen(input) != 0x2b || strncmp(input, "FLAG{", 5) != 0 || strcmp(&input[0x2a], "}") != 0)
  {
    puts("Incorrect");
    return 1;
  }
  strncpy(flag, input + 5, 0x25);
  for (int i = 0; i < %%%%; i++)
  {
    result = check(i, flag);
    if (result == 0)
    {
      continue;
    }
    if (result == 1)
    {
      puts("Incorrect");
      return 1;
    }
    if (result == 2)
    {
      printf("Correct! Flag is %s\n", input);
      return 0;
    }
  }
  return 0;
}
