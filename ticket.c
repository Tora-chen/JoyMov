#include "FilmSystem.h"
int Ticket() {
    while (1) {
        int index = 1;
        system("cls");
        printf("===================================================== \n");
        printf("                   欢迎使用电影购票系统 \n");
        printf("                        票务管理  \n");
        printf("    %d. 购票\n", index++);
        printf("    %d. 退票\n", index++);
        printf("    %d. 返回 \n", index);
        printf("===================================================== \n");

        int (*functions[20])(void) = {
            BuyTicket, RefundTicket, GoBack
        };
        if (GetUserOrder(3, functions) == -1) {
            break;
        }
    }

    return 0;
};

int BuyTicket() {
    ResetFilmInfoArr();
    ReadFilmInfo();

    // 输入欲购买电影的放映编号
    printf("请输入欲购买电影的放映编号：\n");
    int id_buying = 0;
    int info_index_buying = -1;
    while (1) {
        id_buying = GetInteger(1, INT_MAX);
        info_index_buying = FindFilmInfoIndex(id_buying);
        if (info_index_buying == -1) {
            printf("未找到该电影！\n");
            printf("请重新输入：\n");
        } else {
            break;
        }
    }

    // 选择场次
    PrintFilmInfo(film_info_arr[info_index_buying]);
    SplitLine();
    int session_buying;
    while (1) {
        printf("请选择场次：");
        session_buying = GetInteger(1, INT_MAX) - 1;
        if (film_info_arr[info_index_buying].
            sessions[session_buying].time.year == 0) {
            printf("未找到该场次！\n");
            printf("R: 重新选择   Q: 返回\n");
            char tmp = GetCharIn("RrQq");

            if (tmp == 'r' || tmp == 'R') {
                continue;
            } else {
                PressQToGoBack();
                return 0;
            }
        }

        // 检查是否有余票
        if (GetRemainTicketNum(info_index_buying, session_buying) == 0) {
            printf("该场次已售罄！\n");
            printf("R: 重新选择  Q: 返回\n");
            char tmp = GetCharIn("RrQq");

            if (tmp == 'r' || tmp == 'R') {
                continue;
            } else {
                PressQToGoBack();
                return 0;
            }
        }
        break;
    }

    // 选择座位
    int seat;
    while (1) {
        printf("请输入欲购买电影的座位号：\n");
        seat = GetInteger(1, 99) - 1;
        if (film_info_arr[info_index_buying].
            sessions[session_buying].seat_status[seat] == 0) {
            break;
        }

        printf("该座位不可用！\n");
        printf("R: 重新选择  Q: 返回\n");
        char tmp = GetCharIn("RrQq");

        if (tmp == 'r' || tmp == 'R') {
            continue;
        } else {
            PressQToGoBack();
            return 0;
        }
    }

    // 添加交易信息
    DealInfoT deal = { id_buying, session_buying, seat };
    for (int i = 0; USER[i] != '\0'; i++) {
        deal.username[i] = USER[i];
    }
    time_t t = time(NULL);
    deal.time = *localtime(&t);

    FILE* movie_deal_f = fopen("movie_deal", "ab");
    fwrite(&deal, sizeof(DealInfoT), 1, movie_deal_f);
    fclose(movie_deal_f);

    // 修改电影信息
    film_info_arr[info_index_buying].
        sessions[session_buying].seat_status[seat] = 1;
    FILE* move_base = fopen("movie_base.dat", "wb+");
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        WriteFilmInfo(film_info_arr[i], move_base);
    }
    fclose(move_base);

    // 修改用户数据
    ResetUserDataArr();
    ReadUserData();

    int user_data_index = 0;
    for (int i = 0; user_data_arr[i].username[0] != 0; i++) {
        if (strcmp(user_data_arr[i].username, USER) == 0) {
            user_data_index = i;
            break;
        }
    }
    user_data_arr[user_data_index].change -=
        film_info_arr[info_index_buying].sessions[session_buying].price * 10;

    FILE* user_data_f = fopen("UserData.dat", "wb+");
    for (int i = 0; user_data_arr[i].username[0] != 0; i++) {
        WriteUserData(user_data_arr[i], user_data_f);
    }
    fclose(user_data_f);

    printf("购票成功！\n");
    PressQToGoBack();
    GoBack(Ticket);
    return 0;
}

int RefundTicket() {
    // 显示用户手中的票
    ReadThisUserData(USER);

    system("cls");
    printf("我的电影票：\n");
    for (int i = 0; ThisUser.tickets[i].film_name[0] != '\0'; i++) {
        printf("========================================\n");
        printf("    影片名：%s\n", ThisUser.tickets[i].film_name);
        printf("    放映编号：%d\n", ThisUser.tickets[i].film_id);
        printf("    %d月%d日 %d:%d开始     时长：%d分\n",
            ThisUser.tickets[i].time.month,
            ThisUser.tickets[i].time.day,
            ThisUser.tickets[i].time.hour,
            ThisUser.tickets[i].time.minute,
            ThisUser.tickets[i].length);
        printf("    座位号：%d    票价：%.2f\n", \
            ThisUser.tickets[i].seat, ThisUser.tickets[i].price);
    }

    // 选择要退的票
    printf("输入要退的票的放映编号：\n");
    int id_refunding = GetInteger(1, INT_MAX);
    int ticket_index_refunding = -1;

    for (int i = 0; ThisUser.tickets[i].film_id != 0; i++) {
        if (ThisUser.tickets[i].film_id == id_refunding) {
            ticket_index_refunding = i;
            break;
        }
    }

    ResetUserDataArr();
    ReadUserData();
    for (int i = 0; i < 999; i++) {
        if (strcmp(user_data_arr[i].username, USER) == 0) {
            user_data_arr[i].change += ThisUser.tickets[ticket_index_refunding].price * 10;
            ThisUser.tickets[ticket_index_refunding].film_id = 0;
            film_info_arr[FindFilmInfoIndex(id_refunding)].
                sessions[ThisUser.tickets[ticket_index_refunding].session].
                seat_status[ThisUser.tickets[ticket_index_refunding].seat] = 0;
            break;
        }
    }

    FILE* user_data_f = fopen("UserData.dat", "wb+");
    for (int i = 0; user_data_arr[i].username[0] != 0; i++) {
        WriteUserData(user_data_arr[i], user_data_f);
    }
    fclose(user_data_f);

    FILE* movie_base = fopen("movie_base.dat", "wb+");
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        WriteFilmInfo(film_info_arr[i], movie_base);
    }
    fclose(movie_base);
    printf("退票成功！\n");
    return 0;
}