#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

char *g_memos[10];

void init();
void print_menu();
int get_int();
void list_memos();

void command()
{
    int cmd;
    int index;
    int ret;

    print_menu();
    cmd = get_int();
    printf("index?[0-9]: ");
    index = get_int();

    switch(cmd){
    case 1:
        printf("size?: ");
        ret = get_int();
        g_memos[index] = malloc(ret);
        break;
    case 2:
        printf("memo?: ");
        read(0, g_memos[index], 0x100);
        break;
    case 3:
        puts(g_memos[index]);
        break;
    case 9:
        free(g_memos[index]);
        g_memos[index] = 0;
        break;
    default:
        break;
    }
}

int main()
{
    init();
    puts("Welcome to memo application!!!");
    while (1)
    {
        command();
        list_memos();
    }
}

void init()
{
    int i;
    alarm(180);
    setbuf(stdin, NULL);
    setbuf(stdout, NULL);
    setbuf(stderr, NULL);
    for(i = 0; i < 10; i++){
        g_memos[i] = 0;
    }
}

void print_menu()
{
    printf("1: add memo\n2: edit memo\n3: view memo\n9: del memo\ncommand?: ");
}

int get_int()
{
    char buf[10];
    int ret;
    ret = read(0, buf, 9);
    buf[ret] = 0;
    ret = atoi(buf);
    return ret;
}

void list_memos()
{
    int i;
    printf("\n\n\n[[[list memos]]]\n");
    for(i = 0; i < 10; i++){
        if(g_memos[i] != 0){
            printf("***** %d *****\n", i);
            puts(g_memos[i]);
        }
    }
    puts("");
}