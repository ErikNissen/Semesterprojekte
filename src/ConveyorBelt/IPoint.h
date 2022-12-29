//
// Created by alexn on 11.12.2022.
//

/*
 * This class handles the storing of Items into the Inventory.
 * It can receive tasks (TransferMessages) to store a certain amount of a certain Item
 * and will try to fulfill them by filling existing Containers or generating new ones.
 * It also checks for incoming Containers from the KPoint and uses them for fulfilling tasks
 * before sending them back to the Inventory.
 */

#ifndef NP_SEMESTERPROJEKT_IPOINT_H
#define NP_SEMESTERPROJEKT_IPOINT_H

#include <unistd.h>
#include "Inventory.h"
#include "ConveyorBeltStore.h"

class IPoint {
public:
	[[maybe_unused]] explicit IPoint(inventoryLib::Inventory&);
    void storeContainerInInventory(Container&);
    void sendTaskForStoringItems(TransferMessage);
    void addContainer(Container&);

	[[maybe_unused]] bool processNextContainerInQueue();

	[[maybe_unused]] void processTasks();
private:
    inventoryLib::Inventory& inv;
    ConveyorBeltStore conveyor;
    std::vector<TransferMessage> tasks;
    std::queue<Container> containersToCheck;
    unsigned int currentContainerId = 1;
    std::optional<TimeSegmentMessage> checkForNonFullContainersInInventory(TransferMessage&);
    std::vector<Container> generateContainersForItems(const itemLib::Item&, unsigned int itemCount);
};


#endif //NP_SEMESTERPROJEKT_IPOINT_H
