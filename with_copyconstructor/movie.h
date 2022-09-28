#pragma once

class Movie {
private:
	const char* name;
	const char* releaseDate;
	int* rates;
	int numRates;

public:
	Movie(const char* name, const char* releaseDate);
	Movie(const Movie& movie);
	~Movie();

	void addRate(int rate);
	void print();
};