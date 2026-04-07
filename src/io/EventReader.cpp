#include "../../include/io/EventReader.hpp"
#include <stdexcept>

EventReader :: EventReader(const std::string& filename){
    CSVParser csv;
    events_ = csv.parseFile(filename);
    currentIndex_ = 0;
}

bool EventReader::hasNext() const{
    return currentIndex_ < events_.size();
}

Event EventReader::next(){
    if(!hasNext()){
        throw std::invalid_argument("Reached the end of the events");
    }

    return events_[currentIndex_++];
}

std::vector<Event> EventReader::readAll() const{
    return events_;
}