//商品信息文件不超过200行

#ifndef _GOOD_H_
#define _GOOD_H_

struct GOODS
{
    char good_ID[6];            //商品ID，开头字符为大写字符M，后5位为数字
    char good_name[10];         //名称，不超过10个字符，中文汉字或英文字母
    double good_price;          //价格，大于零的小数，精确到小数点后一位
    char good_desription[100];  //描述，商品的描述信息，不超过100个字符
    char seller_ID[6];          //卖家ID，开头字符为大写字符U，后5位为数字
    char listing_time[10];      //上架时间，yyyy-mm-dd
    int good_status;            //商品状态，包括已售出，已下架，销售中
};

#endif