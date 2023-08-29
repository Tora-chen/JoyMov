#include "FilmSystem.h"

int (*Accountfunc[20])(void) = {
    ViewAccounts, ModifyUserName, ModifyPassword,
    DeleteAccount, AddAccount, GoBack
};

int Account() {
    while (1) {
        system("cls");
        printf("===================================================== \n");
        printf("                   欢迎使用电影购票系统 \n");
        printf("                       账号管理   \n");
        printf("    1. 显示所有账号 \n");
        printf("    2. 修改用户名\n");
        printf("    3. 修改密码 \n");
        printf("    4. 删除账号 \n");
        printf("    5. 添加账号 \n");
        printf("    6. 返回 \n");
        printf("===================================================== \n");


        if (GetUserOrder(6, Accountfunc) == ExitAndGoBack) {
            break;
        };
    }

    return 0;
};

int FindAccount(char username_input[]) {
    AccountT accounts[99] = { 0 };
    ReadAccountInfo(accounts);
    for (int i = 0; strlen(accounts[i].username) != 0; i++) {
        if (strcmp(accounts[i].username, username_input) == 0) {
            return i;
        }
    }
    return -1;
}

int ReadAccountInfo(AccountT accounts[]) {
    FILE* account = fopen("Account.dat", "r");
    for (int i = 0; i < 999; i++) {
        if (fscanf(account, "%99s", accounts[i].username) == -1) {
            break;
        };
        fscanf(account, "%99s", accounts[i].password_hash);
    }
    fclose(account);
    return 0;
}

int RewriteAccountInfo(AccountT accounts[]) {
    FILE* account_file = fopen("Account.dat", "w+");
    for (int i = 0; accounts[i].username[0] != 0; i++) {
        fprintf(account_file, "%s %s\n", accounts[i].username, accounts[i].password_hash);
    }
    fclose(account_file);
    return 0;
}

int ViewAccounts() {
    system("cls");
    printf("现有账号：\n");

    AccountT accounts[999] = { 0 };
    ReadAccountInfo(accounts);
    for (int i = 0; accounts[i].username[0] != 0; i++) {
        printf("%s\n", accounts[i].username);
    }
    printf("显示完毕！\n");

    PressQToGoBack();
    return 0;
}

int DeleteAccount() {
    AccountT accounts[999] = { 0 };
    ReadAccountInfo(accounts);

    // 输入要删除的账号
    char username_input[99] = { 0 };
    system("cls");
    printf("请输入要删除的账号：\n");
    int index = -1; // 记录要删除的账号的下标
    while (1) {
        scanf("%99s", username_input);

        // 寻找账号
        for (int i = 0; accounts[i].username[0] != 0; i++) {
            if (strcmp(accounts[i].username, username_input) == 0) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            break;
        }

        printf("没有该账号！请重新输入：\n");
    }

    // 确认删除
    getchar();
    printf("输入y确定删除账号\"%s\": ", accounts[index].username);
    if (getchar() != 'y') {
        printf("取消删除\n");
        GoBack(Account);
        return 0;
    }

    // 重新写入账号信息
    FILE* account_file = fopen("Account.dat", "w+");
    for (int i = 0; accounts[i].username[0] != 0; i++) {
        if (i == index) {
            continue;
        }
        fprintf(account_file, "%s %s\n", accounts[i].username, accounts[i].password_hash);
    }
    fclose(account_file);

    printf("删除完毕！\n");
    PressQToGoBack(Account);

    return 0;
}

int ModifyUserName() {
    system("cls");
    if (strcmp(USER, "root") == 0) {
        printf("root账号不允许修改用户名！\n");
        PressQToGoBack(Account);
        return 0;
    }
    // 输入新用户名
    AccountT accounts[99] = { 0 };
    ReadAccountInfo(accounts);

    char newUsername[99] = { 0 };
    printf("输入新的用户名：\n");
    printf("账号长度不大于20，仅由半角的数字、大小写字母、连接线或下划线组成。\n");
    while (1) {
        scanf("%99s", newUsername);

        // 验证字符串合法性
        int rob = PasswordRobustness(newUsername);
        if (rob == 120) {
            printf("账号太长，请重新输入：\n");
            continue;
        } else if (rob == -1) {
            printf("账号应仅含半角的数字、大小写字母、连接线或下划线。\n");
            printf("请重新输入：\n");
            continue;
        }

        // 确认是否有重复用户名
        if (FindAccount(newUsername) == -1) {
            break;
        }
        printf("该账号已存在，请重新输入\n");
    }

    // 修改用户名
    int account_index = FindAccount(USER);
    strcpy(accounts[account_index].username, newUsername);
    strcpy(USER, newUsername);

    // 重新写入账号信息
    RewriteAccountInfo(accounts);

    printf("修改成功！\n");
    PressQToGoBack(Account);
    return 0;
}

