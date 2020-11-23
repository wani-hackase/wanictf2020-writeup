#include <stdio.h>
#include <string.h>

int main(void)
{
  char input[50];
  printf("input flag : ");
  scanf("%s", input);

  if (strlen(input) != 36)
  {
    puts("incorrect");
    return 1;
  }

  // FLAG{5imp1e_Revers1ng_4rray_5trings}
  char flag[36] = {'F', 'L', 'A', 'G', '{', '5', 'i', 'm', 'p', '1', 'e', '_', 'R', 'e', 'v', 'e', 'r', 's', '1', 'n', 'g', '_', '4', 'r', 'r', 'a', 'y', '_', '5', 't', 'r', 'i', 'n', 'g', 's', '}'};

  for (int i = 0; i < sizeof(flag); i++)
  {
    if (input[i] != flag[i])
    {
      puts("Incorrect");
      return 1;
    }
  }
  printf("Correct! Flag is %s\n", input);
  return 0;
}
