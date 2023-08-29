#include "FilmSystem.h"
int HomeForCustomer() {
    while (1) {
        int index = 1;
        system("cls");
        printf("=====================================================\n");
        printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ\n");
        printf("                         ������\n");
        printf("    %d. �����˺�\n", index++);
        printf("    %d. �鿴��Ӱ��ӳ��Ϣ\n", index++);
        printf("    %d. ��Ʊ��Ʊ\n", index++);
        printf("    %d. ��ѯ��Ӱ\n", index++);
        printf("    %d. �˳���¼\n", index++);
        printf("    %d. �˳�ϵͳ\n", index);
        printf("=====================================================\n");

        // �������飬�洢����������Ӧ�ĺ���ָ��
        // int (*functions[10])(void) = {
        //     AccountForCustomer, ViewFilmInfo, Ticket, SearchFilmInfo, GoBackToLogin, Exit
        // }; // Temply
        int (*functions[10])(void) = {
            AccountForCustomer, ViewFilmInfo, Ticket, Search, GoBackToLogin, Exit
        };

        // ��ȡ�û����룬�򿪶�Ӧ�Ĺ���
        if (GetUserOrder(index, functions) == -1) {
            break;
        };
    }
    return 0;
}