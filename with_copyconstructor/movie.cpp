#include <cstring>
#include <iostream>

#include "movie.h"


Movie::Movie(const char* name, const char* releaseDate) {
    std::cout << "Constructor called" << std::endl;

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


// 본 과제는 복사 생성자를 배우기 전에 생성자 소멸자를 연습해 보는 것이 목적입니다.
// 따라서 복사 생성자는 숙제의 범위가 아닙니다.
// 그러나 복사 생성자 없이 Movie class 는 버그가 있게 됩니다.
// 왜 그럴까요? 그건 수업 시간에 설명한대로 컴파일러가 만들어주는 복사 생성자는 모듬 멤버를 얕은 복사 하는데,
// 그렇게 되면 name, releaseDates, rates 역시 복사가 되고 원본과 사본의 소멸자가 각각 불릴 경우 이들이 가리키는 메모리가
// 두 번 해제 되기 때문입니다.
// 여기서는 클래스 구현의 완전성 측면에서 참고하시라고 복사 생성자를 추가했습니다.
Movie::Movie(const Movie& ref) {
    std::cout << "Copy constructor called" << std::endl;

    name = _strdup(ref.name);
    releaseDate = _strdup(ref.releaseDate);

    if (ref.rates != NULL) {
        rates = (int*)malloc(ref.numRates * sizeof(int));


        // 아래 for 를 이용한 복사는 다음처럼 한 줄로도 표현이 가능합니다.
        //memcpy(rates, ref.rates, ref.numRates * sizeof(int));
        int i;
        for (i = 0; i < ref.numRates; ++i) {
            rates[i] = ref.rates[i];
        }
    }
    else {
        rates = NULL;
    }

    numRates = ref.numRates;
}


Movie::~Movie() {
    std::cout << "Destructor called" << std::endl;

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

    int* resized = (int *) realloc(rates, (numRates + 1) * sizeof(int));

    if (resized == NULL) {
        std::cerr << "realloc failed" << std::endl;
        return;
    }

    resized[numRates++] = rate;
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

    double avg = sum * 1.0 / numRates;

    std::cout << name << std::endl;
    std::cout << releaseDate << std::endl;
    std::cout << avg << std::endl;
}