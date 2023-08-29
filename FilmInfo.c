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
        printf("                   欢迎使用电影购票系统 \n");
        printf("                     电影放映信息管理   \n");
        printf("    %d. 显示所有在映电影 \n", index++);
        printf("    %d. 添加电影\n", index++);
        printf("    %d. 删除电影\n", index++);
        printf("    %d. 修改电影信息\n", index++);
        printf("    %d. 返回 \n", index);
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
        printf("错误：文件打开失败！\n");
        fclose(FilmBase);
        return 0;
    }

    // 从文件读取放映信息
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
    printf("放映编号: %d\n", info.id);
    printf("电影名称: %s\n", info.name);
    printf("电影类型: %s\n", info.type);
    printf("时长: %d\n", info.length);
    printf("场次: \n");
    for (int i = 0; info.sessions[i].time.year != 0; i++) {
        printf("[%d] ", i + 1);
        printf("%4hd年%2hd月%2hd日 %2hd:%2hd",
            info.sessions[i].time.year,
            info.sessions[i].time.month,
            info.sessions[i].time.day,
            info.sessions[i].time.hour,
            info.sessions[i].time.minute);
        printf("%4d号厅", info.sessions[i].hall);
        printf("%7.2f元", info.sessions[i].price);
        printf("  余票%2d张\n", info.sessions[i].ticket_num);
    }
    return 0;
}

int ViewFilmInfo() {
    // 读取电影信息
    ResetFilmInfoArr();
    ReadFilmInfo();

    // 浏览放映信息
    int looking = 0;
    int info_num = 0; // 计算有多少条放映信息
    for (int i = 0; i < 999; i++) {
        if (film_info_arr[i].id == 0) {
            info_num = i;
            break;
        }
    }

    if (info_num == 0) {
        system("cls");
        printf("===================================================== \n\n");
        printf("                     这里空空如也 -_- \n\n");
        printf("===================================================== \n");
        printf("  Q: 退出\n");
        while (getch() != 'q');
        return 0;
    }

    while (1) {
        system("cls");
        printf("==================== %03d/%03d ======================== \n\n",
            looking + 1, info_num);
        PrintFilmInfo(film_info_arr[looking]);
        printf("\n===================================================== \n");
        printf(" J: 上一条            L: 下一条            Q: 退出\n");

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
    // 用户输入电影信息
    FilmInfoT info = { 0 };
    system("cls");
    printf("放映编号：");
    while (1) {
        info.id = GetInteger(1, 999999);

        ResetFilmInfoArr();
        ReadFilmInfo();

        int flag = 0;
        for (int i = 0; film_info_arr[i].id != 0; i++) {
            if (film_info_arr[i].id == info.id) {
                printf("该编号已存在！请重新输入: ");
                flag = 1;
                break;
            }
        }

        if (!flag) {
            break;
        }
    }

    printf("电影名称: ");
    scanf("%*c");
    scanf("%s", info.name);
    printf("电影类型: ");
    scanf("%*c");
    scanf("%s", info.type);

    printf("时长：");
    info.length = GetInteger(0, 9999);

    printf("场次\n");
    printf(" (格式: 年-月-日-时:分 影厅 票价 总票量, 输入“e”结束): \n");
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
            printf("格式错误！请重新输入：\n");
        }
    }

    // 写入电影信息
    FILE* FilmBase = fopen(FilmBaseFileName, "ab");
    WriteFilmInfo(info, FilmBase);
    fclose(FilmBase);
    printf("写入成功！\n");

    // 返回上级界面
    ResetFilmInfoArr();
    PressQToGoBack();
    return 0;
}

int DeleteFilmInfo() {
    ResetFilmInfoArr();
    ReadFilmInfo();

    system("cls");
    printf("请输入要删除的电影放映编号：\n");
    unsigned int id = 0;
    scanf("%ld", &id);

    // 查找电影编号
    int index = -1;
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        if (film_info_arr[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("未找到该电影！\n");
        PressQToGoBack();
        return 0;
    }

    // 打印原电影信息
    printf("您要删除的电影信息为：\n");
    printf("===================================\n");
    PrintFilmInfo(film_info_arr[index]);
    printf("===================================\n");

    // 确认删除
    scanf("%*c");
    printf("输入y确定删除：");
    if (getchar() != 'y') {
        printf("取消删除\n");
        PressQToGoBack();
        return 0;
    }

    // 重新写入电影信息
    FILE* FilmBase = fopen("movie_base.dat", "wb+");
    for (int i = 0; film_info_arr[i].id != 0; i++) {
        if (i == index) {
            continue;
        }
        WriteFilmInfo(film_info_arr[i], FilmBase);
    }
    fclose(FilmBase);

    printf("删除完毕！\n");
    PressQToGoBack();

    return 0;
}

int ModifyFilmInfo() {
    ResetFilmInfoArr();
    ReadFilmInfo();

    system("cls");
    printf("请输入要修改的电影放映编号：\n");
    int id = GetInteger(1, INT_MAX);
    int index = FindFilmInfoIndex(id);

    // 打印原电影信息
    printf("===================================\n");
    PrintFilmInfo(film_info_arr[index]);
    printf("===================================\n");

    // 输入新信息
    FilmInfoT info = { 0 };
    printf("输入修改后的信息: \n");
    printf("放映编号: ");
    while (1) {
        info.id = GetInteger(1, 999999);

        ResetFilmInfoArr();
        ReadFilmInfo();

        if (FindFilmInfoIndex(info.id) != -1) {
            printf("该编号已存在！请重新输入: ");
        } else {
            break;
        }
    }

    printf("电影名称: ");
    scanf("%*c");
    scanf("%s", info.name);
    printf("电影类型: ");
    scanf("%*c");
    scanf("%s", info.type);

    printf("时长：");
    info.length = GetInteger(0, 9999);

    printf("场次\n");
    printf(" (格式: 年-月-日-时:分 影厅 票价 总票量, 输入“e”结束): \n");
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
            printf("格式错误！请重新输入：\n");
        }
    }

    // 修改信息
    film_info_arr[index] = info;

    // 写入信息
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