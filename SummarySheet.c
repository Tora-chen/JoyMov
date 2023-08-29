#include "FilmSystem.h"
int SummarySheet() {
    while (1) {
        int index = 0;
        system("cls");
        printf("===================================================== \n");
        printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ \n");
        printf("                       ���ܱ���   \n");
        printf("    %d. ��Ʊ������ \n", ++index);
        printf("    %d. ���׽����� \n", ++index);
        printf("    %d. ���� \n", ++index);
        printf("===================================================== \n");

        int (*functions[20])(void) = {
            ViewTicketNum, GoBack, GoBack
        };
        if (GetUserOrder(index, functions) == -1) {
            break;
        }
    }
    return 0;
};

int ViewTicketNum() {
    FilmInfoT info[999] = { 0 };
    ReadFilmInfo(info);

    system("cls");
    printf("��Ӱ���ơ�������������������"); // 10��ȫ�ǿո�
    printf("��Ʊ��\n");
    for (int i = 0; info[i].id != 0; i++) {
        printf("%-35s", info[i].name);
    }

    PressQToGoBack();
    return 0;
}