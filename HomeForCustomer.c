#include "FilmSystem.h"
int HomeForCustomer() {
    while (1) {
        int index = 1;
        system("cls");
        printf("=====================================================\n");
        printf("                   欢迎使用电影购票系统\n");
        printf("                         主界面\n");
        printf("    %d. 管理账号\n", index++);
        printf("    %d. 查看电影放映信息\n", index++);
        printf("    %d. 购票退票\n", index++);
        printf("    %d. 查询电影\n", index++);
        printf("    %d. 退出登录\n", index++);
        printf("    %d. 退出系统\n", index);
        printf("=====================================================\n");

        // 函数数组，存储上述操作对应的函数指针
        // int (*functions[10])(void) = {
        //     AccountForCustomer, ViewFilmInfo, Ticket, SearchFilmInfo, GoBackToLogin, Exit
        // }; // Temply
        int (*functions[10])(void) = {
            AccountForCustomer, ViewFilmInfo, Ticket, Search, GoBackToLogin, Exit
        };

        // 获取用户输入，打开对应的功能
        if (GetUserOrder(index, functions) == -1) {
            break;
        };
    }
    return 0;
}