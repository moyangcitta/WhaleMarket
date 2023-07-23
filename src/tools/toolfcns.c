#include "tools/toolfcns.h"

/*
输入：intTemp1，intTemp2
功能：选择intTemp1和之间的数字
返回：返回选取的数字
*/
int select_menu(int intTemp1, int intTemp2)
{
    // 输入操作
    int num = 0;
    printf("输入操作:");
    scanf("%d", &num);
    //判断输入是否正确
    while(num < intTemp1 || num > intTemp2)
    {
        printf("输入错误,请重新输入:");
        scanf("%d", &num);
    }
    return num;
}