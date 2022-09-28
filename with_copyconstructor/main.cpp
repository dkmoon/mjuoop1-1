#include "movie.h"

// 아래 코드는 관심 있는 학생의 경우 의도적으로 복사 생성자를 호출할 수 있게 하기 위해서 넣은 코드입니다.
void f(Movie f) {
    // 빈 구현
}

int main()
{
    Movie topGun("Top Gun", "2022-06-22");

    topGun.addRate(0);  // Invalid rate 나와야 함
    topGun.addRate(6);  // Invalid rate 나와야 함

    topGun.addRate(5);
    topGun.addRate(1);

    topGun.print();

    // 아래는 본 과제의 범위는 아니나 의도적으로 복사 생성자를 호출해보기 위한 코드입니다.
    // 관심 있는 학생은 주석을 해제하고 해보시기 바랍니다.
    f(topGun);

    return 0;
}