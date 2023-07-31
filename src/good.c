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
void array_add(GOODS_ARRAY *array, GOODS good_data)
{
    if(array->real_size == 200)
    {
        printf("Goods information greater than 200, can't input Goods information!");
    }
    else if(array->real_size < array->size)
    {
        good_add(array);
        save_goods_data(array);
    }
    else if(array->real_size > array->size)
    {
        array_inflate(array);
        good_add(array);
        save_goods_data(array);
    }
}

/*
输入：array，商品信息数组
功能：向商品信息数组中存入数据
输出：无
*/
void good_info(GOODS_ARRAY *array)
{
    scanf("%s", array->goods_array[array->real_size++].good_ID);
    scanf("%s", array->goods_array[array->real_size++].good_name);
    scanf("%lf", &array->goods_array[array->real_size++].good_price);
    scanf("%s", array->goods_array[array->real_size++].good_desription);
    scanf("%s", array->goods_array[array->real_size++].seller_ID);
    scanf("%s", array->goods_array[array->real_size++].listing_time);
    scanf("%d", &array->goods_array[array->real_size++].good_status);
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

/**
 * @description: 根据商品ID删除商品，成功返回0，失败返回-1
 * @param {GOODS_ARRAY} *goods_array
 * @param {char} *good_id
 * @return {*}
 */
int del_good(GOODS_ARRAY *goods_array, char *good_id)
{
    int jud = -1;
    if(goods_array->real_size != 0)
    {
        for(int i = 0; i < goods_array->real_size; i++)
        {
            if((!strcmp(goods_array->goods_array[i].good_ID, good_id)) && (!save_choose()))
            {
                jud = 0;
                GOODS *temp = (GOODS*)malloc(sizeof(GOODS)*goods_array->size);
                for(int j = 0; j < goods_array->real_size; j++)
                {
                    if(j >= i)
                    {   
                        temp[j] = goods_array->goods_array[j + 1];
                        continue;
                    }
                    temp[j] = goods_array->goods_array[j];
                }
                free(goods_array->goods_array);
                goods_array->goods_array = temp;
                save_goods_data(goods_array);
                break;
            }
        }
    }
    if(jud == -1)
    {
        printf("删除失败，没有该商品\n");
    }
    return jud;
}

/*
输入：goods_array，商品信息数组
功能：更改商品信息，将商品信息保存到GOODS文档中
输出：无
*/
void save_goods_data(GOODS_ARRAY *goods_array)
{
    FILE *goodFp = fopen("./store/GOODS.txt", "w+");
    if(goodFp)
    {   
        for(int i = 0; i < goods_array->real_size; i++)
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
GOODS_ARRAY goods_data_init(void)
{
    FILE *goodFp = fopen("./store/GOODS.txt", "a+");
    GOODS_ARRAY goods_array = create_array(50);
    if(goodFp)
    {
        GOODS good_data;
        while(!feof(goodFp))
        {
            fscanf(goodFp, "%s %s %lf %s %s %s %d\n", \
            good_data.good_ID, \
            good_data.good_name, \
            &good_data.good_price, \
            good_data.good_desription, \
            good_data.seller_ID, \
            good_data.listing_time, \
            &good_data.good_status);
            good_add(goods_array, good_data);
        }
        fclose(goodFp);
    }
    return goods_array;
}
