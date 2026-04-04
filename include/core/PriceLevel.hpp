#pragma once

#include "../common/Types.hpp"
#include "Order.hpp"
#include <cstddef>
#include <list>

class PriceLevel{
private:
    Price price_;
    std::list<Order> orders_;
    Quantity totalQuantity_;
public:
    explicit PriceLevel(Price price);

    Price getPrice() const;
    Quantity getTotalQuantity() const;
    bool empty() const;
    std::size_t orderCount() const;

    void addOrder(const Order& order);
    void removeFrontOrder();
    void removeOrderById(OrderId id);
    Order& frontOrder();
    const Order& frontOrder() const;

    std::list<Order>& getOrders();
    const std::list<Order>& getOrders() const;

    void updateTotalQuantity();
};