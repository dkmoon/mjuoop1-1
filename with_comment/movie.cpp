#include <cstring>
#include <iostream>  // #include �߿��� <...> �� "..." �տ� ���ϴ�. �׸��� ���ĺ� �����մϴ�.
                     // #include <...> �κа� #include "..." ���̿��� �� ���� ����ִ°� �����ϴ�.
#include "movie.h"  // �ڽ��� ���� �����̹Ƿ� #include <...> �� �ƴ϶� #include "..." �� ���ϴ�.

// movie.h �� ������ ������, �Ҹ���, �޼����� ������ .cpp �� �ֽ��ϴ�.
// �� �� class ���ǿ� �����ϴ� ������� �����ϴ� ���� �����ϴ�.
Movie::Movie(const char* name, const char* releaseDate) {
    std::cout << "Constructor called" << std::endl;

    // ���� �Ҵ��ϰ� �Ű� ������ �����϶�� �����Ƿ� �Ʒ�ó�� �մϴ�.
    // strdup �� malloc + strcpy �Դϴ�. ���� malloc + strcpy �� �ص� �˴ϴ�.
    // ��� ������ �Ű� ���� �̸��� ���� ������ �Ʒ������� this-> �� ����߽��ϴ�.
    // ��� ���� �̸��� m_name, m_releaseDate ó�� �� ���� this-> �� ���� �����մϴ�.
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


    // ������, �Ҹ���, �޼����� ������ ���̿��� ��� �� �� �̻��� ���ϴ�.
    // �� ���� ���� ���� �� �����ϴ�. �� �̻��� ���� ���̵� �� 2���� �����մϴ�.
Movie::~Movie() {
    std::cout << "Destructor called" << std::endl;

    // ���� �ð��� ������ ��ó�� free �� delete �� �ϱ� ���� null check �� ���� ������ ��Ÿ���Դϴ�.
    // free �� delete �� ��ü������ null check �� �ϹǷ� null �̸� �ƹ��ϵ� ���� �ʽ��ϴ�.
    // �׷��� �ʱ�ȭ���� ���� ���� NULL �� ȥ�������� ������.
    // ������ �����ڿ� this->rates = NULL �� �����Ƿ� ���⼭�� free �� �� �� �ִ� �̴ϴ�.
    // ���� this->rates �� �ʱ�ȭ���� �ʾҴٸ� NULL �� �ƴ϶� ������ �����Ⱚ�� �� �ְ� �ǰ�
    // �� ���¿��� free �� �Ҹ��� �װ� �޸� �����Դϴ�.
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

    // realloc �� byte ������ �Ҵ��ϱ� ������ * sizeof(int) �� ����� ���� ����ϼ���.
    int* resized = (int *) realloc(rates, (numRates + 1) * sizeof(int));

    // �޸� �Ҵ��� �����ϴ� ��쿡 ���� ó���� ���ִ� ���� �����ϴ�.
    // �׷��� �����Ҵ��� �� �� �Ҵ��Ϸ��� �޸𸮰� MB ���� �̻����� ū ��찡 �ƴԿ���
    // ���� �޸𸮸� �Ҵ� ��û�ߴµ� �����ߴٸ� �̴� ���� �������� ��Ȳ�� ���������� ���մϴ�.
    // �Ƹ� ���α׷��� ����� ���������� ���� ���̰�
    // ���⼭ ���� ó���� �Ѵٰ� �ص� ���� �� �� �ִ� �͵� �����ϴ�.
    // �׷��� �ǹ������δ� �޸� �Ҵ��� ������ ��� �׳� ���α׷��� �װ� �ϴ� ��찡 ��κ��Դϴ�.
    // �� �� assert(...) ���� ���� ����մϴ�.
    // ���� �Ʒ��� assert(resized != NULL); ���� ������ ��ü �����մϴ�.
    if (resized == NULL) {
        std::cerr << "realloc failed" << std::endl;
        return;
    }

    // resized[numRates] = rate; �� ++numRates; �̷��� �� �ٷ� �� ���� �ִµ�
    // ���⼭ ���� �ǵ������� C ������ postfix ++ �� ������Ű�� ���ؼ� numRates++ �� ����ϴ�.
    resized[numRates++] = rate;

    // �� �Ҵ��� ���� rates ���� �ٽ� �����ؾߵ˴ϴ�.
    rates = resized;
}


void Movie::print() {
    int sum = 0;

    // C++ �� for �ȿ��� ������ ������ �� �ֽ��ϴ�.
    // ���� �Ʒ��� for (int i = 0; i < numRates; ++i) �� �ٲ� �� �ֽ��ϴ�.
    // C ������ ������ ������ C++ ���� ���Ǵ� �͵��� ���߿� �� ������ ��� ������ �����Դϴ�.
    int i;
    for (i = 0; i < numRates; ++i) {
        sum += rates[i];
    }

    // int �� int �� ���� ��� �������� ������ ���� �����Ⱑ �˴ϴ�.
    // ���� ��� 5/4 �� 1.25 �� �ƴ϶� 1 �� �˴ϴ�.
    // ������ �Ҽ������� �����Ϸ��� double �̳� float ���� �����ؾߵǴµ� �̸� �����ϰ� �ϴ� ����
    // �Ʒ�ó�� 1.0 �� �����ָ� �˴ϴ�. �׷� sum * 1.0 �� double �� conversion �ǰ� ����� double �� �˴ϴ�.
    // ���� float �� ���� ���� ��� sum * 1.0f �� �ϸ� �˴ϴ�.
    double avg = sum * 1.0 / numRates;

    std::cout << name << std::endl;
    std::cout << releaseDate << std::endl;
    std::cout << avg << std::endl;
}