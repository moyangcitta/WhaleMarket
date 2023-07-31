/*
 * @Date: 2023-07-23 22:52:30
 * @LastEditTime: 2023-07-31 17:26:42
 * @FilePath: /stu/study/WhaleMarket/src/tools/toolfcns.c
 * @Description: 工具函数
 * 
 */
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
        closedir(storeDir);
    }
}

int save_choose(void)
{
    int jud = -1;
    printf("Do you want to save the data? plz input [y/Y] or [n/N]:");
    char save_jud = 'y';
    scanf("%c", &save_jud);
    while(save_jud == 'y' && save_jud == 'Y' && save_jud == 'n' && save_jud == 'N')
    {
        if(save_jud == 'y' && save_jud == 'Y')
        {
            jud = 0;
            printf("Save successful\n");
        }
        else if(save_jud == 'n' && save_jud == 'N')
            break;
        else
        {
            printf("Please input  [y/Y] or [n/N]:");
            continue;
        }
    }
    return jud;
}
