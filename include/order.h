//整个历史订单不超过2000行

#ifndef _ORDER_H_
#define _ORDER_H_

struct ORDERS
{
    char order_ID[6];       //订单ID，开头字符为大写字符T，后5位为数字
    char good_ID[6];        //商品ID，开头字符为大写字符M，后5位为数字
    double trading_price;   //交易金额，大于零的小数，精确到小数点后一位
    char trading_time[10];  //交易时间，yyyy-mm-dd
    char seller_ID[6];      //卖家ID，开头字符为大写字符U，后5位为数字
    char buyer_ID[6];       //买家ID，开头字符为大写字符U，后5位为数字
};

#endif