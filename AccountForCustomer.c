#include "FilmSystem.h"

int AccountForCustomer() {
    while (1) {
        system("cls");
        printf("===================================================== \n");
        printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ \n");
        printf("                       �˺Ź���   \n");
        printf("    1. �޸��û���\n");
        printf("    2. �޸����� \n");
        printf("    3. ���� \n");
        printf("===================================================== \n");


        int (*func[20])(void) = {
            ModifyUserName, ModifyPassword, GoBack
        };

        if (GetUserOrder(3, func) == ExitAndGoBack) {
            break;
        };
    }

    return 0;
};