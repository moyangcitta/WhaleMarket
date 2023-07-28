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

/*
输入：无
功能：创建用户信息、订单信息以及商品信息文档的储存目录，并且判断目录是否存在，如果不存在，则创建目录
输出：无
*/
void create_dir(void)
{
    //打开目录
    DIR *storeDir = opendir("./store");
    if(NULL == storeDir)
    {
        //S_IRWXU指的是允许文件所有者拥有读、写、执行的权利
        mkdir("./store", S_IRWXU);
    }
    else
    {
        close(storeDir);
    }
}