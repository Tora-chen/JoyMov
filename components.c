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
    printf("����qȷ���˳�ϵͳ��");

    char temp[99] = "";
    scanf("%s", &temp);

    if (strcmp(temp, "q") == 0) {
        exit(0);
    }

    return 0; // ȡ���˳���¼
}

int GoBackToLogin() {
    printf("����qȷ���˳���¼��");

    char temp[99] = "";
    scanf("%s", &temp);

    if (strcmp(temp, "q") == 0) {
        return ExitAndGoBack;
    }

    return 0; // ȡ���˳���¼
}

long long GetInteger(long long min, long long max) {
    /* min��max Ϊ���뷶Χ������ҿ� */
    long long integer = 0;
    while (1) {
        scanf("%*c");
        if (scanf("%lld", &integer) != 1) {
            printf("���������֣�\n");
        } else if (integer < min) {
            printf("��������ڻ���� %lld ������\n", min);
        } else if (integer >= max) {
            printf("������С�� %lld ������\n", max);
        } else {
            break;
        }
    }
    return integer;
}

int GetUserOrder(int choiceNum, int (*functions[])(void)) {
    int choice = 0;
    char choice_char = 0;

    printf("���¶�Ӧ���ּ���ѡ���ܡ�\n");
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
    printf("����q���أ�");
    while (getch() != 'q');

    return 0;
}

int HiddenInput(char* destination, int limit) {
    /*
       ʵ���û�������ַ���`*`���ԡ�
       ���ܣ�
       һ���ַ���ָ���Դ洢�û����룻
       һ�������������û�������볤�ȡ�
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
        printf("�����ļ���ʧ�ܣ�\n");
        fclose(user_data);
        return -2;
    }

    // ���ļ���ȡ��ӳ��Ϣ
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
        printf("�����ļ���ʧ�ܣ�\n");
        fclose(user_data);
        return 0;
    }

    // ���ļ���ȡ��ӳ��Ϣ
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
//     printf("��ӳ���: %d\n", info.id);
//     printf("��Ӱ����: %s\n", info.name);
//     printf("��Ӱ����: %s\n", info.type);
//     printf("ʱ��: %d\n", info.length);
//     printf("����: \n");
//     for (int i = 0; info.sessions[i].time.year != 0; i++) {
//         printf("[%d] ", i + 1);
//         printf("%4hd��%2hd��%2hd�� %2hd:%2hd",
//             info.sessions[i].time.year,
//             info.sessions[i].time.month,
//             info.sessions[i].time.day,
//             info.sessions[i].time.hour,
//             info.sessions[i].time.minute);
//         printf("%4d����", info.sessions[i].hall);
//         printf("%7.2fԪ", info.sessions[i].price);
//         printf("  ��Ʊ%2d��\n", info.sessions[i].ticket_num);
//     }
//     return 0;
// }