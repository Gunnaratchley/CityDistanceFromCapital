#include "City.h"

//Constructors
City::City()
{
}
City::City(std::string cName, std::string country, double lt, double lon)
{
	cityName = cName;
	countryName = country;
	latitude = lt;
	longitude = lon;
}
//Setter
void City::setDetails(std::string cName, std::string country, double lt, double lon)
{
	cityName = cName;
	countryName = country;
	latitude = lt;
	longitude = lon;
}

//Getters
std::string City::getCityName()
{
	return cityName;
}
std::string City::getCountryName() 
{
	return countryName;
}
double City::getLatitute() 
{
	return latitude;
}
double City::getLongitude()
{
	return longitude;
}

//Funnction to covert radiance to get distnace
double City::rad_convertor(const double degree)
{
	double deg = (M_PI) / radCon;
	return (deg * degree);
}

//To find distance
long double City::distance(double lat1, double long1, double lat2, double long2)
{
	//to radian change
	lat1 = rad_convertor(lat1);
	long1 = rad_convertor(long1);
	lat2 = rad_convertor(lat2);
	long2 = rad_convertor(long2);
	//Distance formulae
	double dlong = long2 - long1;
	double dlat = lat2 - lat1;
	double ans = pow(sin(dlat / base), base) + cos(lat1) * cos(lat2) * pow(sin(dlong / base), base);
	ans = base * asin(sqrt(ans));
	//Earth radius
	double R = 6371;
	ans = ans * R;
	return ans;
}

//menu
void City::menu()
{
	std::cout << "1. Enter city name.\n2. Enter city index.\n3. Quit.\n";
}

//Sort the vectors to get ascending order
void City::sort(std::vector<double> val, std::vector<std::string> names, std::string name) 
{
	for (int i = 0; i < val.size(); i++)
	{
		for (int j = 0; j < val.size() - 1; j++)
		{
			if (val.at(j) > val.at(j + 1))
			{
				double temp = val.at(j);
				std::string temp1 = names.at(j);
				val.at(j) = val.at(j + 1);
				names.at(j) = names.at(j + 1);
				val.at(j + 1) = temp;
				names.at(j + 1) = temp1;
			}
		}
	}
	std::cout << std::setw(colWidth) << "Closest Cities" << std::setw(colWidth) << "Distance\n";
	for (int i = 0; i < topFive; i++)
	{
		std::cout << std::setw(colWidth) << names.at(i) << std::setw(colWidth) << (val.at(i) * toMiles)
			<< "  Miles" << std::endl;
	}
	std::cout << std::endl;
	std::cout << std::setw(colWidth) << "Farthest Cities" << std::setw(colWidth) << "Distance\n";
	auto lastFive = val.size() - topFive;
	for (int j = lastFive; j < val.size(); j++)
	{
		std::cout << std::setw(colWidth) << names.at(j) << std::setw(colWidth) << val.at(j)
			<< "  Kilometers" << std::endl;
	}
}

//Search by name
void City::searchByName(std::vector<City> city, std::string name)
{
	//word capitalization
	for (int i = 0; name[i] != '\0'; i++)
	{
		if (i == 0)
		{
			if ((name[i] >= 'a' && name[i] <= 'z'))
				name[i] = name[i] - asciiBase;
			continue;
		}
		if (name[i] == ' ')
		{
			++i;
			if (name[i] >= 'a' && name[i] <= 'z')
			{
				name[i] = name[i] - asciiBase;
				continue;
			}
		}
		else
		{
			if (name[i] >= 'A' && name[i] <= 'Z')
				name[i] = name[i] + asciiBase;
		}
	}
	int flag = 0, i = 0;
	//Check city in the list
	for (i = 0; i < city.size() - 1; i++)
	{
		if (city.at(i).getCityName() == name) 
		{
			flag = 1;
			break;
		}
	}
	std::vector<double>dist;
	std::vector<std::string>cityName;
	if (flag == 0)
	{
		std::cout << "City not found" << std::endl;
		return;
	}
	else {
		for (int j = 0; j < city.size() - 1; j++)
		{
			if (j != i)
			{
				dist.push_back(distance(city.at(i).getLatitute(), city.at(i).getLongitude(), city.at(j).getLatitute(), city.at(j).getLongitude()));
				cityName.push_back(city.at(j).getCityName());
			}
		}
	}
	sort(dist, cityName, city.at(i).getCityName());
}

//Search by index
void City::searchByIndex(std::vector<City> city, int index)
{
	if (index < 0 || index > city.size() - 1)
	{
		std::cout << "Index out of bound!!1" << std::endl;
		return;
	}
	else
	{
		std::vector<double>dist;
		std::vector<std::string>cityName;

		for (int j = 0; j < city.size() - 1; j++)
		{
			if (j != index)
			{
				dist.push_back(distance(city.at(index).getLatitute(), city.at(index).getLongitude(), city.at(j).getLatitute(), city.at(j).getLongitude()));
				cityName.push_back(city.at(j).getCityName());
			}
		}
		sort(dist, cityName, city.at(index).getCityName());
	}
}
