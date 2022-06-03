#include <iostream>

#include "City.h"

int main()
{
	City c;
	std::vector<City> cityDetails;
	std::string line, name;
	std::ifstream in;
	int j = 0, k = 0, index;
	in.open("worldcities.csv");
	if (!in) 
	{
		std::cout << "File not found!!!!" << std::endl;
		exit(0);
	}
	else
	{
		while (!in.eof())
		{

			if (j == 0)
			{
				//to skip first line which just contains column info
				getline(in, line);
				j++;
			}
			else
			{
				//Cut it up into cells
				getline(in, line);
				std::stringstream   lineStream(line);
				std::string         cell;
				std::string arr[4];
				int i = 0;
				std::string::size_type sz = 0;
				while (std::getline(lineStream, cell, ','))
				{
					arr[i] = cell;
					i++;
				}
				//converts long and lat from string to double
				double val1 = strtod(arr[2].c_str(), NULL);
				double val2 = strtod(arr[3].c_str(), NULL);
				//sets the values to your object and push back into vector
				c.setDetails(arr[0], arr[1], val1, val2);
				cityDetails.push_back(c);
			}
		}
	}
	int ch;
	std::cout << "Cities:" << std::endl;
	for (int i = 0; i < cityDetails.size() - 1; i++) 
	{
		std::cout << i << " " << cityDetails.at(i).getCityName() << std::endl;
	}
	std::cout << std::endl;
	c.menu();
	std::cout << std::endl << "Enter your choice:";
	std::cin >> ch;
	while (ch < 1 || ch>3)
	{
		std::cout << "ERROR!	Choice should be 1, 2, or a 3\n";
		std::cout << "Enter your choice:";
		std::cin >> ch;
	}
	while (ch != 3) 
	{
		switch (ch)
		{
		case 1:
			std::cout << "Enter the name of the city:";
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			std::getline(std::cin, name);
			std::cout << std::endl;
			c.searchByName(cityDetails, name);
			break;
		case 2:
			std::cout << "Enter the number of the city:";
			std::cin >> index;
			std::cout << std::endl;

			c.searchByIndex(cityDetails, index);
			break;
		default:
			break;
		}

		std::cout << std::endl;
		c.menu();
		std::cout << std::endl << "Enter your choice:";
		std::cin >> ch;
	}
	return 0;
}