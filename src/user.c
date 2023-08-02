/*
 * @Date: 2023-07-28 10:22:41
 * @LastEditTime: 2023-08-02 18:36:48
 * @FilePath: /stu/study/WhaleMarket/src/user.c
 * @Description: 
 * 
 */
#include "user.h"

/**
 * @description: 初始化用户链表
 * @return {USERS} users_list
 */
USERS_LIST* create_users_list(void)
{
    USERS_LIST *users_list = (USERS_LIST*)malloc(sizeof(USERS_LIST));
    users_list->next = NULL;
    return users_list;
}

/**
 * @description: 返回用户个数
 * @param {USERS_LIST} *users_list
 * @return {*}
 */
int users_size(USERS_LIST *users_list)
{
    int rcd = 0;
    USERS_LIST *temp_list = users_list;
    while(temp_list->next != NULL)
    {
        rcd++;
        temp_list = temp_list->next;
    }
    return rcd;
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
    //如果goods_list数量多于200
    if(20 <= users_size(users_list))
    {
        jud = -1;
    }
    else{
        USERS_LIST *temp_list = users_list;
        while(temp_list != NULL)
        {
            //如果商品链表末尾为NULL
            if(temp_list->next == NULL)
            {
                USERS_LIST *temp_node = create_users_list();
                temp_node->user_data = user_info(temp_list->user_data.user_ID);
                temp_list->next = temp_node;
                break;
            }   
            //如果商品链表中间编号不是连续的，则在断开的编号后增加商品
            if(1 < difference_value(temp_list->user_data.user_ID, temp_list->next->user_data.user_ID))
            {
                USERS_LIST *temp_node = create_users_list();
                temp_node->user_data = user_info(temp_list->user_data.user_ID);
                temp_node->next = temp_list->next;
                temp_list->next = temp_node;
                break;
            }
            temp_list = temp_list->next;
        }
        if(!save_choose())
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
USER user_info(char *pre_user_id)
{
    USER user_data;
    strcpy(user_data.user_ID, pre_user_id);
    edit_ID(user_data.user_ID);

    scanf("%s", user_data.user_name);
    scanf("%s", user_data.user_password);
    scanf("%s", user_data.user_contact);
    scanf("%s", user_data.user_address);
    scanf("%lf", &user_data.user_purse);
    return user_data;
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
        USERS_LIST *temp_list = users_list;
        if(!strcmp(temp_list->next->user_data.user_ID, user_id))
        {
            USERS_LIST *temp_node = temp_list->next;
            temp_list->next = temp_node->next;
            free(temp_node);
            if(!save_choose())
            {
                save_users_data(users_list);
            }
            jud = 0;
            break;
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
    if(users_list->next != NULL)
    {
        USERS_LIST *temp_list = users_list;
        while(temp_list->next != NULL)
        {
            if(!strcmp(temp_list->next->user_data.user_ID, user_id))
            {
                temp_list->next->user_data = user_info(temp_list->user_data.user_ID);
                jud = 0;
            }
            if(save_choose() == 0)
            {
                save_users_data(users_list);
            }
            temp_list = temp_list->next;
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
    if(users_list->next != NULL)
    {
        USERS_LIST *temp_list = users_list;
        while(temp_list->next != NULL)
        {
            if(!strcmp(temp_list->next->user_data.user_ID, user_id))
            {
                user_info = temp_list->user_data;
                break;
            }
            temp_list = temp_list->next;
        }
    }
    return user_info;
}

/**
 * @description: 从USERS文档中读取文件信息，并存放于users_header链表中
 * @param {USERS_LIST} *users_header
 * @return {*}
 */
USERS_LIST* users_data_init(void)
{
    USERS_LIST *users_header = create_users_list();
    strcpy(users_header->user_data.user_ID, "U00000");   
    FILE *userFp = fopen("./store/USERS.txt", "a+");
    if(userFp)
    {
        USERS_LIST *temp_list = users_header;
        while(!feof(userFp))
        {
            USERS_LIST *temp_node = (USERS_LIST*)malloc(sizeof(USERS_LIST));

            fscanf(userFp, "%s %s %s %s %s %lf\n", \
            temp_node->user_data.user_ID, \
            temp_node->user_data.user_name, \
            temp_node->user_data.user_password, \
            temp_node->user_data.user_contact, \
            temp_node->user_data.user_address, \
            &temp_node->user_data.user_purse);

            temp_list->next = temp_node;
            temp_list = temp_list->next;
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
        USERS_LIST *temp_list = users_list;
        while(temp_list->next != NULL)
        {
            fprintf(userFp, "%s %s %s %s %s %.1lf\n", \
            temp_list->user_data.user_ID, \
            temp_list->user_data.user_name, \
            temp_list->user_data.user_password, \
            temp_list->user_data.user_contact, \
            temp_list->user_data.user_address, \
            temp_list->user_data.user_purse);

            temp_list = temp_list->next;
        }
        fclose(userFp);
    }
    else
    {
        jud = -1;
    }
    return jud;
}
