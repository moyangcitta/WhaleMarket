/*
 * @Date: 2023-07-08 11:00:22
 * @LastEditTime: 2023-08-02 18:36:32
 * @FilePath: /stu/study/WhaleMarket/include/user.h
 * @Description: 
 * 
 */
//整个用户文件不超过20行

#ifndef _USER_H_
#define _USER_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "./tools/toolfcns.h"

typedef struct
{
    char user_ID[6];        //用户ID，开头字符为大写字符U，后5位为数字
    char user_name[10];     //用户名，不超过10个字符，中文汉字或英文字母
    char user_password[20]; //密码，不超过20个字符，只由小写字母和数字组成
    char user_contact[20];  //联系方式，不超过20个字符，由数字组成
    char user_address[20];  //地址，不超过20个字符，中文汉字或英文字母
    double user_purse;      //保留一位小数
} USER;

//用户链表
typedef struct USERS_LIST{
    USER user_data;                 //保存单个用户数据
    struct USERS_LIST *next;        //保存下一位用户数据的地址
} USERS_LIST;

USERS_LIST* create_users_list(void);                              //创建用户链表
int users_size(USERS_LIST *users_list);         //返回用户个数
int users_add(USERS_LIST *users_list, USER user_data);  //增加用户信息
USER user_info(char *pre_user_id);                        //用户信息填写
int user_del(USERS_LIST *users_list, char *user_id);    //删除用户信息
int user_edit(USERS_LIST *users_list, char *user_id);   //修改用户信息
USER user_find(USERS_LIST *users_list, char *user_id);  //查找用户信息
USERS_LIST* users_data_init(void);                        //从文件中读取用户信息，并存放于链表中
int save_users_data(USERS_LIST *users_list);            //将用户链表中的用户信息存放到USERS文件中

#endif