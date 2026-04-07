#include "../../include/core/MatchingEngine.hpp"
#include <stdexcept>
#include <algorithm>

MatchingEngine::MatchingEngine():book_(),sequence_(0){}

bool MatchingEngine::shouldMatch(const Order& incoming) const{
    return book_.canMatch(incoming);
}

Price MatchingEngine::determineExecutionPrice(const Order& resting, const Order& incoming) const{
    return resting.price;
}

Trade MatchingEngine::createTrade(
    const Order& incoming,
    const Order& resting,
    Quantity qty,
    Price price,
    Timestamp ts
){
    if(incoming.side == Side::Buy){
        return Trade(incoming.id, resting.id,price,qty,ts);
    }
    else if(incoming.side == Side::Sell){
        return Trade(resting.id, incoming.id,price,qty,ts);
    }

    throw std::invalid_argument("Invalid incoming side when creating trade");
}

void MatchingEngine::matchBuyOrder(Order& incoming,  ExecutionReport& report){
    while(incoming.remainingQuantity > 0 && shouldMatch(incoming)){
        PriceLevel& bestAskLevel = book_.getBestOpposingLevel(Side::Buy);
        Order& resting = bestAskLevel.frontOrder();

        Quantity fillQty = std::min(incoming.remainingQuantity, resting.remainingQuantity);
        Price execPrice = determineExecutionPrice(resting, incoming);

        Trade trade = createTrade(incoming, resting, fillQty, execPrice, sequence_++);
        report.addTrade(trade);
        
        OrderId restingId = resting.id;

        incoming.fill(fillQty);
        resting.fill(fillQty);

        if(resting.isFilled()){
            book_.cancelOrder(restingId);
        }
        else{
            bestAskLevel.updateTotalQuantity();
        }
    }
}

void MatchingEngine::matchSellOrder(Order& incoming, ExecutionReport& report){
    while (incoming.remainingQuantity > 0 && shouldMatch(incoming)) {
        PriceLevel& bestBidLevel = book_.getBestOpposingLevel(Side::Sell);
        Order& resting = bestBidLevel.frontOrder();

        Quantity fillQty = std::min(incoming.remainingQuantity, resting.remainingQuantity);
        Price execPrice = determineExecutionPrice(resting, incoming);

        Trade trade = createTrade(incoming, resting, fillQty, execPrice, sequence_++);
        report.addTrade(trade);

        OrderId restingId = resting.id;

        incoming.fill(fillQty);
        resting.fill(fillQty);

        if (resting.isFilled()) {
            book_.cancelOrder(restingId);
        } else {
            bestBidLevel.updateTotalQuantity();
        }
    }
}

ExecutionReport MatchingEngine::matchIncomingOrder(Order incoming){
    ExecutionReport report;
    report.setAccepted(true);
    report.setMessage("Order processed");

    if(incoming.side == Side::Buy){
        matchBuyOrder(incoming, report);
    }
    else if(incoming.side == Side::Sell){
        matchSellOrder(incoming,report);
    }
    else{
        report.setAccepted(false);
        report.setMessage("Invalid incoming side");
        return report;
    }

    if(incoming.remainingQuantity > 0 && incoming.type == OrderType::Limit){
        book_.addOrder(incoming);
    }

    return report;
}

ExecutionReport MatchingEngine::processAddOrder(const Order& incoming){
    return matchIncomingOrder(incoming);
}

ExecutionReport MatchingEngine::processCancelOrder(OrderId id){
    ExecutionReport report;

    if(book_.cancelOrder(id)){
        report.setAccepted(true);
        report.setMessage("Order cancelled successfully");
    }else{
        report.setAccepted(false);
        report.setMessage("Order not found");
    }

    return report;
}

ExecutionReport MatchingEngine::processModifyOrder(OrderId id, Price newPrice, Quantity newQty){
    ExecutionReport report;

    if(book_.modifyOrder(id,newPrice, newQty, sequence_++)){
        report.setAccepted(true);
        report.setMessage("Order modified successfully");
    }else{
        report.setAccepted(false);
        report.setMessage("Order modification failed");
    }

    return report;
}

const OrderBook& MatchingEngine::getOrderBook() const{
    return book_;
}

OrderBook& MatchingEngine::getOrderBook(){
    return book_;
}

void MatchingEngine::reset(){
    book_ = OrderBook();
    sequence_ = 0;
}

ExecutionReport MatchingEngine::processEvent(const Event& event){
    if(event.isAdd()){
        Order order(
            event.orderId,
            event.side,
            event.orderType,
            event.price,
            event.quantity,
            event.timestamp
        );
        return processAddOrder(order);
    }
    else if(event.isCancel()){
        return processCancelOrder(event.orderId);
    }
    else if(event.isModify()){
        return processModifyOrder(event.orderId, event.price, event.quantity);
    }

    ExecutionReport report;
    report.setAccepted(false);
    report.setMessage("Unknown event type");
    return report;
}