/*
 * @Date: 2023-07-28 15:58:34
 * @LastEditTime: 2023-08-02 18:48:17
 * @FilePath: /stu/study/WhaleMarket/src/order.c
 * @Description: 
 * 
 */
#include "order.h"

/**
 * @description: 创建订单队列，返回队列结构订单
 * @return {ORDERS_QUEUE}
 */
ORDERS_QUEUE* create_orders_queue(void)
{
    ORDERS_QUEUE *orders_queue = (ORDERS_QUEUE*)malloc(sizeof(ORDERS_QUEUE));
    orders_queue->order_header = (ORDER_NODE*)malloc(sizeof(ORDER_NODE));
    orders_queue->order_rear = (ORDER_NODE*)malloc(sizeof(ORDER_NODE));

    return orders_queue;
}

/**
 * @description: 输入订单信息，输入成功返回0，输入失败返回-1
 * @param {ORDER} *order_data
 * @return {*}
 */
int order_info(ORDER *order_data)
{
    int jud = 0;
    scanf("%s", order_data->order_ID);
    scanf("%s", order_data->good_ID);
    scanf("%lf", &order_data->trading_price);
    scanf("%s", order_data->trading_time);
    scanf("%s", order_data->seller_ID);
    scanf("%s", order_data->buyer_ID);
    return jud;
}

/**
 * @description: 将订单数据推到队列中，当成功推送时返回为0，推送失败时返回-1
 * @param {ORDERS_QUEUE} *orders_queue
 * @return {*}
 */
int order_push(ORDERS_QUEUE *orders_queue, ORDER order_data)
{
    int jud = 0;
    ORDER_NODE *order_node = (ORDER_NODE*)malloc(sizeof(ORDER_NODE));
    if(0 == orders_queue->order_num)
    {
        order_info(&order_node->order_data);
        order_node->next = NULL;
        orders_queue->order_header = order_node;
        orders_queue->order_rear = order_node;
        orders_queue->order_num = 1;
        if(save_choose())
        {
            save_orders_data(orders_queue);
        }
    }
    else if(2000 >= orders_queue->order_num)
    {
        order_info(&order_node->order_data);
        orders_queue->order_rear->next = order_node;
        orders_queue->order_rear = order_node;
        orders_queue->order_num++;
        if(save_choose())
        {
            save_orders_data(orders_queue);
        }
    }
    else if(2000 == orders_queue->order_num)
    {
        order_pop(orders_queue);
        order_push(orders_queue, order_data);
        if(save_choose())
        {
            save_orders_data(orders_queue);
        }
    }
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
    if(orders_queue->order_num == 0)
    {
        printf("Delete fail!\n");
        jud = -1;
    }
    else
    {
        ORDER_NODE *order_tmp = orders_queue->order_header;
        orders_queue->order_header = orders_queue->order_header->next;
        free(order_tmp);
        orders_queue->order_num--;
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
    int jud = 0;
    FILE *orderFp = fopen("./store/ORDERS.txt", "w+");
    if(orderFp)
    {
        ORDER_NODE *order_temp = orders_queue->order_header;
        while(order_temp != NULL)
        {
            fprintf(orderFp, "%s %s %.1lf %s %s %s\n", \
            order_temp->order_data.order_ID, \
            order_temp->order_data.good_ID, \
            order_temp->order_data.trading_price, \
            order_temp->order_data.trading_time, \
            order_temp->order_data.seller_ID, \
            order_temp->order_data.buyer_ID);
        }
        fclose(orderFp);
    }
    else
    {
        jud = -1;
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
        while(!feof(orderFp))
        {
            ORDER_NODE *temp_list = (ORDER_NODE*)malloc(sizeof(ORDER_NODE));
            
            fscanf(orderFp, "%s %s %lf %s %s %s\n", \
            temp_list->order_data.order_ID, \
            order_data.good_ID, \
            &order_data.trading_price, \
            order_data.trading_time, \
            order_data.seller_ID, \
            order_data.buyer_ID);
            order_push(&orders_queue, order_data);
        }
        fclose(orderFp);
    }
    return orders_queue;
}
