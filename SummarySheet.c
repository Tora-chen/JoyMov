#include "FilmSystem.h"
int SummarySheet() {
    while (1) {
        int index = 0;
        system("cls");
        printf("===================================================== \n");
        printf("                   欢迎使用电影购票系统 \n");
        printf("                       汇总报表   \n");
        printf("    %d. 余票量汇总 \n", ++index);
        printf("    %d. 交易金额汇总 \n", ++index);
        printf("    %d. 返回 \n", ++index);
        printf("===================================================== \n");

        int (*functions[20])(void) = {
            ViewTicketNum, GoBack, GoBack
        };
        if (GetUserOrder(index, functions) == -1) {
            break;
        }
    }
    return 0;
};

int ViewTicketNum() {
    FilmInfoT info[999] = { 0 };
    ReadFilmInfo(info);

    system("cls");
    printf("电影名称　　　　　　　　　　"); // 10格全角空格
    printf("余票量\n");
    for (int i = 0; info[i].id != 0; i++) {
        printf("%-35s", info[i].name);
    }

    PressQToGoBack();
    return 0;
}