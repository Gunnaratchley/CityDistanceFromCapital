#pragma once
#ifndef M_PI
#define M_PI    3.1415926535897932384626433832795
#endif


#include <algorithm>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>



class City
{
private:
	std::string cityName;
	std::string countryName;
	double latitude;
	double longitude;

	// Base to change letter casse
	static const int asciiBase = 32;
	// Used to convert radians
	static const int radCon = 180;
	// Base used in Distance
	static const int base = 2;
	// Column width for formatting menu
	static const int colWidth = 16;
	// Value used to convert kilometers to miles
	const double toMiles = 0.62137119;
	// Value to be used for 5 closest and farthest cities
	static const int topFive = 5;
public:
	City();
	City(std::string cName, std::string country, double lt, double lon);
	void setDetails(std::string cName, std::string country, double lt, double lon);
	std::string getCityName();
	std::string getCountryName();
	double getLatitute();
	double getLongitude();

	double rad_convertor(const double);
	long double distance(double, double, double, double);
	void menu();
	void sort(std::vector<double> val, std::vector<std::string> names, std::string name);
	void searchByName(std::vector<City>, std::string name);
	void searchByIndex(std::vector<City>, int index);
	
};

