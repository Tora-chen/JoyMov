#include "FilmSystem.h"
int Search() {
    while (1) {
        system("cls");
        printf("===================================================== \n");
        printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ \n");
        printf("                        ��ѯ����   \n");
        printf("    1. ��������ѯ��Ӱ��ӳ��Ϣ \n");
        printf("    2. ��������ѯ������Ϣ\n");
        printf("    3. ����\n");
        printf("===================================================== \n");

        // int (*functions[20])(void) = {
        //     SearchFilmInfo, SearchDealInfo, GoBack
        // }; // Temply

        int (*functions[20])(void) = {
            GoBack, GoBack, GoBack
        };
        if (GetUserOrder(3, functions) == ExitAndGoBack) {
            break;
        };
    }

    return 0;
};

// int SearchFilmInfo() {
//     while (1) {
//         system("cls");
//         int index = 1;
//         printf("%d. ����ӳ��Ų�ѯ\n", index++);
//         printf("%d. ����Ӱ���Ʋ�ѯ\n", index++);
//         printf("%d. ����Ӱ���Ͳ�ѯ\n", index++);
//         printf("%d. ����ӳ��ʼ���ڲ�ѯ\n", index++);
//         printf("%d. ����ӳ�������ڲ�ѯ\n", index++);
//         printf("%d. ����ӳӰ����ѯ\n", index++);
//         printf("%d. ��Ʊ�۲�ѯ\n", index++);
//         printf("%d. ����Ʊ��ѯ\n", index++);
//         printf("%d. ����\n", index);

//         int (*functions[20])(void) = {
//             SearchFilmInfoById, SearchFilmInfoByName, SearchFilmInfoByType,
//             SearchFilmInfoByDateBegin, SearchFilmInfoByDateEnd,
//             SearchFilmInfoByMovieHall, SearchFilmInfoByTicketPrice,
//             SearchFilmInfoByTicketNum, GoBack
//         };
//         if (GetUserOrder(index, functions) == ExitAndGoBack) {
//             break;
//         }
//     }
//     return 0;
// }

// int SearchFilmInfoById() {
//     system("cls");
//     printf("�������ӳ��ţ�\n");
//     long long id_input = 0;
//     scanf("%lld", &id_input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("��ѯ�����\n");
//     printf("===================================\n");
//     int isNoRes = 1;
//     for (int i = 0; info[i].id != 0; i++) {
//         if (info[i].id == id_input) {
//             PrintFilmInfo(info[i]);
//             isNoRes = 0;
//             printf("===================================\n");
//         }
//     }
//     if (isNoRes) {
//         printf("û�в�ѯ�����\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByName() {
//     system("cls");
//     printf("�������Ӱ���ƣ�\n");
//     wchar_t name_input[99] = { 0 };
//     wscanf(L"%s", name_input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("��ѯ�����\n");
//     printf("===================================\n");
//     int isNoRes = 1;
//     for (int i = 0; info[i].id != 0; i++) {
//         if (wcscmp(info[i].name, name_input) == 0) {
//             PrintFilmInfo(info[i]);
//             isNoRes = 0;
//             printf("===================================\n");
//         }
//     }
//     if (isNoRes) {
//         printf("û�в�ѯ�����\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByType() {
//     system("cls");
//     printf("�������Ӱ���ͣ�\n");
//     wchar_t input[99] = L"\0";
//     wscanf(L"%s", input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("��ѯ�����\n");
//     printf("===================================\n");
//     int isNoRes = 1;
//     for (int i = 0; info[i].id != 0; i++) {
//         if (wcscmp(info[i].type, input) == 0) {
//             PrintFilmInfo(info[i]);
//             isNoRes = 0;
//             printf("===================================\n");
//         }
//     }
//     if (isNoRes) {
//         printf("û�в�ѯ�����\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByDateBegin() {
//     system("cls");
//     printf("�������ӳ��ʼ���ڣ�\n");
//     wchar_t input[99] = L"\0";
//     wscanf(L"%s", input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("��ѯ�����\n");
//     printf("===================================\n");
//     int isNoRes = 1;
//     for (int i = 0; info[i].id != 0; i++) {
//         if (wcscmp(info[i].date_begin, input) == 0) {
//             PrintFilmInfo(info[i]);
//             isNoRes = 0;
//             printf("===================================\n");
//         }
//     }
//     if (isNoRes) {
//         printf("û�в�ѯ�����\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByDateEnd() {
//     system("cls");
//     printf("�������Ӱ���ͣ�\n");
//     wchar_t input[99] = L"\0";
//     wscanf(L"%s", input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("��ѯ�����\n");
//     printf("===================================\n");
//     int isNoRes = 1;
//     for (int i = 0; info[i].id != 0; i++) {
//         if (wcscmp(info[i].date_end, input) == 0) {
//             PrintFilmInfo(info[i]);
//             isNoRes = 0;
//             printf("===================================\n");
//         }
//     }
//     if (isNoRes) {
//         printf("û�в�ѯ�����\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByMovieHall() {
//     system("cls");
//     printf("�������ӳӰ����\n");
//     long long input = 0;
//     scanf("%lld", &input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("��ѯ�����\n");
//     printf("===================================\n");
//     int isNoRes = 1;
//     for (int i = 0; info[i].id != 0; i++) {
//         if (info[i].movie_hall = input) {
//             PrintFilmInfo(info[i]);
//             isNoRes = 0;
//             printf("===================================\n");
//         }
//     }
//     if (isNoRes) {
//         printf("û�в�ѯ�����\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByTicketPrice() {
//     system("cls");
//     printf("������Ʊ�ۣ�\n");
//     float input = 0;
//     scanf("%f", &input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("��ѯ�����\n");
//     printf("===================================\n");
//     int isNoRes = 1;
//     for (int i = 0; info[i].id != 0; i++) {
//         if (info[i].ticket_price = input) {
//             PrintFilmInfo(info[i]);
//             isNoRes = 0;
//             printf("===================================\n");
//         }
//     }
//     if (isNoRes) {
//         printf("û�в�ѯ�����\n");
//     }

//     PressQToGoBack();
// }

// int SearchFilmInfoByTicketNum() {
//     system("cls");
//     printf("��������Ʊ������\n");
//     long long input = 0;
//     scanf("%f", &input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("��ѯ�����\n");
//     printf("===================================\n");
//     int isNoRes = 1;
//     for (int i = 0; info[i].id != 0; i++) {
//         if (info[i].ticket_num = input) {
//             PrintFilmInfo(info[i]);
//             isNoRes = 0;
//             printf("===================================\n");
//         }
//     }
//     if (isNoRes) {
//         printf("û�в�ѯ�����\n");
//     }

//     PressQToGoBack();
//     return 0;
// }

// int SearchDealInfo() {
//     PressQToGoBack();
//     return 0;
// }