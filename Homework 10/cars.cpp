// Program Cars reads a record from a file and writes
// its contents back to another file with the price member
// increased by 10%.
#include <iostream>
#include <fstream>
#include <string>
#include <time.h>

using namespace std;

struct Date
{
	Date::Date() {}
	Date::Date(int _day, int _month, int _year)
	{
		day = _day;
		month = _month;
		year = _year;
	}

	int month;
	int day;
	int year;

	static Date getFromSystem()		//Returns a Date struct, populated with data from the system clock
	{
		//time_t sysTime;
		//localtime_s(time_t(0), & sysTime);
		//return Date(sysTime.tm_mday, sysTime->tm_mon + 1, sysTime->tm_year + 1900);
		

		//Currently only returns 11/12/17 (hardcoded) because the compiler is angry that functions are depreciated and I can't get it to work
		return Date(12, 11, 17);
	}
};

struct type_soldTo
{
	string customer;
	Date soldDate;
};

struct Car
{
	Car::Car()
	{
		sold = false;
	}

	Car::Car(string _customer, float _price, Date _purchased)
	{
		price = _price;
		purchased = _purchased;
		soldTo.customer = _customer;
		sold = false;
	}

	Car::Car(string _customer, float _price, Date _purchased, Date _soldDate)
	{
		(*this) = Car(_customer, _price, _purchased);
		sold = true;
		soldTo.soldDate = _soldDate;
	}

	float price;
	Date purchased;

	bool sold;	//If a car was sold
	type_soldTo soldTo;	//The owner (if sold) and the date sold
};

// Pre:  File dataIn has been opened.
// Post: The fields of car are read from file dataIn.
Car GetCar(ifstream&  dataIn)
{
	Car car;
	dataIn >> car.soldTo.customer;
	dataIn >> car.price >> car.purchased.day
		>> car.purchased.month >> car.purchased.year;
	dataIn.ignore(2, '\n');
	return car;
}

Car CarSold(Date _date, Car _car, string purchaser)
{
	_car.sold = true;
	_car.soldTo.soldDate = _date;
	_car.soldTo.customer = purchaser;
	return _car;
}

// Pre:  File dataOut has been opened.
// Post: The fields of car are written on file dataOut,
//       appropriately labeled.
void  WriteCar(ofstream&  dataOut, Car  car)
{
	dataOut << "Customer: " << car.soldTo.customer << endl
		<< "Price:    " << car.price << endl
		<< "Purchased:" << car.purchased.day << "/"
		<< car.purchased.month << "/"
		<< car.purchased.year << endl;
	if(car.sold) {
		dataOut << "Sold:     true" << endl;
		dataOut << "SoldDate: " << car.soldTo.soldDate.day << "/"
			<< car.soldTo.soldDate.month << "/"
			<< car.soldTo.soldDate.year << endl;
	}
	dataOut << endl;
}

int main()
{
	Car  car;
	ifstream dataIn;
	ofstream dataOut;
	ofstream dataSold;	//A special output location for cars that have been sold

	dataIn.open("cars.dat");
	dataOut.open("cars.out");
	dataSold.open("carsSold.out");
	cout << fixed << showpoint;

	car = GetCar(dataIn);
	while (dataIn)
	{
		car.price = car.price * 1.10;

		cout << "The car's owner is " << car.soldTo.customer << endl;

		//Ask if the car has been sold or not
		cout << "Has the car been resold? <y/n>" << endl;

		char response;
		while (true)
		{
			cout << ">";
			response = cin.get();	//Get the user's input
			cin.ignore(numeric_limits<streamsize>::max(), '\n');		//Get rid of any trailing data and the endline
			if (tolower(response) == 'y' || tolower(response) == 'n') break;
			cout << "I'm sorry, I don't understand \"" << response << "\".  Please try again." << endl;
			
		}
		
		if (tolower(response) == 'y')	//The car was sold
		{
			cout << "Who bought the car?" << endl << ">";
			string owner;
			getline(cin, owner);
			car = CarSold(Date::getFromSystem(), car, owner);
			WriteCar(dataSold, car);
		}
		else WriteCar(dataOut, car);
		car = GetCar(dataIn);

		cout << endl;
	}

	dataIn.close();
	dataOut.close();
	dataSold.close();
	return 0;
}