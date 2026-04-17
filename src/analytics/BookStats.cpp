#include "../../include/analytics/BookStats.hpp"

Price BookStats::midPrice(const OrderBook& book) {
    if (book.empty(Side::Buy) || book.empty(Side::Sell)) {
        return 0;
    }

    return (book.getBestBid() + book.getBestAsk()) / 2;
}

Price BookStats::spread(const OrderBook& book) {
    if (book.empty(Side::Buy) || book.empty(Side::Sell)) {
        return 0;
    }

    return book.getBestAsk() - book.getBestBid();
}

Quantity BookStats::totalBidVolume(const OrderBook& book, std::size_t depth) {
    Quantity total = 0;
    const auto levels = book.getBidDepth(depth);

    for (const auto& [price, qty] : levels) {
        (void)price;
        total += qty;
    }

    return total;
}

Quantity BookStats::totalAskVolume(const OrderBook& book, std::size_t depth) {
    Quantity total = 0;
    const auto levels = book.getAskDepth(depth);

    for (const auto& [price, qty] : levels) {
        (void)price;
        total += qty;
    }

    return total;
}

double BookStats::imbalance(const OrderBook& book, std::size_t depth) {
    const Quantity bidVol = totalBidVolume(book, depth);
    const Quantity askVol = totalAskVolume(book, depth);
    const Quantity total = bidVol + askVol;

    if (total == 0) {
        return 0.0;
    }

    return static_cast<double>(bidVol) / static_cast<double>(total);
}