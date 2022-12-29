//
// Created by Kim Simoski on 21.11.2022.
//

#include "TimeSegmentMessage.h"

using namespace messagesLib;

    // constructors
    TimeSegmentMessage::TimeSegmentMessage() = default;

    TimeSegmentMessage::TimeSegmentMessage(const double neededTimeForShelfWayInSeconds, const double neededTimeWithoutWaitingInQueueInSeconds, const unsigned int shelfPairNumber, const unsigned int shelfNumber, const unsigned long long int row, unsigned long long int column){
        this->neededTimeForShelfWayInSeconds = neededTimeForShelfWayInSeconds;
        this->neededTimeWithoutWaitingInQueueInSeconds = neededTimeWithoutWaitingInQueueInSeconds;
        this->shelfPairNumber = shelfPairNumber; //!!! Kann mit Suchmechanismus in ShelfPair auch wegrationalisiert werden, da sie aus einander hergeleitet werden können!!!
        this->segmentDataMessage = SegmentDataMessage{shelfNumber, row, column};
    }

    TimeSegmentMessage::TimeSegmentMessage(const double neededTimeForShelfWayInSeconds, const double neededTimeWithoutWaitingInQueueInSeconds,
                                           const SegmentDataMessage& segmentDataMessage) {
        this->neededTimeForShelfWayInSeconds = neededTimeForShelfWayInSeconds;
        this->neededTimeWithoutWaitingInQueueInSeconds = neededTimeWithoutWaitingInQueueInSeconds;
        this->shelfPairNumber = std::ceil(segmentDataMessage.getShelfNumber()/2); //!!! Kann mit Suchmechanismus in ShelfPair auch wegrationalisiert werden, da sie aus einander hergeleitet werden können!!!
        this->segmentDataMessage = SegmentDataMessage{segmentDataMessage};

    }


    // getters and setters
    double TimeSegmentMessage::getNeededTimeForShelfWayInSeconds() const{
        return neededTimeForShelfWayInSeconds;
    }
    double TimeSegmentMessage::getNeededTimeWithoutWaitingInQueueInSeconds() const{
        return neededTimeWithoutWaitingInQueueInSeconds;
    }
    unsigned int TimeSegmentMessage::getShelfPairNumber() const{ //!!! Kann mit Suchmechanismus in ShelfPair auch wegrationalisiert werden, da sie aus einander hergeleitet werden können!!!
        return shelfPairNumber;
    }
    unsigned int TimeSegmentMessage::getShelfNumber(){
        return segmentDataMessage.getShelfNumber();
    }
    unsigned long long int TimeSegmentMessage::getRow(){
        return segmentDataMessage.getRow();
    }
    unsigned long long int TimeSegmentMessage::getColumn(){
        return segmentDataMessage.getColumn();
    }

    SegmentDataMessage TimeSegmentMessage::getSegmentDataMessage() {
        return segmentDataMessage;
    }

    // methods
    void TimeSegmentMessage::print() {
        //!!! For Debugging!!!
        std::cout << "!Der aktuell schnellste Weg zu einem freien Container:!" << std::endl;
        std::cout << toString();
    }

    std::string TimeSegmentMessage::toString() {
        std::string segmentDataMessageOutput{segmentDataMessage.toString()};
        std::string neededTimeWithoutWaitingInQueueInSecondsOutput{" needed time without waiting in queue in seconds: " + std::to_string(neededTimeWithoutWaitingInQueueInSeconds) + "\n"};
        return segmentDataMessageOutput + neededTimeWithoutWaitingInQueueInSecondsOutput;
    }