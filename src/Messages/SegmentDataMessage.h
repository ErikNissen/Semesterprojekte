//
// Created by Kim Simoski on 21.11.2022.
//

#ifndef NUPPROJECT_SEGMENTDATAMESSAGE_H
#define NUPPROJECT_SEGMENTDATAMESSAGE_H

#include <iostream>
#include <cmath>

namespace messagesLib {
    /*
     * The class SegmentDataMessage represents a message containing the address of a segment (which contains a container of items) of a shelf in the inventory.
     * The class is used separately. The class is also used as a part of the class TimeSegmentMessage
     */
    class SegmentDataMessage {

        // attributes
    private:
        unsigned int shelfNumber;
        unsigned long long int row;
        unsigned long long int column;

        // constructors
    public:
        SegmentDataMessage() = default;
        SegmentDataMessage(unsigned int shelfNumber, unsigned long long int row, unsigned long long int column);


        // getters and setters
    public:
        unsigned int getShelfPairNumber();
        [[nodiscard]] unsigned long long int getRow() const;
        [[nodiscard]] unsigned long long int getColumn() const;
        [[nodiscard]]unsigned int getShelfNumber() const;

        // methods
    public:
        void print() const;
        [[nodiscard]] std::string toString() const;
    };
}

#endif //NUPPROJECT_SEGMENTDATAMESSAGE_H
