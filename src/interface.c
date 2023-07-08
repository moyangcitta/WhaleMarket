#include "interface.h"
#include "menu.h"
#include <stdio.h>
#include <stdlib.h>

int select_menu();     //选择菜单

void interface()
{
    int select_num = select_menu();
    switch(select_num)
    {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            exit(0);
            break;
        default:
            break;
    }
}

int select_menu()
{
    homepage_menu();
    // 输入操作
    int num = 0;
    printf("输入操作:");
    scanf("%d", &num);
    //判断输入是否正确
    while(num < 1 || num > 4)
    {
        printf("输入错误,请重新输入:");
        scanf("%d", &num);
    }
    return num;
}