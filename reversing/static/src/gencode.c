#include <stdio.h>
#include <stdlib.h>

#define FLAG "rc4_4nd_3tatic_1ink_4nd_s7ripp3d_p1us_upx_pack3d"

int main(void)
{
  int key[48];
  int enc[48];
  srand(19640503);
  for (int i = 0; i < 48; i++)
  {
    key[i] = rand();
    printf("%d, ", key[i]);
  }
  puts("\n");
  for (int i = 0; i < 48; i++)
  {
    enc[i] = FLAG[i] ^ key[i];
    printf("%d, ", enc[i]);
  }
  puts("\n");

  int check = 0;
  for (int i = 0; i < 48; i++)
  {
    if ((FLAG[i] ^ key[i]) != enc[i])
    {
      check = 1;
    }
  }
  if (check == 0)
  {
    puts("good");
  }
  else
  {
    puts("bad");
  }
  return 0;
}
