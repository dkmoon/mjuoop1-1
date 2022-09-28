#pragma once  // 헤더 파일 첫줄은 무조건 #include guard 를 넣습니다.

// 클래스의 이름은 단어시작 첫글자 대문자, 그 이후 소문자를 씁니다.
// 단어의 조합 같은 경우는 단어의 시작마다 대문자가 됩니다.
// 예를 들어 class KoreanMovie 같이 씁니다.
// 이렇게 단어 시작마다 대문자가 나오는게 낙타 등처럼 보인다고 해서 camel form 이라고 합니다.
// 반대로 단어를 _ 로 연결하는 것은 뱀처럼 보인다고 해서 snake form 이라고 합니다.
// 예를 들어 korean_movie 이렇게 쓰는 것입니다.
// 참고로 snake form 을 쓸 때는 모두 소문자로 쓰지 대문자를 섞지는 않습니다.
// 그리고 클래스 이름을 쓸 때는 위에 언급한 것처럼 camel form 을 쓰지 snake form 을 쓰지 않습니다.
class Movie {

// private 접근 지정자를 앞에 쓸지 뒤에 쓸지는 개인 스타일입니다.
// 그러나 적어도 오락가락 하는건 좋지 않으니 한 방법으로 일관되게 하는 것이 좋습니다.
// 예를 들어 여기서는 private: 이 public: 보다 앞에 나왔는데,
// 우리가 class Theater 를 만들 때 이를 뒤집어서 public: 이 먼저 나오고 하면 안 좋습니다.
private:
	// 멤버 변수의 이름은 snake form 이나 camel form 이지만 소문자로 시작하는 경우를 많이 씁니다.
	// 그리고 사람들 스타일에 따라 멤버 변수 이름은 다음 3가지 변형이 가능합니다.
	// 1. 앞에 _ 을 붙이는 경우: snake form, camel form 모두 가능. 예: _rates, _numRates, _num_rates
	// 2. 뒤에 _ 을 붙이는 경우: snake form, camel form 모두 가능. 예: rates_, numRates_, num_rates_
	// 3. 앞에 m_ 을 붙이는 경우: 헝가리안 표기법인데 camel form만 씁니다. 예: m_rates, m_numRates,
	// 이렇게 멤버 변수 이름 앞뒤에 접두사 접미사를 붙이는 것은 멤버 변수가 메서드 안에서 쓰일 때
	// 그것이 멤버 변수인지 아니면 일반 변수인지 쉽게 구분이 가게 하려는 목적입니다.
	const char* name;
	const char* releaseDate;
	int* rates;
	int numRates;

public:
	// 함수의 매개 변수 이름은 보통 소문자로 씁니다.
	// snake form 을 쓰거나 camel form 을 쓰더라도 첫 글자를 소문자로 시작합니다.
	// 아래에 저는 camel form 인데 첫 글자를 소문자로 해서 releaseDate 이라고 했습니다.
	// 아주 드믈긴 하지만 매개 변수 이름 앞에 _ 을 붙이는 사람들도 있습니다. 예: _name, _releaseDate
	// 이런 경우 위에 멤버 변수 이름 설명에 쓴 1번 (앞에 _ 을 붙이는 경우) 는 사용하지 않습니다.
	// _ 같은걸 붙이는 이유가 멤버 변수와 일반 변수를 구분하기 위한 것이기 때문에 둘 중 한 경우만 씁니다.
	Movie(const char* name, const char* releaseDate);
	~Movie();

	// 같은 성격의 것들을 그룹핑해서 배치하면 보기가 편합니다.
	// 그룹핑이라고 해서 특별한 것은 아니고 서로 다른 그룹의 것은 빈 줄로 구분하는 겁니다.
	// 이 예에서는 위에 생성자/소멸자는 빈줄 없이 붙여 써서 같은 종류의 것이라는 것을 나타내고,
	// 메서드는 소멸자 뒤에 한 줄 띄고 두 개를 빈 줄 없이 나열했습니다.
	void addRate(int rate);
	void print();
};