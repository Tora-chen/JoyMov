#include "FilmSystem.h"

int Home() {
    while (1) {
        int index = 1;
        system("cls");
        printf("=====================================================\n");
        printf("                   ��ӭʹ�õ�Ӱ��Ʊϵͳ\n");
        printf("                         ������\n");
        printf("    %d. �˺Ź���\n", index++);
        printf("    %d. ��Ӱ��ӳ��Ϣ����\n", index++);
        printf("    %d. Ʊ�����\n", index++);
        printf("    %d. ��ѯ����\n", index++);
        printf("    %d. ͳ�ƹ���\n", index++);
        printf("    %d. ���ܱ���\n", index++);
        printf("    %d. �˳���¼\n", index++);
        printf("    %d. �˳�ϵͳ\n", index);
        printf("=====================================================\n");

        // �������飬�洢����������Ӧ�ĺ���ָ��
        int (*functions[10])(void) = {
            Account, FilmInfo, Ticket, Search, Search,
            SummarySheet, GoBackToLogin, Exit
        };

        // ��ȡ�û����룬�򿪶�Ӧ�Ĺ���
        if (GetUserOrder(index, functions) == ExitAndGoBack) {
            break;
        }
    }
    return 0;
}