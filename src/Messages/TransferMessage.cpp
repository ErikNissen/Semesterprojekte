//
// Created by Kim Simoski on 22.11.2022.
//

#include "TransferMessage.h"

using namespace messagesLib;

// getters and setters
const itemLib::Item &TransferMessage::getItem() const {
    return item;
}

unsigned int TransferMessage::getAmountToTransfer() const {
    return amountToTransfer;
}

// constructors
//!!! Den Konstruktor zu einem klassischen Konstruktor umformen, oder die anderen an diese Form anpassen !!!
TransferMessage::TransferMessage(const itemLib::Item &item, unsigned int amountToTransfer) : item(item),
                                                                                             amountToTransfer(
                                                                                                     amountToTransfer) {}

void TransferMessage::setAmountToTransfer(unsigned int newAmount) {
    amountToTransfer = newAmount;
}
