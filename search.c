#include "FilmSystem.h"
int Search() {
    while (1) {
        system("cls");
        printf("===================================================== \n");
        printf("                   欢迎使用电影购票系统 \n");
        printf("                        查询管理   \n");
        printf("    1. 按条件查询电影放映信息 \n");
        printf("    2. 按条件查询交易信息\n");
        printf("    3. 返回\n");
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
//         printf("%d. 按放映编号查询\n", index++);
//         printf("%d. 按电影名称查询\n", index++);
//         printf("%d. 按电影类型查询\n", index++);
//         printf("%d. 按放映开始日期查询\n", index++);
//         printf("%d. 按放映结束日期查询\n", index++);
//         printf("%d. 按放映影厅查询\n", index++);
//         printf("%d. 按票价查询\n", index++);
//         printf("%d. 按余票查询\n", index++);
//         printf("%d. 返回\n", index);

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
//     printf("请输入放映编号：\n");
//     long long id_input = 0;
//     scanf("%lld", &id_input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("查询结果：\n");
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
//         printf("没有查询到结果\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByName() {
//     system("cls");
//     printf("请输入电影名称：\n");
//     wchar_t name_input[99] = { 0 };
//     wscanf(L"%s", name_input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("查询结果：\n");
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
//         printf("没有查询到结果\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByType() {
//     system("cls");
//     printf("请输入电影类型：\n");
//     wchar_t input[99] = L"\0";
//     wscanf(L"%s", input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("查询结果：\n");
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
//         printf("没有查询到结果\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByDateBegin() {
//     system("cls");
//     printf("请输入放映开始日期：\n");
//     wchar_t input[99] = L"\0";
//     wscanf(L"%s", input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("查询结果：\n");
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
//         printf("没有查询到结果\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByDateEnd() {
//     system("cls");
//     printf("请输入电影类型：\n");
//     wchar_t input[99] = L"\0";
//     wscanf(L"%s", input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("查询结果：\n");
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
//         printf("没有查询到结果\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByMovieHall() {
//     system("cls");
//     printf("请输入放映影厅：\n");
//     long long input = 0;
//     scanf("%lld", &input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("查询结果：\n");
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
//         printf("没有查询到结果\n");
//     }

//     PressQToGoBack();
//     return 0;
// }
// int SearchFilmInfoByTicketPrice() {
//     system("cls");
//     printf("请输入票价：\n");
//     float input = 0;
//     scanf("%f", &input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("查询结果：\n");
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
//         printf("没有查询到结果\n");
//     }

//     PressQToGoBack();
// }

// int SearchFilmInfoByTicketNum() {
//     system("cls");
//     printf("请输入余票数量：\n");
//     long long input = 0;
//     scanf("%f", &input);

//     FilmInfoT info[999] = { 0 };
//     ReadFilmInfo(info);

//     printf("查询结果：\n");
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
//         printf("没有查询到结果\n");
//     }

//     PressQToGoBack();
//     return 0;
// }

// int SearchDealInfo() {
//     PressQToGoBack();
//     return 0;
// }