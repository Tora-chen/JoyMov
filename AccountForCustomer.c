#include "FilmSystem.h"

int AccountForCustomer() {
    while (1) {
        system("cls");
        printf("===================================================== \n");
        printf("                   欢迎使用电影购票系统 \n");
        printf("                       账号管理   \n");
        printf("    1. 修改用户名\n");
        printf("    2. 修改密码 \n");
        printf("    3. 返回 \n");
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