#include "FilmSystem.h"

int Login() {
    system("cls");
    printf("=====================================================\n");
    printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ                \n");
    printf("                         ��¼����                     \n");
    printf("=====================================================\n");

    char username[99] = { 0 };
    char password[99] = { 0 };
    char username_input[99] = { 0 };
    char password_input[99] = { 0 };

    // �����û���
    printf("�������û�����\n");
    while (1) {
        scanf("%99s", username_input);

        // �ж��û����Ƿ����
        if (FindAccount(username_input) != -1) {
            break;
        }

        printf("�û��������ڣ����������룺\n");
    }

    // �����ȡ����
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

    // ��������
    char hash[99] = { 0 };
    printf("���������룺\n");
    while (1) {
        // ʵ����������
        HiddenInput(password_input, 98);

        sha256(password_input, strlen(password_input), hash);

        // ��֤����
        if (strcmp(password, hash) == 0) {
            break;
        }
        printf("����������������룺\n");
    }

    // ��¼�ɹ�����¼�û���ݣ�����������
    printf("��¼�ɹ���");
    strcpy(USER, username_input);
    if (strcmp(USER, "root") == 0) {
        Home();
    } else {
        HomeForCustomer();
    }

    return 0;
}