// Program Cars reads a record from a file and writes
// its contents back to another file with the price member
// increased by 10%.
#include <iostream>
#include <fstream>
#include <string>

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
};

struct Car
{
	Car::Car() {}

	Car::Car(string _customer, float _price, Date _purchased)
	{
		price = _price;
		purchased = _purchased;
		customer = _customer;
		sold = false;
	}

	Car::Car(string _customer, float _price, Date _purchased, Date _soldDate)
	{
		(*this) = Car(_customer, _price, _purchased);
		sold = true;
		soldDate = _soldDate;
	}

	float price;
	Date purchased;
	string customer;

	bool sold;	//If a car was sold
	Date soldDate;	//The date the car was sold (undefined if not sold)
};

// Pre:  File dataIn has been opened.
// Post: The fields of car are read from file dataIn.
Car GetCar(ifstream&  dataIn)
{
	Car car;
	dataIn >> car.customer;
	dataIn >> car.price >> car.purchased.day
		>> car.purchased.month >> car.purchased.year;
	dataIn.ignore(2, '\n');
	return car;
}

Car CarSold(Date _date, Car _car)
{
	_car.sold = true;
	_car.soldDate = _date;
	return _car;
}

// Pre:  File dataOut has been opened.
// Post: The fields of car are written on file dataOut,
//       appropriately labeled.
void  WriteCar(ofstream&  dataOut, Car  car)
{
	dataOut << "Customer: " << car.customer << endl
		<< "Price:    " << car.price << endl
		<< "Purchased:" << car.purchased.day << "/"
		<< car.purchased.month << "/"
		<< car.purchased.year << endl;
}

int main()
{
	Car  car;
	ifstream dataIn;
	ofstream dataOut;

	dataIn.open("cars.dat");
	dataOut.open("cars.out");
	cout << fixed << showpoint;

	car = GetCar(dataIn);
	while (dataIn)
	{
		car.price = car.price * 1.10;

		cout << "The car's owner is " << car.customer << endl;
		cout << "Has the car been resold? <y/n>" << endl;

		char response;
		while (true)
		{
			cout << ">";
			response = cin.get();
			if (tolower(response) == 'y' && tolower(response) == 'n') break;
			cout << "I'm sorry, I don't understand \"" << response << "\".  Please try again." << endl;
		}
		if(response == 'y' 

		WriteCar(dataOut, car);
		car = GetCar(dataIn);
	}
	return 0;
}