#include <cstring>
#include <iostream>  // #include 중에는 <...> 을 "..." 앞에 씁니다. 그리고 알파벳 정렬합니다.
                     // #include <...> 부분과 #include "..." 사이에는 한 줄을 띄어주는게 좋습니다.
#include "movie.h"  // 자신이 만든 파일이므로 #include <...> 가 아니라 #include "..." 을 씁니다.

// movie.h 에 나열된 생성자, 소멸자, 메서드의 구현을 .cpp 에 넣습니다.
// 이 때 class 정의에 등장하는 순서대로 구현하는 것이 좋습니다.
Movie::Movie(const char* name, const char* releaseDate) {
    std::cout << "Constructor called" << std::endl;

    // 동적 할당하고 매개 변수를 복사하라고 했으므로 아래처럼 합니다.
    // strdup 은 malloc + strcpy 입니다. 따라서 malloc + strcpy 로 해도 됩니다.
    // 멤버 변수와 매개 변수 이름이 같기 때문에 아래에서는 this-> 를 명시했습니다.
    // 멤버 변수 이름을 m_name, m_releaseDate 처럼 한 경우는 this-> 는 생략 가능합니다.
    this->name = _strdup(name);
    this->releaseDate = _strdup(releaseDate);
    this->rates = NULL;
    this->numRates = 0;
}


//// 참고: 위의 생성자는 멤버 변수를 생성자의 몸통에서 구현했습니다.
////       이를 멤버 초기화 리스트를 이용할 수도 있습니다. 그 경우는 다음처럼 합니다.
////       이 때 멤버 초기화 리스트에 나오는 멤버 변수 순서는 class 정의에서의 순서대로 합니다.
//Movie::Movie(const char* name, const char* releaseDate)
//    : name(_strdup(name)), releaseDate(_strdup(releaseDate)), rates(NULL), numRates(0) {
//    std::cout << "Constructor called" << std::endl;
//}


    // 생성자, 소멸자, 메서드의 구현들 사이에는 적어도 한 줄 이상을 비웁니다.
    // 두 줄을 비우는 것이 더 좋습니다. 그 이상은 과한 것이디 딱 2줄이 적당합니다.
Movie::~Movie() {
    std::cout << "Destructor called" << std::endl;

    // 수업 시간에 설명한 것처럼 free 나 delete 를 하기 전에 null check 을 할지 말지는 스타일입니다.
    // free 나 delete 는 자체적으로 null check 을 하므로 null 이면 아무일도 하지 않습니다.
    // 그러나 초기화되지 않은 값과 NULL 을 혼돈하지는 마세요.
    // 위에서 생성자에 this->rates = NULL 을 했으므로 여기서는 free 를 할 수 있는 겁니다.
    // 만일 this->rates 을 초기화하지 않았다면 NULL 이 아니라 임의의 쓰레기값이 들어가 있게 되고
    // 이 상태에서 free 가 불리면 그건 메모리 오류입니다.
    if (name != NULL) {
        free((void *) name);
    }
    if (releaseDate != NULL) {
        free((void *) releaseDate);
    }
    if (rates != NULL) {
        free(rates);
    }
}


void Movie::addRate(int rate) {
    if (rate < 1 || rate > 5) {
        std::cerr << "Invalid rate" << std::endl;
        return;
    }

    // realloc 은 byte 단위로 할당하기 때문에 * sizeof(int) 를 해줘야 됨을 명심하세요.
    int* resized = (int *) realloc(rates, (numRates + 1) * sizeof(int));

    // 메모리 할당이 실패하는 경우에 대한 처리를 해주는 것이 좋습니다.
    // 그런데 동적할당을 할 때 할당하려는 메모리가 MB 단위 이상으로 큰 경우가 아님에도
    // 적은 메모리를 할당 요청했는데 실패했다면 이는 아주 절망적인 상황에 도달했음을 뜻합니다.
    // 아마 프로그램은 제대로 동작하지도 않을 것이고
    // 여기서 오류 처리를 한다고 해도 따로 할 수 있는 것도 없습니다.
    // 그래서 실무적으로는 메모리 할당이 실패한 경우 그냥 프로그램을 죽게 하는 경우가 대부분입니다.
    // 이 때 assert(...) 같은 것을 사용합니다.
    // 따라서 아래는 assert(resized != NULL); 같은 것으로 대체 가능합니다.
    if (resized == NULL) {
        std::cerr << "realloc failed" << std::endl;
        return;
    }

    // resized[numRates] = rate; 과 ++numRates; 이렇게 두 줄로 쓸 수도 있는데
    // 여기서 저는 의도적으로 C 에서의 postfix ++ 을 복습시키기 위해서 numRates++ 을 썼습니다.
    resized[numRates++] = rate;

    // 재 할당한 것을 rates 으로 다시 저장해야됩니다.
    rates = resized;
}


void Movie::print() {
    int sum = 0;

    // C++ 은 for 안에서 변수를 선언할 수 있습니다.
    // 따라서 아래는 for (int i = 0; i < numRates; ++i) 로 바꿀 수 있습니다.
    // C 에서는 허용되지 않지만 C++ 에서 허용되는 것들은 나중에 한 꺼번에 묶어서 설명할 예정입니다.
    int i;
    for (i = 0; i < numRates; ++i) {
        sum += rates[i];
    }

    // int 를 int 로 나눌 경우 나머지를 버리는 정수 나누기가 됩니다.
    // 예를 들어 5/4 는 1.25 가 아니라 1 이 됩니다.
    // 평점을 소숫점으로 변경하려면 double 이나 float 으로 변경해야되는데 이를 간단하게 하는 것은
    // 아래처럼 1.0 을 곱해주면 됩니다. 그럼 sum * 1.0 이 double 로 conversion 되고 결과도 double 이 됩니다.
    // 만일 float 을 쓰고 싶은 경우 sum * 1.0f 를 하면 됩니다.
    double avg = sum * 1.0 / numRates;

    std::cout << name << std::endl;
    std::cout << releaseDate << std::endl;
    std::cout << avg << std::endl;
}