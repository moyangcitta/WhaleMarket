/*
 * @Date: 2023-07-28 15:58:34
 * @LastEditTime: 2023-08-03 19:07:39
 * @FilePath: /stu/study/WhaleMarket/src/order.c
 * @Description: 
 * 
 */
#include "order.h"

/**
 * @description: 创建订单链表，并返回一个订单链表节点
 * @return {*}
 */
ORDERS_LIST* create_orders_list(void)
{
    ORDERS_LIST *orders_list = (ORDERS_LIST*)malloc(sizeof(ORDERS_LIST));
    orders_list->next = NULL;
    return orders_list;
}

/**
 * @description: 创建订单队列，返回队列结构订单
 * @return {ORDERS_QUEUE}
 */
ORDERS_QUEUE* create_orders_queue(void)
{
    ORDERS_QUEUE *orders_queue = (ORDERS_QUEUE*)malloc(sizeof(ORDERS_QUEUE));
    orders_queue->order_header = create_orders_list();
    orders_queue->order_rear = create_orders_list();

    return orders_queue;
}

/**
 * @description: 返回队列的大小
 * @param {ORDERS_QUEUE*} orders_queue
 * @return {*}
 */
int orders_size(ORDERS_QUEUE* orders_queue)
{
    int rcd = 0;
    ORDERS_LIST* orders_list = orders_queue;
    while(orders_list->next != NULL)
    {
        rcd++;
        orders_list = orders_list->next;
    }
    return rcd;
}

/**
 * @description: 输入订单信息，输入成功返回0，输入失败返回-1
 * @param {ORDER} *order_data
 * @return {*}
 */
ORDERS order_info(void)
{
    int jud = 0;
    ORDERS order_data;
    scanf("%lf", &order_data.trading_price);
    scanf("%s", order_data.trading_time);
    scanf("%s", order_data.seller_ID);
    scanf("%s", order_data.buyer_ID);
    return order_data;
}

/**
 * @description: 将订单数据推到队列中，当成功推送时返回为0，推送失败时返回-1
 * @param {ORDERS_QUEUE} *orders_queue
 * @return {*}
 */
int order_push(ORDERS_QUEUE *orders_queue)
{
    int jud = -1;
    ORDERS_LIST *temp_list = create_orders_list();
    if(2000 == orders_size(orders_queue))
    {
        order_pop(orders_queue);
    }
    temp_list->order_data = order_info();
        
    orders_queue->order_rear->next = temp_list;
    orders_queue->order_rear = temp_list;
    if(save_choose())
    {
        save_orders_data(orders_queue);
    }
    jud = 0;
    return jud;
}

/**
 * @description: 将订单的早期数据推出队列，推出成功返回0，推出失败返回-1
 * @param {ORDERS_QUEUE} *orders_queue
 * @return {*}
 */
int order_pop(ORDERS_QUEUE *orders_queue)
{
    int jud = 0;
    if(0 == orders_size(orders_queue))
    {
        jud = -1;
    }
    else
    {
        ORDERS_LIST *temp_list = orders_queue->order_header;
        orders_queue->order_header = orders_queue->order_header->next;
        free(temp_list);
        if(save_choose())
        {
            save_orders_data(orders_queue);
        }
    }
    return jud;
}

/**
 * @description: 保存用户数据，成功返回0，失败返回-1
 * @param {ORDERS_QUEUE} *orders_queue
 * @return {*}
 */
int save_orders_data(ORDERS_QUEUE *orders_queue)
{
    int jud = -1;
    FILE *orderFp = fopen("./store/ORDERS.txt", "w+");
    if(orderFp)
    {
        ORDERS_LIST *temp_list = orders_queue->order_header;
        while(temp_list->next != NULL)
        {
            fprintf(orderFp, "%s %.1lf %s %s %s\n", \
            temp_list->next->order_data.good_ID, \
            temp_list->next->order_data.trading_price, \
            temp_list->next->order_data.trading_time, \
            temp_list->next->order_data.seller_ID, \
            temp_list->next->order_data.buyer_ID);

            temp_list = temp_list->next;
        }
        jud = 0;
        fclose(orderFp);
    }
    return jud;
}

/**
 * @description: 将ORDERS文档中的数据读取到队列中
 * @return {*}
 */
ORDERS_QUEUE* orders_data_init(void)
{
    ORDERS_QUEUE *orders_queue = create_orders_queue();
    FILE *orderFp = fopen("./store/ORDERS.txt", "a+");
    if(orderFp)
    {
        ORDERS_LIST *temp_list = create_orders_list();
        strcpy(temp_list->order_data.order_ID, "T00000");
        //orders_queue初始化
        orders_queue->order_header = temp_list;
        orders_queue->order_rear = temp_list;
        //从头节点的下一个节点开始读取
        while(!feof(orderFp))
        {
            //订单编号统一，后期通过int_to_str()函数处理
            ORDERS_LIST *temp_node = create_orders_list();
            strcpy(temp_node->order_data.order_ID, "T00000");
            
            fscanf(orderFp, "%s %lf %s %s %s\n", \
            temp_node->order_data.good_ID, \
            &temp_node->order_data.trading_price, \
            temp_node->order_data.trading_time, \
            temp_node->order_data.seller_ID, \
            temp_node->order_data.buyer_ID);

            temp_list->next = temp_node;
            temp_list = temp_list->next;
            orders_queue->order_rear = temp_node;
        }
        fclose(orderFp);
    }
    return orders_queue;
}
