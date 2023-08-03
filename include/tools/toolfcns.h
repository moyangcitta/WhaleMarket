/*
 * @Date: 2023-07-23 22:50:29
 * @LastEditTime: 2023-08-03 18:29:37
 * @FilePath: /stu/study/WhaleMarket/include/tools/toolfcns.h
 * @Description: 
 * 
 */
#ifndef __TOOLFCNS_H__
#define __TOOLFCNS_H__

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

int select_menu(int intTemp1, int intTemp2);    //选择菜单
void create_dir(void);                          //创建目录
int save_choose();                              //选择是否保存
void edit_ID(char *temp_ID);                    //根据所给的ID给出该ID的下一位ID
int difference_value(char *word1, char *word2); //比较word2减去word1的差值大小，并以整数的形式返回
void int_to_str(char *sentence, int order);     //将序号填充到字符串中

#endif