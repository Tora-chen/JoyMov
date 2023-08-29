#include "FilmSystem.h"

FilmInfoT film_info_arr[500] = { 0 };
const char FilmBaseFileName[] = "movie_base.dat";
int (*FilmInfoFunc[20])(void) = {
    ViewFilmInfo, AddFilmInfo, DeleteFilmInfo, ModifyFilmInfo, GoBack
};

int FilmInfo() {
    while (1) {
        int index = 1;
        system("cls");
        printf("===================================================== \n");
        printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ \n");
        printf("                     ��Ӱ��ӳ��Ϣ����   \n");
        printf("    %d. ��ʾ������ӳ��Ӱ \n", index++);
        printf("    %d. ��ӵ�Ӱ\n", index++);
        printf("    %d. ɾ����Ӱ\n", index++);
        printf("    %d. �޸ĵ�Ӱ��Ϣ\n", index++);
        printf("    %d. ���� \n", index);
        printf("===================================================== \n");

        if (GetUserOrder(5, FilmInfoFunc) == ExitAndGoBack) {
            break;
        };
    }
    return 0;
};

void ResetFilmInfoArr() {
    for (int i = 0; i < 500; i++) {
        film_info_arr[i] = (FilmInfoT){ 0 };
    }
};

int ReadFilmInfo() {
    FILE* FilmBase = fopen(FilmBaseFileName, "rb");
    if (FilmBase == NULL) {
        printf("�����ļ���ʧ�ܣ�\n");
        fclose(FilmBase);
        return 0;
    }

    // ���ļ���ȡ��ӳ��Ϣ
    for (int i = 0; i < 999; i++) {
        fread(film_info_arr + i, sizeof(FilmInfoT), 1, FilmBase);
        if (feof(FilmBase)) {
            break;
        }
    }
    return 0;
};

int WriteFilmInfo(FilmInfoT info, FILE* FilmBase) {
    fwrite(&info, sizeof(FilmInfoT), 1, FilmBase);
    return 0;
};

int PrintFilmInfo(FilmInfoT info) {
    printf("��ӳ���: %d\n", info.id);
    printf("��Ӱ����: %s\n", info.name);
    printf("��Ӱ����: %s\n", info.type);
    printf("ʱ��: %d\n", info.length);
    printf("����: \n");
    for (int i = 0; info.sessions[i].time.year != 0; i++) {
        printf("[%d] ", i + 1);
        printf("%4hd��%2hd��%2hd�� %2hd:%2hd",
            info.sessions[i].time.year,
            info.sessions[i].time.month,
            info.sessions[i].time.day,
            info.sessions[i].time.hour,
            info.sessions[i].time.minute);
        printf("%4d����", info.sessions[i].hall);
        printf("%7.2fԪ", info.sessions[i].price);
        printf("  ��Ʊ%2d��\n", info.sessions[i].ticket_num);
    }
    return 0;
}

int ViewFilmInfo() {
    // ��ȡ��Ӱ��Ϣ
    ResetFilmInfoArr();
    ReadFilmInfo();

    // �����ӳ��Ϣ
    int looking = 0;
    int info_num = 0; // �����ж�������ӳ��Ϣ
    for (int i = 0; i < 999; i++) {
        if (film_info_arr[i].id == 0) {
            info_num = i;
            break;
        }
    }

    if (info_num == 0) {
        system("cls");
        printf("===================================================== \n\n");
        printf("                     ����տ���Ҳ -_- \n\n");
        printf("===================================================== \n");
        printf("  Q: �˳�\n");
        while (getch() != 'q');
        return 0;
    }

    while (1) {
        system("cls");
        printf("==================== %03d/%03d ======================== \n\n",
            looking + 1, info_num);
        PrintFilmInfo(film_info_arr[looking]);
        printf("\n===================================================== \n");
        printf(" J: ��һ��            L: ��һ��            Q: �˳�\n");

        while (1) {
            char c = getch();
            if (c == 'j' && looking != 0) {
                looking--;
                break;
            } else if (c == 'l' && film_info_arr[looking + 1].id != 0) {
                looking++;
                break;
            } else if (c == 'q') {
                return 0;
            }
        }
    }

    ResetFilmInfoArr();
    return 0;
}

