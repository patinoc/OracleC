//============================================================================
// Name        : HardwoodSellerC.cpp
// Author      : Esteban Parra
// Version     : 1
// Copyright   : It's free
// Description : Main class for the Hardwood Seller
//============================================================================

#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>
#include <map>
#include "WoodItem.h"

/*
* Contains Customer's full name, address, and date of the order.
*/
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
 * Tables for each wood item's base price and delivery time
*/
std::map<std::string, double> BASE_PRICE = { { "Cherry", 5.95 },
{ "Curly Maple", 6.0 }, { "Genuine Mahogany", 9.6 }, { "Wenge", 22.35 },
{ "White Oak", 6.7 }, { "Sawdust", 1.5 } };
std::map<std::string, double> BASE_DELIVERY_TIME = { { "Cherry", 2.5 },
{ "Curly Maple", 1.5 }, { "Genuine Mahogany", 3.0 }, { "Wenge", 5.0 },
{ "White Oak", 2.3 }, { "Sawdust", 1.0 } };

int main(int argc, char* argv[]) {
	if (argc != 2)
	{
		std::cerr << "Usage: " << argv[0] << " filename\n";
		exit(1);
	}
	Customer customer;
	std::vector<WoodItem> orders;
	int total_price = 0;

	readInputFile(std::string(argv[1]), customer, orders);
	for (auto w : orders)
	{
		total_price += w.price;
	}

	std::cout << "Name: " << customer.name << '\n' << "Address: "
		<< customer.address << '\n' << "Date: " << customer.date << "\n\n";

	std::cout << std::left << std::setw(15) << "Wood Type"  
		<< std::setw(8) << "Amount" << std::setw(12) << "Price ($)" << 
		std::right << std::setw(15) << "Delivery Time (in hours)\n"
		<< "--------------------------------------------------------------\n";
	for (auto w : orders)
		std::cout << std::left << std::setw(10) << w.type << std::right << std::setw(10) << w.amount
		<< std::setprecision(2) << std::fixed << std::setw(10) << w.price << std::setw(10)
			<< w.baseDeliveryTime << '\n';

	std::cout << "\nEstimated Delivery Time: " << deliveryTime(orders) << '\n'
		      << "Total Price: $" << total_price << '\n';

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
		if (!customer_info.empty())
			parseCustomer(customer_info, customer);

		std::getline(inFile, orders_line);
		if (!orders_line.empty())
			parseOrders(orders_line, orders);
	}

}


/* 
 * Reads string of the form "<name>;<address>;<date>"
 * and populates a struct with the information
 */
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

/*
* Reads string of the form "<WoodName>:<amount>;...;<WoodName>:<amount>"
* and populates a vector of WoodItems with relevant information
*/
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
		w.amount = amount;
		w.price = amount * BASE_PRICE[w.type];
		w.baseDeliveryTime = deliveryMultiplier(amount) * BASE_DELIVERY_TIME[w.type];
		orders.push_back(w);
	}
}

/*
 * Input: bfamount, the amount of Board Foot
 * Output: The multiplier associated with the range the BF
 *         falls under.
 */
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
