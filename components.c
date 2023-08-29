#include "FilmSystem.h"

char USER[99] = "";
UserDataT ThisUser = { 0 };
UserDataT user_data_arr[100] = { 0 };
const int ExitAndGoBack = -1;

void gotoxy(int x, int y) {
    COORD pos = { x, y };
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOut, pos);
}

void SplitLine() {
    printf("===================================\n");
}
int GoBack() {
    return 0;
}
char GetCharIn(char* str) {
    char tmp = 0;
    while (1) {
        tmp = getch();
        for (int i = 0; str[i] != 0; i++) {
            if (tmp == str[i]) {
                return tmp;
            }
        }
    }
    return 0;
}

int Exit() {
    printf("输入q确认退出系统：");

    char temp[99] = "";
    scanf("%s", &temp);

    if (strcmp(temp, "q") == 0) {
        exit(0);
    }

    return 0; // 取消退出登录
}

int GoBackToLogin() {
    printf("输入q确认退出登录：");

    char temp[99] = "";
    scanf("%s", &temp);

    if (strcmp(temp, "q") == 0) {
        return ExitAndGoBack;
    }

    return 0; // 取消退出登录
}

long long GetInteger(long long min, long long max) {
    /* min、max 为输入范围，左闭右开 */
    long long integer = 0;
    while (1) {
        scanf("%*c");
        if (scanf("%lld", &integer) != 1) {
            printf("请输入数字！\n");
        } else if (integer < min) {
            printf("请输入大于或等于 %lld 的数！\n", min);
        } else if (integer >= max) {
            printf("请输入小于 %lld 的数！\n", max);
        } else {
            break;
        }
    }
    return integer;
}

int GetUserOrder(int choiceNum, int (*functions[])(void)) {
    int choice = 0;
    char choice_char = 0;

    printf("按下对应数字键以选择功能。\n");
    while (choice_char < '1' || choice_char > choiceNum + '0') {
        choice_char = getch();
    }
    choice = choice_char - '1';

    if (functions[choice] == GoBack
        || functions[choice] == GoBackToLogin) {
        return ExitAndGoBack;
    }

    functions[choice]();
    return 0;
}

int PressQToGoBack() {
    printf("按下q返回：");
    while (getch() != 'q');

    return 0;
}

int HiddenInput(char* destination, int limit) {
    /*
       实现用户输入的字符以`*`回显。
       接受：
       一个字符串指针以存储用户输入；
       一个整型以限制用户最大输入长度。
    */
    int i = 0;
    while (1) {
        char temp = (char)getch();
        if (temp == '\r') {
            printf("\n");
            break;
        } else if (temp == '\b') {
            if (i > 0) {
                printf("\b \b");
                i--;
            }
        } else if (temp == 3) {
            exit(0);
        } else {
            printf("*");
            destination[i++] = temp;
        }

        if (i > limit) {
            break;
        }
    }
    return 0;
}

void ResetUserDataArr() {
    for (int i = 0; i < 500; i++) {
        user_data_arr[i] = (UserDataT){ 0 };
    }
};

int ReadThisUserData(char* username) {
    FILE* user_data = fopen("UserData.dat", "rb");
    if (user_data == NULL) {
        printf("错误：文件打开失败！\n");
        fclose(user_data);
        return -2;
    }

    // 从文件读取放映信息
    for (int i = 0; i < 999; i++) {
        fread(&ThisUser, sizeof(UserDataT), 1, user_data);
        if (strcmp(ThisUser.username, username) == 0) {
            return 0;
        } else if (feof(user_data)) {
            return -1;
            break;
        }
    }
    return -3;
}

int ReadUserData() {
    FILE* user_data = fopen("UserData.dat", "rb");
    if (user_data == NULL) {
        printf("错误：文件打开失败！\n");
        fclose(user_data);
        return 0;
    }

    // 从文件读取放映信息
    for (int i = 0; i < 999; i++) {
        fread(user_data_arr + i, sizeof(UserDataT), 1, user_data);
        if (feof(user_data)) {
            break;
        }
    }
    return 0;
};

int WriteUserData(UserDataT info, FILE* user_data) {
    fwrite(&info, sizeof(UserDataT), 1, user_data);
    return 0;
};

// int PrintFilmInfo(FilmInfoT info) {
//     printf("放映编号: %d\n", info.id);
//     printf("电影名称: %s\n", info.name);
//     printf("电影类型: %s\n", info.type);
//     printf("时长: %d\n", info.length);
//     printf("场次: \n");
//     for (int i = 0; info.sessions[i].time.year != 0; i++) {
//         printf("[%d] ", i + 1);
//         printf("%4hd年%2hd月%2hd日 %2hd:%2hd",
//             info.sessions[i].time.year,
//             info.sessions[i].time.month,
//             info.sessions[i].time.day,
//             info.sessions[i].time.hour,
//             info.sessions[i].time.minute);
//         printf("%4d号厅", info.sessions[i].hall);
//         printf("%7.2f元", info.sessions[i].price);
//         printf("  余票%2d张\n", info.sessions[i].ticket_num);
//     }
//     return 0;
// }