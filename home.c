#include "FilmSystem.h"

int Home() {
    while (1) {
        int index = 1;
        system("cls");
        printf("=====================================================\n");
        printf("                   欢迎使用电影购票系统\n");
        printf("                         主界面\n");
        printf("    %d. 账号管理\n", index++);
        printf("    %d. 电影放映信息管理\n", index++);
        printf("    %d. 票务管理\n", index++);
        printf("    %d. 查询管理\n", index++);
        printf("    %d. 统计管理\n", index++);
        printf("    %d. 汇总报表\n", index++);
        printf("    %d. 退出登录\n", index++);
        printf("    %d. 退出系统\n", index);
        printf("=====================================================\n");

        // 函数数组，存储上述操作对应的函数指针
        int (*functions[10])(void) = {
            Account, FilmInfo, Ticket, Search, Search,
            SummarySheet, GoBackToLogin, Exit
        };

        // 获取用户输入，打开对应的功能
        if (GetUserOrder(index, functions) == ExitAndGoBack) {
            break;
        }
    }
    return 0;
}