/*
 * @Date: 2023-07-08 10:35:50
 * @LastEditTime: 2023-08-01 16:11:30
 * @FilePath: /stu/study/WhaleMarket/include/good.h
 * @Description: 
 * 
 */
//商品信息文件不超过200行

#ifndef _GOOD_H_
#define _GOOD_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tools/toolfcns.h"

typedef struct{
    char good_ID[6];            //商品ID，开头字符为大写字符M，后5位为数字
    char good_name[10];         //名称，不超过10个字符，中文汉字或英文字母
    double good_price;          //价格，大于零的小数，精确到小数点后一位
    char good_desription[100];  //描述，商品的描述信息，不超过100个字符
    char seller_ID[6];          //卖家ID，开头字符为大写字符U，后5位为数字
    char listing_time[10];      //上架时间，yyyy-mm-dd
    int good_status;            //商品状态，包括已售出，已下架，销售中
} GOODS;

//链表，第一个节点为空节点，用于保存链表的头部地址
typedef struct GOODS_LIST{
    GOODS good_data;
    struct GOODS_LIST *next;
} GOODS_LIST;

GOODS_LIST* create_goods_array(void);                   //创建商品链表
int goods_size(GOODS_LIST *goods_list);                 //返回链表长度
int goods_add(GOODS_LIST *goods_list);                  //向商品链表中增加数据
GOODS goods_info(char *pre_good_id);                    //输入商品信息，返回商品信息结构体
int goods_del(GOODS_LIST *goods_list, char *good_id);   //删除链表中的商品信息
int goods_edit(GOODS_LIST *goods_list, char *good_id);  //根据商品id编辑相应的商品信息
int save_goods_data(GOODS_LIST *goods_array);           //更改商品信息，将商品信息输入到文件中
GOODS_LIST* goods_data_init(void);                      //判断商品文档是否存在，如果存在读取文件中的商品信息，如果不存在创建商品文档

#endif