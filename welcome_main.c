#include "FilmSystem.h"

int main() {
    while (1) {
        // 打印欢迎界面
        system("cls");
        printf("==========================================================\n");
        printf("           ____               ____    ____  \n");
        printf("           / /                /  |    /  |  \n");
        printf("          / /                / /||   //| |  \n");
        printf("         / / ____ ___  ___  / / ||  // | |   ____  __ ___  \n");
        printf("        / / //  \\\\ \\\\  //  / /  || //  | |  //  \\\\ || //  \n");
        printf("   ____/ / ||   ||  \\\\//  / /   ||//   | | ||   || ||//  \n");
        printf(" /______/  \\\\__//    //  /_/    |_/    |_| \\\\__//  |_/ .  \n");
        printf("                  __//  \n");
        printf("                  \\_/\n");
        printf("                               欢迎使用JoyMov电影购票系统  \n");
        printf("                 (C) 2023 Zhihu Chen. All Rights Reserved.  \n\n");
        printf("         1. 登录        2. 注册        3. 退出\n\n");
        printf("==========================================================\n");

        int (*WelcomeFunc[20])(void) = {
            Login, AddAccount, GoBack
        };

        if (GetUserOrder(3, WelcomeFunc) == -1) {
            break;
        };
    }

    return 0;
}