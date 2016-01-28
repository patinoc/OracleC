//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Esteban Parra
// Version     : 1
// Copyright   : It's free
// Description : Main class for the Hardwood Seller
//============================================================================

#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include "WoodItem.h"

struct Customer
{
	std::string name, address, date;
};

void readInputFile(std::string inputFilePath, Customer& customer, std::vector<WoodItem>& orders);
void parseCustomer(std::string line, Customer& customer);
void parseOrders(std::string line, std::vector<WoodItem>& orders);
double deliveryMultiplier(int bfamount);
double deliveryTime(const std::vector<WoodItem>&);

/*
 * Contains Customer's full name, address, and date of the order.
 */

std::map<std::string, double> BASE_PRICE = { { "Cherry", 5.95 },
{ "Curly Maple", 6.0 }, { "Genuine Mahogany", 9.6 }, { "Wenge", 22.35 },
{ "White Oak", 6.7 }, { "Sawdust", 1.5 } };
std::map<std::string, double> BASE_DELIVERY_TIME = { { "Cherry", 2.5 },
{ "Curly Maple", 1.5 }, { "Genuine Mahogany", 3.0 }, { "Wenge", 5.0 },
{ "White Oak", 2.3 }, { "Sawdust", 1.0 } };

int main() {
	Customer customer;
	std::vector<WoodItem> orders;
	readInputFile("test.txt", customer, orders);
	for (const WoodItem& w : orders)
	{
		std::cout << w.type << ' ' << w.price << ' ' << w.baseDeliveryTime << '\n';
	}
	std::cout << "\n\n" << deliveryTime(orders) << '\n';
	return 0;
}

/*
 * Method to read the input file
 */
void readInputFile(std::string inputFilePath, Customer& customer, std::vector<WoodItem>& orders) {
	std::ifstream inFile(inputFilePath);
	if (!inFile)
	{
		std::cerr << "Error opening input file " << inputFilePath << '\n';
		exit(1);
	}
	while (inFile)
	{
		std::string customer_info, orders_line;
		
		std::getline(inFile, customer_info);
		parseCustomer(customer_info, customer);

		std::getline(inFile, orders_line);
		parseOrders(orders_line, orders);
	}

}

void parseCustomer(std::string line, Customer& customer) {
	std::string token;
	std::stringstream ss(line);
	std::getline(ss, token, ';');
	customer.name = token;
	std::getline(ss, token, ';');
	customer.address = token;
	std::getline(ss, token);
	customer.date = token;
}

void parseOrders(std::string line, std::vector<WoodItem>& orders)
{
	std::stringstream ss(line);
	std::string token;
	WoodItem w;
	while (std::getline(ss, token, ';'))
	{
		std::istringstream iss(token);
		int amount;
		std::getline(iss, w.type, ':'); 
		iss >> amount;
		w.price = amount * BASE_PRICE[w.type];
		w.baseDeliveryTime = deliveryMultiplier(amount) * BASE_DELIVERY_TIME[w.type];
		orders.push_back(w);
	}
}

double deliveryMultiplier(int bfamount)
{
	if (bfamount <= 100)
		return 1;
	else if (bfamount <= 200)
		return 2;
	else if (bfamount <= 300)
		return 3;
	else if (bfamount <= 400)
		return 4;
	else if (bfamount <= 500)
		return 5;
	else
		return 5.5;
}
/*
 * Method to compute the deliveryTime
 */
double deliveryTime(const std::vector<WoodItem>& items) {
	double deliveryETA = 0.0;
	for (const WoodItem& w : items)
	{
		if (w.baseDeliveryTime > deliveryETA)
			deliveryETA = w.baseDeliveryTime;
	}
	return deliveryETA;
}
