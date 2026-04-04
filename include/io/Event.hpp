#include "../common/Types.hpp"

class Event {
public:
    EventType type;
    Timestamp timestamp;
    OrderId orderId;
    Side side;
    OrderType orderType;
    Price price;
    Quantity quantity;

    bool isAdd() const;
    bool isCancel() const;
    bool isModify() const;
};