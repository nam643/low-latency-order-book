#pragma once
#include<iostream>
#include "Types.hpp"

std::string sideToString(Side side);
std::string orderTypeToString(OrderType type);
bool isValidPrice(Price price);
bool isValidQuantity(Quantity qty);