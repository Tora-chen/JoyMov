#include "FilmSystem.h"

int (*Accountfunc[20])(void) = {
    ViewAccounts, ModifyUserName, ModifyPassword,
    DeleteAccount, AddAccount, GoBack
};

int Account() {
    while (1) {
        system("cls");
        printf("===================================================== \n");
        printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ \n");
        printf("                       �˺Ź���   \n");
        printf("    1. ��ʾ�����˺� \n");
        printf("    2. �޸��û���\n");
        printf("    3. �޸����� \n");
        printf("    4. ɾ���˺� \n");
        printf("    5. ����˺� \n");
        printf("    6. ���� \n");
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
    printf("�����˺ţ�\n");

    AccountT accounts[999] = { 0 };
    ReadAccountInfo(accounts);
    for (int i = 0; accounts[i].username[0] != 0; i++) {
        printf("%s\n", accounts[i].username);
    }
    printf("��ʾ��ϣ�\n");

    PressQToGoBack();
    return 0;
}

int DeleteAccount() {
    AccountT accounts[999] = { 0 };
    ReadAccountInfo(accounts);

    // ����Ҫɾ�����˺�
    char username_input[99] = { 0 };
    system("cls");
    printf("������Ҫɾ�����˺ţ�\n");
    int index = -1; // ��¼Ҫɾ�����˺ŵ��±�
    while (1) {
        scanf("%99s", username_input);

        // Ѱ���˺�
        for (int i = 0; accounts[i].username[0] != 0; i++) {
            if (strcmp(accounts[i].username, username_input) == 0) {
                index = i;
                break;
            }
        }
        if (index != -1) {
            break;
        }

        printf("û�и��˺ţ����������룺\n");
    }

    // ȷ��ɾ��
    getchar();
    printf("����yȷ��ɾ���˺�\"%s\": ", accounts[index].username);
    if (getchar() != 'y') {
        printf("ȡ��ɾ��\n");
        GoBack(Account);
        return 0;
    }

    // ����д���˺���Ϣ
    FILE* account_file = fopen("Account.dat", "w+");
    for (int i = 0; accounts[i].username[0] != 0; i++) {
        if (i == index) {
            continue;
        }
        fprintf(account_file, "%s %s\n", accounts[i].username, accounts[i].password_hash);
    }
    fclose(account_file);

    printf("ɾ����ϣ�\n");
    PressQToGoBack(Account);

    return 0;
}

int ModifyUserName() {
    system("cls");
    if (strcmp(USER, "root") == 0) {
        printf("root�˺Ų������޸��û�����\n");
        PressQToGoBack(Account);
        return 0;
    }
    // �������û���
    AccountT accounts[99] = { 0 };
    ReadAccountInfo(accounts);

    char newUsername[99] = { 0 };
    printf("�����µ��û�����\n");
    printf("�˺ų��Ȳ�����20�����ɰ�ǵ����֡���Сд��ĸ�������߻��»�����ɡ�\n");
    while (1) {
        scanf("%99s", newUsername);

        // ��֤�ַ����Ϸ���
        int rob = PasswordRobustness(newUsername);
        if (rob == 120) {
            printf("�˺�̫�������������룺\n");
            continue;
        } else if (rob == -1) {
            printf("�˺�Ӧ������ǵ����֡���Сд��ĸ�������߻��»��ߡ�\n");
            printf("���������룺\n");
            continue;
        }

        // ȷ���Ƿ����ظ��û���
        if (FindAccount(newUsername) == -1) {
            break;
        }
        printf("���˺��Ѵ��ڣ�����������\n");
    }

    // �޸��û���
    int account_index = FindAccount(USER);
    strcpy(accounts[account_index].username, newUsername);
    strcpy(USER, newUsername);

    // ����д���˺���Ϣ
    RewriteAccountInfo(accounts);

    printf("�޸ĳɹ���\n");
    PressQToGoBack(Account);
    return 0;
}

int ModifyPassword() {
    // ��������
    AccountT accounts[99] = { 0 };
    ReadAccountInfo(accounts);

    char newPassword[99] = { 0 };
    system("cls");
    printf("�����µ����룺\n");
    printf("���볤����5-20֮�䣬���ɰ�ǵ����֡���Сд��ĸ��\n");
    printf("�����߻��»���������������������ɡ�\n");
    while (1) {
        HiddenInput(newPassword, 98);

        // ��֤����Ϸ���
        int rob = PasswordRobustness(newPassword);
        if (rob == 15) {
            printf("����̫�̣����������룺\n");
            continue;
        } else if (rob == 120) {
            printf("����̫�������������룺\n");
            continue;
        } else if (rob == -1) {
            printf("����Ӧ������ǵ����֡���Сд��ĸ�������߻��»��ߡ�\n");
            printf("���������룺\n");
            continue;
        } else if (rob <= 2) {
            printf("������ڼ򵥣����������룺\n");
            continue;
        }

        // ȷ������
        char password_verify[99] = { 0 };
        printf("���ٴ�����������ȷ�ϣ�\n");
        HiddenInput(password_verify, 98);
        if (strcmp(newPassword, password_verify) == 0) {
            break;
        }
        printf("������������벻һ�£��������������룺\n");
    }
    int account_index = FindAccount(USER);
    sha256(newPassword, strlen(newPassword),
        accounts[account_index].password_hash);

    RewriteAccountInfo(accounts);

    printf("�޸ĳɹ���\n");
    PressQToGoBack(Account);
}

int PasswordRobustness(char str[]) {
    /* ��������һ���ַ������Դ�д��ĸ��Сд��ĸ�����֡������ĸ�ָ�������ַ������Ӷ�
    ���ַ�������5�ַ�������15�����ַ�������20�ַ�������120��
    ���ַ������а�ǵ����֡���Сд��ĸ�������ߺ��»���������ַ�������-1��
    ����������������������ַ������Ӷȣ���ΧΪ1-4��*/
    struct robustnessT {
        int lower;
        int capital;
        int num;
        int length;
    } rob = { 0, 0, 0, 0 };

    // ����ַ�������
    if (strlen(str) < 5) {
        return 15;
    } else if (strlen(str) > 20) {
        return 120;
    } else if (strlen(str) >= 10) {
        rob.length = 1;
    }

    // �������ַ�
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

    // �������븴�ӳ̶�
    return rob.lower + rob.length + rob.capital + rob.num;
}
int AddAccount() {
    // ��������ӵ��˺�
    char username_input[99] = { 0 };
    system("cls");
    printf("�����µ��˺ţ�\n");
    printf("�˺ų��Ȳ�����20�����ɰ�ǵ����֡���Сд��ĸ�������߻��»�����ɡ�\n");
    while (1) {
        scanf("%99s", username_input);

        // ��֤�ַ����Ϸ���
        int rob = PasswordRobustness(username_input);
        if (rob == 120) {
            printf("�˺�̫�������������룺\n");
            continue;
        } else if (rob == -1) {
            printf("�˺�Ӧ������ǵ����֡���Сд��ĸ�������߻��»��ߡ�\n");
            printf("���������룺\n");
            continue;
        }

        // ȷ���Ƿ����ظ��˺�
        if (FindAccount(username_input) != -1) {
            printf("���˺��Ѵ��ڣ�����������\n");
            continue;
        }
        break;
    }

    // ��������ӵ�����
    char password_input[99] = { 0 };
    printf("���������룺\n");
    printf("���볤����5-20֮�䣬���ɰ�ǵ����֡���Сд��ĸ�������߻��»�����ɡ�\n");
    while (1) {
        HiddenInput(password_input, 98);

        // ��֤����Ϸ���
        int rob = PasswordRobustness(password_input);
        if (rob == 15) {
            printf("����̫�̣����������룺\n");
            continue;
        } else if (rob == 120) {
            printf("����̫�������������룺\n");
            continue;
        } else if (rob == -1) {
            printf("����Ӧ������ǵ����֡���Сд��ĸ�������߻��»��ߡ�\n");
            printf("���������룺\n");
            continue;
        } else if (rob <= 2) {
            printf("������ڼ򵥣����������룺\n");
            continue;
        }

        // ȷ������
        char password_verify[99] = { 0 };
        printf("���ٴ�����������ȷ�ϣ�\n");
        HiddenInput(password_verify, 98);
        if (strcmp(password_input, password_verify) != 0) {
            printf("������������벻һ�£��������������룺\n");
            continue;
        }
        break;
    }

    // �洢�˺ź�����Ĺ�ϣֵ
    FILE* account = fopen("Account.dat", "a");
    char password_hash[99] = { 0 };
    sha256(password_input, strlen(password_input), password_hash);
    fprintf(account, "%s %s\n", username_input, password_hash);
    printf("��ӳɹ���\n");
    fclose(account);

    PressQToGoBack(Account);
    return 0;
}