#include "../../include/io/Event.hpp"

bool Event::isAdd() const{
    return type == EventType::Add;
}

bool Event::isCancel() const{
    return type == EventType::Cancel;
}

bool Event::isModify() const{
    return type == EventType::Modify;
}