#include "FilmSystem.h"
int Ticket() {
    while (1) {
        int index = 1;
        system("cls");
        printf("===================================================== \n");
        printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ \n");
        printf("                        Ʊ�����  \n");
        printf("    %d. ��Ʊ\n", index++);
        printf("    %d. ��Ʊ\n", index++);
        printf("    %d. ���� \n", index);
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

    // �����������Ӱ�ķ�ӳ���
    printf("�������������Ӱ�ķ�ӳ��ţ�\n");
    int id_buying = 0;
    int info_index_buying = -1;
    while (1) {
        id_buying = GetInteger(1, INT_MAX);
        info_index_buying = FindFilmInfoIndex(id_buying);
        if (info_index_buying == -1) {
            printf("δ�ҵ��õ�Ӱ��\n");
            printf("���������룺\n");
        } else {
            break;
        }
    }

    // ѡ�񳡴�
    PrintFilmInfo(film_info_arr[info_index_buying]);
    SplitLine();
    int session_buying;
    while (1) {
        printf("��ѡ�񳡴Σ�");
        session_buying = GetInteger(1, INT_MAX) - 1;
        if (film_info_arr[info_index_buying].
            sessions[session_buying].time.year == 0) {
            printf("δ�ҵ��ó��Σ�\n");
            printf("R: ����ѡ��   Q: ����\n");
            char tmp = GetCharIn("RrQq");

            if (tmp == 'r' || tmp == 'R') {
                continue;
            } else {
                PressQToGoBack();
                return 0;
            }
        }

        // ����Ƿ�����Ʊ
        if (GetRemainTicketNum(info_index_buying, session_buying) == 0) {
            printf("�ó�����������\n");
            printf("R: ����ѡ��  Q: ����\n");
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

    // ѡ����λ
    int seat;
    while (1) {
        printf("�������������Ӱ����λ�ţ�\n");
        seat = GetInteger(1, 99) - 1;
        if (film_info_arr[info_index_buying].
            sessions[session_buying].seat_status[seat] == 0) {
            break;
        }

        printf("����λ�����ã�\n");
        printf("R: ����ѡ��  Q: ����\n");
        char tmp = GetCharIn("RrQq");

        if (tmp == 'r' || tmp == 'R') {
            continue;
        } else {
            PressQToGoBack();
            return 0;
        }
    }

    // ��ӽ�����Ϣ
    DealInfoT deal = { id_buying, session_buying, seat };
    for (int i = 0; USER[i] != '\0'; i++) {
        deal.username[i] = USER[i];
    }
    time_t t = time(NULL);
    deal.time = *localtime(&t);

    FILE* movie_deal_f = fopen("movie_deal", "ab");
    fwrite(&deal, sizeof(DealInfoT), 1, movie_deal_f);
    fclose(movie_deal_f);

    // �޸ĵ�Ӱ��Ϣ
    film_info_arr[info_index_buying].
        sessions[session_buying].seat_status[seat] = 1;
    FILE* move_base = fopen("movie_base.dat", "wb+");
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        WriteFilmInfo(film_info_arr[i], move_base);
    }
    fclose(move_base);

    // �޸��û�����
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

    printf("��Ʊ�ɹ���\n");
    PressQToGoBack();
    GoBack(Ticket);
    return 0;
}

int RefundTicket() {
    // ��ʾ�û����е�Ʊ
    ReadThisUserData(USER);

    system("cls");
    printf("�ҵĵ�ӰƱ��\n");
    for (int i = 0; ThisUser.tickets[i].film_name[0] != '\0'; i++) {
        printf("========================================\n");
        printf("    ӰƬ����%s\n", ThisUser.tickets[i].film_name);
        printf("    ��ӳ��ţ�%d\n", ThisUser.tickets[i].film_id);
        printf("    %d��%d�� %d:%d��ʼ     ʱ����%d��\n",
            ThisUser.tickets[i].time.month,
            ThisUser.tickets[i].time.day,
            ThisUser.tickets[i].time.hour,
            ThisUser.tickets[i].time.minute,
            ThisUser.tickets[i].length);
        printf("    ��λ�ţ�%d    Ʊ�ۣ�%.2f\n", \
            ThisUser.tickets[i].seat, ThisUser.tickets[i].price);
    }

    // ѡ��Ҫ�˵�Ʊ
    printf("����Ҫ�˵�Ʊ�ķ�ӳ��ţ�\n");
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
    printf("��Ʊ�ɹ���\n");
    return 0;
}