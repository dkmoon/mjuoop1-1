#include "movie.h"

int main()
{
    Movie topGun("Top Gun", "2022-06-22");

    topGun.addRate(0);  // Invalid rate 나와야 함
    topGun.addRate(6);  // Invalid rate 나와야 함

    topGun.addRate(5);
    topGun.addRate(1);

    topGun.print();

    return 0;
}