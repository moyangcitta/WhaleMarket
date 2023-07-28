#include "good.h"

/*
输入：数组长度
功能：创建初始动态数组
输出：返回动态数组的地址
*/
GOODS_ARRAY create_array(int size)
{
    GOODS_ARRAY array;
    array.size = size;
    array.goods_array = (GOODS*)malloc(sizeof(GOODS)*size);
}

/*
输入：动态数组
功能：清空动态数组
输出：无
*/
void free_array(GOODS_ARRAY *array)
{
    free(array->goods_array);
    array->size = 0;
    array->goods_array = NULL;
}

/*
输入：动态数组
功能：返回数组长度
输出：数组长度
*/
int array_size(GOODS_ARRAY *array)
{
    return array->size;
}

/*
输入：array，数组
功能：向数组中增加数据，如果商品信息小于200行且数组有空余，则增加数据，如果商品信息小于200行且数组无空余，则扩充数组，如果商品信息达到200行，则输出报错
输出：无
*/
void array_add(GOODS_ARRAY *array)
{
    if(array->real_size == 200)
    {
        printf("Goods information greater than 200, can't input Goods information!");
    }
    else if(array->real_size < array->size)
    {
        good_add(array);
    }
    else if(array->real_size > array->size)
    {
        array_inflate(array);
        good_add(array);
    }
}

/*
输入：array，商品信息数组
功能：向商品信息数组中存入数据
输出：无
*/
void good_add(GOODS_ARRAY *array)
{
    char good_ID[6];            //商品ID，开头字符为大写字符M，后5位为数字
    char good_name[10];         //名称，不超过10个字符，中文汉字或英文字母
    double good_price;          //价格，大于零的小数，精确到小数点后一位
    char good_desription[100];  //描述，商品的描述信息，不超过100个字符
    char seller_ID[6];          //卖家ID，开头字符为大写字符U，后5位为数字
    char listing_time[10];      //上架时间，yyyy-mm-dd
    int good_status;            //商品状态，包括已售出，已下架，销售中
    scanf("%s", array->goods_array[array->real_size++].good_ID);
    scanf("%s", array->goods_array[array->real_size++].good_name);
    scanf("%.1lf", array->goods_array[array->real_size++].good_price);
    scanf("%s", array->goods_array[array->real_size++].good_desription);
    scanf("%s", array->goods_array[array->real_size++].seller_ID);
    scanf("%s", array->goods_array[array->real_size++].listing_time);
    scanf("%s", array->goods_array[array->real_size++].good_status);
}

/*
输入：array，商品信息数组
功能：扩充商品信息数组
输出：无
*/
void array_inflate(GOODS_ARRAY *array)
{
    GOODS *temp = (GOODS*)malloc(sizeof(GOODS)*(array->size + 5));
    for(int i = 0; i < array->real_size; i++)
    {
        temp[i] = array->goods_array[i];
    }
    free(array->goods_array);
    array->goods_array = temp;
    array->size += 5;
}

/*
输入：goods_array，商品信息数组
功能：更改商品信息，将商品信息保存到GOODS文档中
输出：无
*/
void input_goods_data(GOODS_ARRAY *goods_array)
{
    FILE *goodFp = fopen("./store/GOODS.txt", "w+");
    if(goodFp)
    {   
        for(int i = 0; i < array_size(&goods_array); i++)
        {
            fprintf(goodFp, "%s %s %.1lf %s %s %s %d\n", \
            goods_array->goods_array[i].good_ID, \
            goods_array->goods_array[i].good_name, \
            goods_array->goods_array[i].good_price, \
            goods_array->goods_array[i].good_desription, \
            goods_array->goods_array[i].seller_ID, \
            goods_array->goods_array[i].listing_time, \
            goods_array->goods_array[i].good_status);
        }
        fclose(goodFp);
    }
}

/*
输入：无
功能：读取GOODS文档中的商品信息
输出：存放商品信息的数组
*/
GOODS_ARRAY read_goods_data(void)
{
    FILE *goodFp = open("./store/GOODS.text", "r");
    GOODS_ARRAY goods_array = create_array(50);
    if(goodFp)
    {
        int i = 0;
        while(!feof(goodFp))
        {
            if(goods_array.size < i)

            fscanf(goodFp, "%s %s %.1lf %s %s %s %d\n", \
            goods_array.goods_array[i].good_ID, \
            goods_array.goods_array[i].good_name, \
            &goods_array.goods_array[i].good_price, \
            goods_array.goods_array[i].good_desription, \
            goods_array.goods_array[i].seller_ID, \
            goods_array.goods_array[i].listing_time, \
            &goods_array.goods_array[i].good_status);
            ++i;
        }
        fclose(goodFp);
    }
    return goods_array;
}
