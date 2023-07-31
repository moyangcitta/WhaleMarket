/*
 * @Date: 2023-07-08 10:35:50
 * @LastEditTime: 2023-07-31 22:05:49
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
#include "tools/toolfcns.h";

typedef struct{
    char good_ID[6];            //商品ID，开头字符为大写字符M，后5位为数字
    char good_name[10];         //名称，不超过10个字符，中文汉字或英文字母
    double good_price;          //价格，大于零的小数，精确到小数点后一位
    char good_desription[100];  //描述，商品的描述信息，不超过100个字符
    char seller_ID[6];          //卖家ID，开头字符为大写字符U，后5位为数字
    char listing_time[10];      //上架时间，yyyy-mm-dd
    int good_status;            //商品状态，包括已售出，已下架，销售中
} GOODS;

//链表
typedef struct GOODS_LIST{
    GOODS good_data;
    struct GOODS_LIST *next;
} GOODS_LIST;

GOODS_LIST* create_goods_array(void);     //创建商品链表
int array_size(GOODS_ARRAY *array);     //返回数组长度
void array_add(GOODS_ARRAY *array, GOODS good_data);     //向数组中增加数据
void good_info(GOODS_ARRAY *array);      //向数组中添加商品信息
void array_inflate(GOODS_ARRAY *array); //扩充商品信息数组
int del_good(GOODS_ARRAY *goods_array, char *good_id)           //根据商品ID删除商品
void save_goods_data(GOODS_ARRAY *goods_array);     //更改商品信息，将商品信息输入到文件中
GOODS_ARRAY goods_data_init(void);      //判断商品文档是否存在，如果存在读取文件中的商品信息，如果不存在创建商品文档

#endif