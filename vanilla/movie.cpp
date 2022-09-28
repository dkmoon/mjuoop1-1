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


//// ����: ���� �����ڴ� ��� ������ �������� ���뿡�� �����߽��ϴ�.
////       �̸� ��� �ʱ�ȭ ����Ʈ�� �̿��� ���� �ֽ��ϴ�. �� ���� ����ó�� �մϴ�.
////       �� �� ��� �ʱ�ȭ ����Ʈ�� ������ ��� ���� ������ class ���ǿ����� ������� �մϴ�.
//Movie::Movie(const char* name, const char* releaseDate)
//    : name(_strdup(name)), releaseDate(_strdup(releaseDate)), rates(NULL), numRates(0) {
//    std::cout << "Constructor called" << std::endl;
//}


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

    int i;
    for (i = 0; i < numRates; ++i) {
        sum += rates[i];
    }

    double avg = sum * 1.0 / numRates;

    std::cout << name << std::endl;
    std::cout << releaseDate << std::endl;
    std::cout << avg << std::endl;
}