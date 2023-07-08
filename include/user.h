//整个用户文件不超过20行

#ifndef _USER_H_
#define _USER_H_

struct USERS
{
    char user_ID[6];        //用户ID，开头字符为大写字符U，后5位为数字
    char user_name[10];     //用户名，不超过10个字符，中文汉字或英文字母
    char user_password[20]; //密码，不超过20个字符，只由小写字母和数字组成
    int user_contact[20];   //联系方式，不超过20个字符，由数字组成
    char user_address[20];  //地址，不超过20个字符，中文汉字或英文字母
    double user_purse;      //保留一位小数
};

#endif