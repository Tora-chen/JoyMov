#include "FilmSystem.h"

int main() {
    while (1) {
        // ��ӡ��ӭ����
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
        printf("                               ��ӭʹ��JoyMov��Ӱ��Ʊϵͳ  \n");
        printf("                 (C) 2023 Zhihu Chen. All Rights Reserved.  \n\n");
        printf("         1. ��¼        2. ע��        3. �˳�\n\n");
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