/*
 * @Date: 2023-07-23 22:50:29
 * @LastEditTime: 2023-07-31 17:24:16
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

int select_menu(int intTemp1, int intTemp2);    //选择菜单
void create_dir(void);                          //创建目录
int save_choose();                              //选择是否保存

#endif