/*
 * WoodItem.h
 *
 *  Created on: Aug 24, 2015
 *      Author: Esteban
 */


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#ifndef WOODITEM_H_
#define WOODITEM_H_

class WoodItem {
public:

	std::string type;
	double baseDeliveryTime;
	double price;
	int amount;

	// Member functions declaration
	WoodItem();
	WoodItem(std::string woodType, double deliveryTime, double itemPrice, int itemAmount);

};

#endif /* WOODITEM_H_ */
