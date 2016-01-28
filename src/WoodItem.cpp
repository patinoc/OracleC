/*
 * WoodItem.cpp
 *
 *  Created on: Aug 24, 2015
 *      Author: Esteban Parra
 */

#include "WoodItem.h"
/*
 * Empty constructor
 */
WoodItem::WoodItem() {
	type = "";
	baseDeliveryTime = 0.0;
	price = 0.0;
	amount = 0;
}

WoodItem::WoodItem(std::string woodType, double deliveryTime, double itemPrice, int itemAmount) {
	type = woodType;
	baseDeliveryTime = deliveryTime;
	price = itemPrice;
	amount = itemAmount;
}
