//
// Created by Kim Simoski on 21.11.2022.
//

#include "SegmentDataMessage.h"

using namespace messagesLib;

    // constructors
    SegmentDataMessage::SegmentDataMessage(const unsigned int shelfNumber, const unsigned long long int row, const unsigned long long int column) {
        this->shelfNumber = shelfNumber;
        this->row = row;
        this->column = column;
    }

    // getters and setters
    unsigned int SegmentDataMessage::getShelfNumber() const{
        return shelfNumber;
    }

    unsigned long long int SegmentDataMessage::getRow() const{
        return row;
    }

    unsigned long long int SegmentDataMessage::getColumn() const{
        return column;
    }

    // methods
    void SegmentDataMessage::print() const {
        std::cout << toString();
    }

    std::string SegmentDataMessage::toString() const {
        std::string shelfNumberOutput = "shelf number: " + std::to_string(shelfNumber) + "\n";
        std::string rowNumberOutput = "row number: " + std::to_string(row) + "\n";
        std::string columnNumberOutput = "column number: " + std::to_string(column) + "\n";
        return shelfNumberOutput + rowNumberOutput + columnNumberOutput;
    }

    unsigned int SegmentDataMessage::getShelfPairNumber() {
        return std::ceil(static_cast<double>(shelfNumber)/2);
    }

