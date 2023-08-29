#include "FilmSystem.h"
long long GetDealNum() {
    long long num = 0;

    FILE* movie_deal = fopen("movie_deal.dat", "r");
    scanf("%lld", &num);
    fclose(movie_deal);

    return num;
}