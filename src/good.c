/*
 * @Date: 2023-07-08 10:35:44
 * @LastEditTime: 2023-08-02 18:24:05
 * @FilePath: /stu/study/WhaleMarket/src/good.c
 * @Description: 
 * 
 */
#include "good.h"

/**
 * @description: 创建商品链表
 * @return {*}
 */
GOODS_LIST* create_goods_list(void)
{
    GOODS_LIST *goods_list = (GOODS_LIST*)malloc(sizeof(GOODS_LIST));
    goods_list->next = NULL;
    return goods_list;
}

/**
 * @description: 返回链表长度
 * @param {GOODS_LIST} *goods_list
 * @return {*}
 */
int goods_size(GOODS_LIST *goods_list)
{
    int len = 0;
    GOODS_LIST *temp_list = goods_list;
    while(temp_list->next != NULL)
    {
        temp_list->next = temp_list->next->next;
        ++len;
    }
    
    return len;
}

/*
输入：array，数组
功能：向数组中增加数据，如果商品信息小于200行且数组有空余，则增加数据，如果商品信息小于200行且数组无空余，则扩充数组，如果商品信息达到200行，则输出报错
输出：无
*/
int goods_add(GOODS_LIST *goods_list)
{
    int jud = 0;
    //如果goods_list数量多于200
    if(200 <= goods_size(goods_list))
    {
        jud = -1;
    }
    else{
        GOODS_LIST *temp_list = goods_list;
        while(temp_list != NULL)
        {
            //如果商品链表末尾为NULL
            if(temp_list->next == NULL)
            {
                GOODS_LIST *temp_node = create_goods_list();
                temp_node->good_data = goods_info(temp_list->good_data.good_ID);
                temp_list->next = temp_node;
                break;
            }   
            //如果商品链表中间编号不是连续的，则在断开的编号后增加商品
            if(1 < difference_value(temp_list->good_data.good_ID, temp_list->next->good_data.good_ID))
            {
                GOODS_LIST *temp_node = create_goods_list();
                temp_node->good_data = goods_info(temp_list->good_data.good_ID);
                temp_node->next = temp_list->next;
                temp_list->next = temp_node;
                break;
            }
            temp_list = temp_list->next;
        }
        if(!save_choose())
        {
            save_goods_data(goods_list);
        }
    }
    return jud;
}

/**
 * @description: 输入商品信息，返回商品信息结构体
 * @return {*}
 */
GOODS goods_info(char *pre_good_id)
{
    GOODS good_data;
    strcpy(good_data.good_ID, pre_good_id);
    edit_ID(good_data.good_ID);
    scanf("%s", good_data.good_name);
    scanf("%lf", &good_data.good_price);
    scanf("%s", good_data.good_desription);
    scanf("%s", good_data.seller_ID);
    scanf("%s", good_data.listing_time);
    scanf("%d", &good_data.good_status);
    return good_data;
}

/**
 * @description: 删除链表中的商品信息，如果成功删除，返回0，删除失败，返回-1，表示该商品不存在
 * @param {GOODS_LIST} *goods_list
 * @param {char} *good_id
 * @return {*}
 */
int goods_del(GOODS_LIST *goods_list, char *good_id)
{
    int jud = -1;
    if(goods_list->next != NULL)
    {
        GOODS_LIST *temp_list = goods_list;
        while(temp_list->next != NULL)
        {
            if(!strcmp(temp_list->next->good_data.good_ID, good_id))
            {
                GOODS_LIST *temp_node = temp_list;
                temp_list->next = temp_node->next;
                free(temp_node);
                jud = 0;
                if(!save_choose())
                {
                    save_goods_data(goods_list);
                }
                break;
            }
        }
    }
    return jud;
}

/**
 * @description: 商品信息编辑，根据商品id决定需要修改的商品信息，成功编辑返回0，编辑失败返回-1
 * @param {GOODS_LIST} *goods_list
 * @param {char} *good_id
 * @return {*}
 */
int goods_edit(GOODS_LIST *goods_list, char *good_id)
{
    int jud = -1;
    if(goods_list->next != NULL)
    {
        GOODS_LIST *temp_list = goods_list;
        while(temp_list->next != NULL)
        {
            if(!strcmp(temp_list->next->good_data.good_ID, good_id))
            {
                temp_list->next->good_data = goods_info(temp_list->good_data.good_ID);
                jud = 0;
                break;
            }
        }
        if(!save_choose())
        {
            save_goods_data(goods_list);
        }
        temp_list = temp_list->next;
    }
    return jud;
}

/*
输入：goods_array，商品信息数组
功能：更改商品信息，将商品信息保存到GOODS文档中
输出：无
*/
int save_goods_data(GOODS_LIST *goods_list)
{
    int jud = -1;
    FILE *goodFp = fopen("./store/GOODS.txt", "w+");
    if(goodFp)
    {   
        GOODS_LIST *temp_list = goods_list;
        while(temp_list->next != NULL)
        {
            fprintf(goodFp, "%s %s %.1lf %s %s %s %d\n", \
            temp_list->next->good_data.good_ID, \
            temp_list->next->good_data.good_name, \
            temp_list->next->good_data.good_price, \
            temp_list->next->good_data.good_desription, \
            temp_list->next->good_data.seller_ID, \
            temp_list->next->good_data.listing_time, \
            temp_list->next->good_data.good_status);
            
            temp_list = temp_list->next;
        }
        fclose(goodFp);
        jud = 0;
    }
    return jud;
}

/*
输入：无
功能：读取GOODS文档中的商品信息
输出：存放商品信息的数组
*/
GOODS_LIST* goods_data_init(void)
{
    FILE *goodFp = fopen("./store/GOODS.txt", "a+");
    //创建商品链表头节点
    GOODS_LIST *goods_list = create_goods_list();
    strcpy(goods_list->good_data.good_ID, "M00000");
    if(goodFp)
    {
        GOODS_LIST *temp_list = goods_list;
        //从头节点的下一个节点开始读取
        while(!feof(goodFp))
        {
            GOODS_LIST *temp_node = create_goods_list();
            fscanf(goodFp, "%s %s %lf %s %s %s %d\n", \
            temp_node->good_data.good_ID, \
            temp_node->good_data.good_name, \
            &temp_node->good_data.good_price, \
            temp_node->good_data.good_desription, \
            temp_node->good_data.seller_ID, \
            temp_node->good_data.listing_time, \
            &temp_node->good_data.good_status);
            
            temp_list->next = temp_node;
            temp_list = temp_list->next;
        }
        fclose(goodFp);
    }
    return goods_list;
}
