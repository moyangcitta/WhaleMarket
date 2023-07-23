#include "interface.h"

void admin_login(void);     //管理员登录
void admin_feature(void);   //管理员功能

void interface(void)
{
    while(1)
    {
        homepage_menu();
        switch(select_menu(1, 4))
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                admin_login();
                break;
            case 4:
                exit(0);
                break;
            default:
                break;
        }
    }
}

void admin_login(void)
{
    char adminName[20];
    int password = 0;

    printf("请输入管理员姓名：");
    scanf("%s", adminName);
    printf("请输入密码：");
    scanf("%d", &password);
    if(!strcmp(adminName, "admin") && password == 123456)
    {
        printf("\n");
        printf("****** 登陆成功！ ******\n");
        administrator_menu();
        admin_feature();
    }
    else
    {
        printf("\n");
        printf("****** 登陆失败！即将返回主菜单... ******\n");
    }
}

/*
输入：无
功能：管理员功能选择菜单
返回：无
*/
void admin_feature(void)
{
    while(1)
    {
        int selectNum = select_menu(1, 7);
        if(selectNum == 7)
            break;
        else
        {
            switch(select_menu(1, 7))
            {  
                case 1:
                    break;
                case 2:
                    break;
                case 3:
                    break;
                case 4:
                    break;
                case 5:
                    break;
                case 6:
                    break;
                default:
                    break;
            }
        }
    }
}