int AddFilmInfo() {
    // �û������Ӱ��Ϣ
    FilmInfoT info = { 0 };
    system("cls");
    printf("��ӳ��ţ�");
    while (1) {
        info.id = GetInteger(1, 999999);

        ResetFilmInfoArr();
        ReadFilmInfo();

        int flag = 0;
        for (int i = 0; film_info_arr[i].id != 0; i++) {
            if (film_info_arr[i].id == info.id) {
                printf("�ñ���Ѵ��ڣ�����������: ");
                flag = 1;
                break;
            }
        }

        if (!flag) {
            break;
        }
    }

    printf("��Ӱ����: ");
    scanf("%*c");
    scanf("%s", info.name);
    printf("��Ӱ����: ");
    scanf("%*c");
    scanf("%s", info.type);

    printf("ʱ����");
    info.length = GetInteger(0, 9999);

    printf("����\n");
    printf(" (��ʽ: ��-��-��-ʱ:�� Ӱ�� Ʊ�� ��Ʊ��, ���롰e������): \n");
    for (int i = 0; i < 49;) {
        scanf("%*c");
        if (scanf("%hd-%hd-%hd-%hd:%hd %hd %f %hd",
            &info.sessions[i].time.year,
            &info.sessions[i].time.month,
            &info.sessions[i].time.day,
            &info.sessions[i].time.hour,
            &info.sessions[i].time.minute,
            &info.sessions[i].hall,
            &info.sessions[i].price,
            &info.sessions[i].ticket_num) == 8) {
            i++;
        } else if (getchar() == 'e') {
            break;
        } else {
            printf("��ʽ�������������룺\n");
        }
    }

    // д���Ӱ��Ϣ
    FILE* FilmBase = fopen(FilmBaseFileName, "ab");
    WriteFilmInfo(info, FilmBase);
    fclose(FilmBase);
    printf("д��ɹ���\n");

    // �����ϼ�����
    ResetFilmInfoArr();
    PressQToGoBack();
    return 0;
}

int DeleteFilmInfo() {
    ResetFilmInfoArr();
    ReadFilmInfo();

    system("cls");
    printf("������Ҫɾ���ĵ�Ӱ��ӳ��ţ�\n");
    unsigned int id = 0;
    scanf("%ld", &id);

    // ���ҵ�Ӱ���
    int index = -1;
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        if (film_info_arr[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("δ�ҵ��õ�Ӱ��\n");
        PressQToGoBack();
        return 0;
    }

    // ��ӡԭ��Ӱ��Ϣ
    printf("��Ҫɾ���ĵ�Ӱ��ϢΪ��\n");
    printf("===================================\n");
    PrintFilmInfo(film_info_arr[index]);
    printf("===================================\n");

    // ȷ��ɾ��
    scanf("%*c");
    printf("����yȷ��ɾ����");
    if (getchar() != 'y') {
        printf("ȡ��ɾ��\n");
        PressQToGoBack();
        return 0;
    }

    // ����д���Ӱ��Ϣ
    FILE* FilmBase = fopen("movie_base.dat", "wb+");
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        if (i == index) {
            continue;
        }
        WriteFilmInfo(film_info_arr[i], FilmBase);
    }
    fclose(FilmBase);

    printf("ɾ����ϣ�\n");
    PressQToGoBack();

    return 0;
}

int ModifyFilmInfo() {
    ResetFilmInfoArr();
    ReadFilmInfo();

    system("cls");
    printf("������Ҫ�޸ĵĵ�Ӱ��ӳ��ţ�\n");
    int id = GetInteger(1, INT_MAX);
    int index = FindFilmInfoIndex(id);

    // ��ӡԭ��Ӱ��Ϣ
    printf("===================================\n");
    PrintFilmInfo(film_info_arr[index]);
    printf("===================================\n");

    // ��������Ϣ
    FilmInfoT info = { 0 };
    printf("�����޸ĺ����Ϣ: \n");
    printf("��ӳ���: ");
    while (1) {
        info.id = GetInteger(1, 999999);

        ResetFilmInfoArr();
        ReadFilmInfo();

        if (FindFilmInfoIndex(info.id) != -1) {
            printf("�ñ���Ѵ��ڣ�����������: ");
        } else {
            break;
        }
    }

    printf("��Ӱ����: ");
    scanf("%*c");
    scanf("%s", info.name);
    printf("��Ӱ����: ");
    scanf("%*c");
    scanf("%s", info.type);

    printf("ʱ����");
    info.length = GetInteger(0, 9999);

    printf("����\n");
    printf(" (��ʽ: ��-��-��-ʱ:�� Ӱ�� Ʊ�� ��Ʊ��, ���롰e������): \n");
    for (int i = 0; i < 49;) {
        scanf("%*c");
        if (scanf("%hd-%hd-%hd-%hd:%hd %hd %f %hd",
            &info.sessions[i].time.year,
            &info.sessions[i].time.month,
            &info.sessions[i].time.day,
            &info.sessions[i].time.hour,
            &info.sessions[i].time.minute,
            &info.sessions[i].hall,
            &info.sessions[i].price,
            &info.sessions[i].ticket_num) == 8) {
            i++;
        } else if (getchar() == 'e') {
            break;
        } else {
            printf("��ʽ�������������룺\n");
        }
    }

    // �޸���Ϣ
    film_info_arr[index] = info;

    // д����Ϣ
    FILE* FilmBase = fopen("movie_base.dat", "wb+");
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        WriteFilmInfo(film_info_arr[i], FilmBase);
    }
    fclose(FilmBase);

    PressQToGoBack();
    return 0;
}

int FindFilmInfoIndex(int id) {
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        if (film_info_arr[i].id == id) {
            return i;
        }
    }
    return -1;
}

int GetRemainTicketNum(int index, int session) {
    int num = 0;
    for (int i = 0; i < film_info_arr[index].sessions[session].ticket_num; i++) {
        if (film_info_arr[index].sessions[session].seat_status[i] == 0) {
            num++;
        }
    }
    return num;
}