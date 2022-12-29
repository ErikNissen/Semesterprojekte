//
// Created by alexn on 11.12.2022.
//


#include "IPoint.h"


[[maybe_unused]] IPoint::IPoint(inventoryLib::Inventory &inventory) : inv{inventory}, conveyor{ConveyorBeltStore()} {}

// Generate new Containers and fill them with Items
std::vector<Container> IPoint::generateContainersForItems(const Item &item, unsigned int itemCount) {
    std::vector<Container> newContainers;
    unsigned int amountOfContainers {itemCount / item.getMaxAmountPerContainer()};
    unsigned int amountOfItemsInLastContainer {itemCount % item.getMaxAmountPerContainer()};

    if(amountOfItemsInLastContainer > 0) {
        amountOfContainers++;
    } else {
        amountOfItemsInLastContainer = item.getMaxAmountPerContainer();
    }

    // Create as many full containers as possible and one last container with the rest of the items
    for(int i = 1; i <= amountOfContainers; i++){
        if(i != amountOfContainers) {
            newContainers.emplace_back(Container(item, currentContainerId, item.getMaxAmountPerContainer()));
        } else {
            newContainers.emplace_back(Container(item, currentContainerId, amountOfItemsInLastContainer));
        }
        currentContainerId++;
    }

    return newContainers;
}

// Check if there is a non-full Container with the same ItemType already in the Inventory and initiate its Output
std::optional<TimeSegmentMessage> IPoint::checkForNonFullContainersInInventory(TransferMessage& tm) {
    auto answer{inv.reserveContainerOutputFromInventoryToAddItems(tm.getItem())};
    // If there is such a container, request it to be output (to the KPoint which then sends it here)
    if(answer) {
        ///TODO: tell the thread of this ShelfPair to wait for answer->getNeededTimeWithoutWaitingInQueueInSeconds() and then call takeContainer() to put it onto outputTransferPoint
    // if not, generate new Containers until all the items fit in and send them to Inventory
    } else {
        auto containers {generateContainersForItems(tm.getItem(), tm.getAmountToTransfer())};
        for (auto &c : containers) {
            storeContainerInInventory(c);
        }
    }
    return answer;
}

// Reserve >one< Container to be stored in the Inventory and if reservation was successful, send it to the correct TransferPoint via ConveyorBelt
void IPoint::storeContainerInInventory(Container &container) {
    auto answer {inv.reserveContainerToAddToInventory(container)};
    if(answer) {
        /////// IMPORTANT: ///////
        ///TODO: call transportContainer() via std::async with the amount of time the belt needs to get the Container to the TransferPoint (?) This means a thread for each Container on Belt (too many?)
        // put Container onto ConveyorBelt and send it to the correct TransferPoint
        conveyor.transportContainer(container, inv.getShelfPairByShelfNumber(answer->getShelfPairNumber()).getInputTransferPoint());
        // wait before putting the next Container onto the ConveyorBelt
        Sleep(500);
    }
}

/// Send a task to the I-Point for storing certain amount of Items in the Inventory
void IPoint::sendTaskForStoringItems(TransferMessage tm) {
    tasks.emplace_back(tm);
    checkForNonFullContainersInInventory(tm);
}

void IPoint::addContainer(Container &container) {
    containersToCheck.emplace(container);
}

/// TODO: let a thread call this method repeatedly in a while() or implement while() in this method (whatever makes more sense)
/// when false is returned, there are currently no Containers in the queue. The while() should wait a bit before trying again (to reduce the load)
// Process the next Container in line (check if there are fitting tasks for the kind of Item contained and try to fulfill them)
[[maybe_unused]] bool IPoint::processNextContainerInQueue() {
    if(!containersToCheck.empty()) {
        // Store the first Container from the queue
        Container container = containersToCheck.front();
        // Remove from queue
        containersToCheck.pop();
        // Look through all tasks to see if some fit the ItemType in the Container
        for(auto &task : tasks) {
            if(task.getItem().getItemId() == container.getItem().getItemId()) {
                unsigned int amountToAdd {std::min(container.getAmountOfPlacesForItem(), task.getAmountToTransfer())};
                container.addAmount(amountToAdd);
                task.setAmountToTransfer(task.getAmountToTransfer() - amountToAdd);
                // If the Task is not done, send another request to Inventory
                if(task.getAmountToTransfer() > 0) {
                    checkForNonFullContainersInInventory(task);
                }
                // If Container is full, no other Tasks need to be checked for this Container
                if(!container.containsPlaceForAtLeastOnePieceOfThisItemToAdd(container.getItem())) {
                    break;
                }
            }
        }
        /// TODO: check if this actually works
        // Remove tasks that have had their requirements fulfilled from the vector
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),[](TransferMessage& tm) {
            return tm.getAmountToTransfer() == 0;
        }), tasks.end());

        storeContainerInInventory(container);

        return true;
    } else {
        return false;
    }
}


[[maybe_unused]] void IPoint::processTasks(){
	std::cout << this->tasks.size() << std::endl;
	if(!tasks.empty()) { // ToDo tasks immer leer

		auto currentTask{ tasks.front() };

		// Create container, add it to Inventory and get the fastet reachable
		// segment
		Container container = Container(currentTask.getItem(), 1, currentTask.getAmountToTransfer());
		auto messageOfFastestToReachSegment{
				inv.reserveContainerToAddToInventory( container )
		};
		tasks.pop_back();
		int timeNeededForWayToSegmentInSecs{
				static_cast<int>(messageOfFastestToReachSegment->getNeededTimeWithoutWaitingInQueueInSeconds())
		};
		sleep( timeNeededForWayToSegmentInSecs ); //way
		// to segment
		inv.addContainer(
				messageOfFastestToReachSegment->getSegmentDataMessage(),
				container
		);
		timeNeededForWayToSegmentInSecs
				= messageOfFastestToReachSegment->getNeededTimeForShelfWayInSeconds();
		sleep( timeNeededForWayToSegmentInSecs ); //way back from segment to input point
	}
}