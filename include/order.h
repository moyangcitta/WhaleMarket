/*
 * @Date: 2023-07-08 10:52:35
 * @LastEditTime: 2023-08-03 19:02:22
 * @FilePath: /stu/study/WhaleMarket/include/order.h
 * @Description: 整个历史订单不超过2000行
 * 
 */

#ifndef _ORDER_H_
#define _ORDER_H_

#include <stdio.h>
#include <stdlib.h>
#include "./tools/toolfcns.h"

typedef struct
{
    char order_ID[6];       //订单ID，开头字符为大写字符T，后5位为数字
    char good_ID[6];        //商品ID，开头字符为大写字符M，后5位为数字
    double trading_price;   //交易金额，大于零的小数，精确到小数点后一位
    char trading_time[10];  //交易时间，yyyy-mm-dd
    char seller_ID[6];      //卖家ID，开头字符为大写字符U，后5位为数字
    char buyer_ID[6];       //买家ID，开头字符为大写字符U，后5位为数字
} ORDERS;

//链表结构订单
typedef struct ORDER_NODE{
    ORDERS order_data;
    struct ORDER_NODE *next;
} ORDERS_LIST;

//队列结构订单
typedef struct{
    ORDER_NODE *order_header;
    ORDER_NODE *order_rear;
} ORDERS_QUEUE;

ORDERS_LIST* create_orders_list(void);      //创建订单链表，并返回订单链表
ORDERS_QUEUE* create_orders_queue(void);       //创建订单队列，并返回队列结构订单
int orders_size(ORDERS_QUEUE* orders_queue);    //返回队列的大小
ORDERS order_info(void);  //输入订单信息，成功返回0，失败返回-1
int order_push(ORDERS_QUEUE *orders_queue); //将订单数据推到队列中
int order_pop(ORDERS_QUEUE *orders_queue);  //将订单的早期数据推出队列
int save_orders_data(ORDERS_QUEUE *orders_queue);   //将用户数据保存到ORDERS文档中
ORDERS_QUEUE* orders_data_init(void); //将ORDERS文档中的数据读取到队列中

#endif