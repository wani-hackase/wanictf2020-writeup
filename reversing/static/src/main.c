#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// FLAG{rc4_4nd_3tatic_1ink_4nd_s7ripp3d_p1us_upx_pack3d}

void incorrect()
{
  puts("Incorrect");
  exit(0);
}

int check_length(const unsigned char *input)
{
  if (strlen(input) == 54)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int check_first(const unsigned char *input)
{
  if (strncmp(input, "FLAG{", 5) == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int check_end(const unsigned char *input)
{
  if (strcmp(&input[53], "}") == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int check_flag(const unsigned char *flag)
{
  int check = 0;
  int res[48] = {1673648587, 943659954, 1091034512, 881074101, 1052636472, 827741573, 1307510110, 469625721, 605130745, 656578792, 2059187682, 155607921, 2006560776, 388139424, 1075455395, 969826744, 1458334120, 275718076, 2013020381, 1210625693, 575847095, 1167285708, 1969601946, 1524777152, 552457729, 1194730498, 190971079, 2088110007, 1828156285, 1377985274, 1591816603, 1354321058, 174161412, 535367484, 87911553, 1226797853, 1363109188, 1395421621, 1696423675, 1968239986, 2052000511, 1608127566, 2123847799, 1911077513, 1996266935, 1051819631, 733420610, 1307117554};
  int key[48];
  srand(19640503);
  for (int i = 0; i < 48; i++)
  {
    key[i] = rand();
  }
  for (int i = 0; i < 48; i++)
  {
    if ((flag[i] ^ key[i]) != res[i])
    {
      check = 1;
    }
  }
  if (check == 0)
  {
    return 0;
  }
  else
  {
    return 1;
  }
}

int main(void)
{
  char input[54];
  char flag[48];
  int result;
  printf("input flag : ");
  scanf("%s", input);

  if (check_length(input) != 0)
  {
    incorrect();
  }

  if (check_first(input) != 0)
  {
    incorrect();
  }

  if (check_end(input) != 0)
  {
    incorrect();
  }

  strncpy(flag, input + 5, 48);

  if (check_flag(flag) == 0)
  {
    printf("Correct! Flag is %s\n", input);
    return 1;
  }
  else
  {
    puts("Incorrect");
  }
  return 0;
}
