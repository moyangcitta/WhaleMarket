/*
 * @Date: 2023-07-28 10:22:41
 * @LastEditTime: 2023-07-31 17:27:52
 * @FilePath: /stu/study/WhaleMarket/src/user.c
 * @Description: 
 * 
 */
#include "user.h"

/**
 * @description: 初始化用户链表
 * @return {USERS} users_list
 */
USERS_LIST users_create()
{
    USERS_LIST users_list;
    users_list.next = NULL;
    users_list.users_list_length = 0;
    return users_list;
}

/**
 * @description: 增加用户信息，成功添加返回0，添加失败返回-1
 * @param {USERS_LIST} *users_list
 * @param {USER} user_data
 * @return {*}
 */
int users_add(USERS_LIST *users_list, USER user_data)
{
    int jud = 0;
    if(20 == users_list->users_list_length)
    {
        printf("The number of users is enough\n");
        jud = -1;
    }
    else
    {
        USERS_LIST user_node = users_create();
        USERS_LIST *users_temp = users_list;
        while(NULL != users_temp->next)
        {
            users_temp = users_temp->next;
        }
        user_node.user_data = user_data;
        users_temp->next = &user_node;
        ++users_list->users_list_length;
        if(save_choose() == 0)
        {
            save_users_data(users_list);
        }
    }
    return jud;
}

/**
 * @description: 用户信息填写
 * @param {USER} *user_data
 * @return {*}
 */
void user_info(USER *user_data)
{
    scanf("%s", user_data->user_ID);
    scanf("%s", user_data->user_name);
    scanf("%s", user_data->user_password);
    scanf("%s", user_data->user_contact);
    scanf("%s", user_data->user_address);
    scanf("%lf", &user_data->user_purse);
}   

/**
 * @description: 根据用户id删除对应的用户，成功返回0，失败返回-1
 * @param {USERS_LIST} *users_list
 * @param {char} user_id
 * @return {*}
 */
int user_del(USERS_LIST *users_list, char *user_id)
{
    int jud = -1;
    while(users_list->next != NULL)
    {
        if(!strcmp(users_list->next->user_data.user_ID, user_id))
        {
            users_list->next = users_list->next->next;
            if(save_choose() == 0)
            {
                save_users_data(users_list);
            }
            break;
            jud = 0;
        }
    }
    return jud;
}

/**
 * @description: 根据用户id编辑相应的用户，成功返回0，失败返回-1
 * @param {USERS_LIST} *users_list
 * @param {char} user_id
 * @return {*}
 */
int user_edit(USERS_LIST *users_list, char *user_id)
{
    int jud = -1;
    while(users_list->next != NULL)
    {
        if(!strcmp(users_list->next->user_data.user_ID, user_id))
        {
            user_info(&users_list->next->user_data);
            if(save_choose() == 0)
            {
                save_users_data(users_list);
            }
            jud = 0;
        }
    }
    return jud;
}

/**
 * @description: 通过用户id查找用户信息
 * @param {USERS_LIST} *users_list
 * @param {char} user_id
 * @return {USER} 
 */
USER user_find(USERS_LIST *users_list, char *user_id)
{
    USER user_info;
    while(users_list->next != NULL)
    {
        if(!strcmp(users_list->next->user_data.user_ID, user_id))
        {
            user_info = users_list->user_data;
            break;
        }
    }
    return user_info;
}

/**
 * @description: 从USERS文档中读取文件信息，并存放于users_header链表中
 * @param {USERS_LIST} *users_header
 * @return {*}
 */
USERS_LIST get_users_data(void)
{
    USERS_LIST users_header = users_create();
    FILE *userFp = fopen("./store/USERS.txt", "a+");
    if(userFp)
    {
        while(!feof(userFp))
        {
            USER user_data;
            fscanf(userFp, "%s %s %s %s %s %lf\n", \
            user_data.user_ID, \
            user_data.user_name, \
            user_data.user_password, \
            user_data.user_contact, \
            user_data.user_address, \
            &user_data.user_purse);
            users_add(&users_header, user_data);
        }
        fclose(userFp);
    }
    return users_header;
}

/**
 * @description: 将用户数据存放到USERS文档中，如果成功存放返回0，存放失败返回-1
 * @param {USERS_LIST} *users_list
 * @return {*}
 */
int save_users_data(USERS_LIST *users_list)
{
    int jud = 0;
    FILE *userFp = fopen("./store/USERS.txt", "w+");
    if(userFp)
    {
        USERS_LIST *user_temp = users_list;
        while(user_temp->next != NULL)
        {
            fprintf(userFp, "%s %s %s %s %s %.1lf\n", \
            user_temp->user_data.user_ID, \
            user_temp->user_data.user_name, \
            user_temp->user_data.user_password, \
            user_temp->user_data.user_contact, \
            user_temp->user_data.user_address, \
            user_temp->user_data.user_purse);
        }
        fclose(userFp);
    }
    else
    {
        jud = -1;
    }
    return jud;
}
