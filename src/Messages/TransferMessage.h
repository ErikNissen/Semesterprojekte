//
// Created by Kim Simoski on 22.11.2022.
//

#ifndef NUPPROJECT_TRANSFERMESSAGE_H
#define NUPPROJECT_TRANSFERMESSAGE_H

#include "../Item/Item.h"

namespace messagesLib {

    /*
     * The class TransferMessage represents a message for a transfer for input or output.
     * It contains an item (Item) and an amount to transfer.
     * It is used by methods to book, add and get in the inventory (Inventory).
     */
    class TransferMessage {
        // attributes
    private:
        itemLib::Item item{};
        unsigned int amountToTransfer{};

        // getters and setters
    public:
        [[nodiscard]] const itemLib::Item &getItem() const;
        [[nodiscard]] unsigned int getAmountToTransfer() const;
        void setAmountToTransfer(unsigned int);

        // constructors
        TransferMessage() = default;
        TransferMessage(const itemLib::Item &item, unsigned int amountToTransfer);

    public:

    }; // Inventory
}


#endif //NUPPROJECT_TRANSFERMESSAGE_H
