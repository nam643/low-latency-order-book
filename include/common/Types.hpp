#pragma once
#include <cstdint>

enum class Side {Buy, Sell};
enum class OrderType {Limit, Market};
enum class EventType {Add, Cancel, Modify};
using OrderId = std::uint64_t;
using Price = std::uint64_t;
using Quantity = std::uint64_t;
using Timestamp = std::uint64_t;