int ModifyPassword() {
    // 输入密码
    AccountT accounts[99] = { 0 };
    ReadAccountInfo(accounts);

    char newPassword[99] = { 0 };
    system("cls");
    printf("输入新的密码：\n");
    printf("密码长度在5-20之间，仅由半角的数字、大小写字母、\n");
    printf("连接线或下划线且至少由以上两种组成。\n");
    while (1) {
        HiddenInput(newPassword, 98);

        // 验证密码合法性
        int rob = PasswordRobustness(newPassword);
        if (rob == 15) {
            printf("密码太短，请重新输入：\n");
            continue;
        } else if (rob == 120) {
            printf("密码太长，请重新输入：\n");
            continue;
        } else if (rob == -1) {
            printf("密码应仅含半角的数字、大小写字母、连接线或下划线。\n");
            printf("请重新输入：\n");
            continue;
        } else if (rob <= 2) {
            printf("密码过于简单，请重新输入：\n");
            continue;
        }

        // 确认密码
        char password_verify[99] = { 0 };
        printf("请再次输入密码以确认：\n");
        HiddenInput(password_verify, 98);
        if (strcmp(newPassword, password_verify) == 0) {
            break;
        }
        printf("两次输入的密码不一致！请重新输入密码：\n");
    }
    int account_index = FindAccount(USER);
    sha256(newPassword, strlen(newPassword),
        accounts[account_index].password_hash);

    RewriteAccountInfo(accounts);

    printf("修改成功！\n");
    PressQToGoBack(Account);
}

int PasswordRobustness(char str[]) {
    /* 函数接受一个字符串，以大写字母、小写字母、数字、长度四个指标评估字符串复杂度
    若字符串短于5字符，返回15，若字符串长于20字符，返回120；
    若字符串含有半角的数字、大小写字母、连接线和下划线以外的字符，返回-1；
    若不属于以上情况，返回字符串复杂度，范围为1-4。*/
    struct robustnessT {
        int lower;
        int capital;
        int num;
        int length;
    } rob = { 0, 0, 0, 0 };

    // 检查字符串长度
    if (strlen(str) < 5) {
        return 15;
    } else if (strlen(str) > 20) {
        return 120;
    } else if (strlen(str) >= 10) {
        rob.length = 1;
    }

    // 检查组成字符
    for (int i = 0; str[i] != 0; i++) {
        if (str[i] >= 'a' && str[i] <= 'z') {
            rob.lower = 1;
        } else if (str[i] >= 'A' && str[i] <= 'Z') {
            rob.capital = 1;
        } else if (str[i] >= '0' && str[i] <= '9') {
            rob.num = 1;
        } else if (str[i] != '-' && str[i] != '_') {
            return -1;
            continue;
        }
    }

    // 评估密码复杂程度
    return rob.lower + rob.length + rob.capital + rob.num;
}
int AddAccount() {
    // 输入欲添加的账号
    char username_input[99] = { 0 };
    system("cls");
    printf("输入新的账号：\n");
    printf("账号长度不大于20，仅由半角的数字、大小写字母、连接线或下划线组成。\n");
    while (1) {
        scanf("%99s", username_input);

        // 验证字符串合法性
        int rob = PasswordRobustness(username_input);
        if (rob == 120) {
            printf("账号太长，请重新输入：\n");
            continue;
        } else if (rob == -1) {
            printf("账号应仅含半角的数字、大小写字母、连接线或下划线。\n");
            printf("请重新输入：\n");
            continue;
        }

        // 确认是否有重复账号
        if (FindAccount(username_input) != -1) {
            printf("该账号已存在，请重新输入\n");
            continue;
        }
        break;
    }

    // 输入欲添加的密码
    char password_input[99] = { 0 };
    printf("请输入密码：\n");
    printf("密码长度在5-20之间，仅由半角的数字、大小写字母、连接线或下划线组成。\n");
    while (1) {
        HiddenInput(password_input, 98);

        // 验证密码合法性
        int rob = PasswordRobustness(password_input);
        if (rob == 15) {
            printf("密码太短，请重新输入：\n");
            continue;
        } else if (rob == 120) {
            printf("密码太长，请重新输入：\n");
            continue;
        } else if (rob == -1) {
            printf("密码应仅含半角的数字、大小写字母、连接线或下划线。\n");
            printf("请重新输入：\n");
            continue;
        } else if (rob <= 2) {
            printf("密码过于简单，请重新输入：\n");
            continue;
        }

        // 确认密码
        char password_verify[99] = { 0 };
        printf("请再次输入密码以确认：\n");
        HiddenInput(password_verify, 98);
        if (strcmp(password_input, password_verify) != 0) {
            printf("两次输入的密码不一致！请重新输入密码：\n");
            continue;
        }
        break;
    }

    // 存储账号和密码的哈希值
    FILE* account = fopen("Account.dat", "a");
    char password_hash[99] = { 0 };
    sha256(password_input, strlen(password_input), password_hash);
    fprintf(account, "%s %s\n", username_input, password_hash);
    printf("添加成功！\n");
    fclose(account);

    PressQToGoBack(Account);
    return 0;
}