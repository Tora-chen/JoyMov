#include "FilmSystem.h"

int Login() {
    system("cls");
    printf("=====================================================\n");
    printf("                   欢迎使用电影购票系统                \n");
    printf("                         登录界面                     \n");
    printf("=====================================================\n");

    char username[99] = { 0 };
    char password[99] = { 0 };
    char username_input[99] = { 0 };
    char password_input[99] = { 0 };

    // 输入用户名
    printf("请输入用户名：\n");
    while (1) {
        scanf("%99s", username_input);

        // 判断用户名是否存在
        if (FindAccount(username_input) != -1) {
            break;
        }

        printf("用户名不存在，请重新输入：\n");
    }

    // 程序读取密码
    FILE* Account = fopen("Account.dat", "r");
    while (1) {
        fscanf(Account, "%99s", username);
        if (strcmp(username, username_input) == 0) {
            fscanf(Account, "%99s", password);
            break;
        }
        char temp[99] = { 0 };
        fscanf(Account, "%99s", temp);
    }
    fclose(Account);

    // 输入密码
    char hash[99] = { 0 };
    printf("请输入密码：\n");
    while (1) {
        // 实现隐蔽输入
        HiddenInput(password_input, 98);

        sha256(password_input, strlen(password_input), hash);

        // 验证密码
        if (strcmp(password, hash) == 0) {
            break;
        }
        printf("密码错误，请重新输入：\n");
    }

    // 登录成功，记录用户身份，进入主界面
    printf("登录成功！");
    strcpy(USER, username_input);
    if (strcmp(USER, "root") == 0) {
        Home();
    } else {
        HomeForCustomer();
    }

    return 0;
}