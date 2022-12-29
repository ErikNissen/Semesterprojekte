//
// Created by alexn on 13.12.2022.
//

#ifdef _WIN32
#include <Windows.h>
#include <unistd.h>

#else
#include <unistd.h>
#endif
#include "KPoint.h"

[[maybe_unused]] KPoint::KPoint(inventoryLib::Inventory &inventory, IPoint& _iPoint) : inv{inventory}, iPoint{_iPoint} {}

// Add a Container to the KPoint for processing (this is mainly (only?) used by the RetrievingConveyorBelt)
[[maybe_unused]] void KPoint::addContainer(Container &container) {
    containersToCheck.push(container);
}

// Reserve a Container to be output from the Inventory
auto KPoint::sendTaskToInventory(TransferMessage &tm) {
    auto answer {inv.reserveContainerOutputFromInventoryToGetItems(tm.getItem())};
    if(answer) {
        /// TODO: tell the thread of this ShelfPair to wait for answer->getNeededTimeWithoutWaitingInQueueInSeconds() and then call takeContainer() to put it onto outputTransferPoint
        ///(same as checkForNonFullContainer() in IPoint)
    }
    return answer;
}

/// TODO: let a thread call this method repeatedly in a while() or implement while() in this method (whatever makes more sense)
/// when false is returned, there are currently no Containers in the queue. The while() should wait a bit before trying again (to reduce the load)
// Process the next Container in line (check if there are fitting tasks for the kind of Item contained and try to fulfill them)
[[maybe_unused]] bool KPoint::processNextContainerInQueue() {
    if(!containersToCheck.empty()) {
        // Store the first Container from the queue
        Container container = containersToCheck.front();
        // Remove from queue
        containersToCheck.pop();
        // Look through all tasks to see if some fit the ItemType in the Container
        for(auto &task : tasks) {
            // If ItemTypes match, take the necessary/highest possible amount of Items from the Container and reduce the amount within the task accordingly
            if(task.getItem().getItemId() == container.getItem().getItemId()) {
                unsigned int amountToTake {std::min(container.getCurrentAmountOfItem(), task.getAmountToTransfer())};
                container.takeAmount(amountToTake);
                task.setAmountToTransfer(task.getAmountToTransfer() - amountToTake);
                // If the task is not fulfilled, send another request to the Inventory to get another Container
                if(task.getAmountToTransfer() > 0) {
                    sendTaskToInventory(task);
                }
                // If Container is empty, no other Tasks need to be checked for this Container
                if(container.isEmpty()) {
                    break;
                }
            }
        }
        /// TODO: check if this actually works
        // Remove tasks that have had their requirements fulfilled from the vector
        tasks.erase(std::remove_if(tasks.begin(), tasks.end(),[](TransferMessage& tm) {
            return tm.getAmountToTransfer() == 0;
        }), tasks.end());

        // If the Container is still not empty, send it to the IPoint for refilling and re-storing
        if(!container.isEmpty()) {
            iPoint.addContainer(container);
        }
        return true;
    } else {
        return false;
    }
}

/// Send a task to the K-Point for removing certain amount of Items from the Inventory
[[maybe_unused]] void KPoint::sendTaskForRetrievingItems(TransferMessage &tm) {
    // Store the task within the KPoint, so it can later be executed when a fitting Container gets here
    tasks.emplace_back(tm);
    //sendTaskToInventory(tm);
}

[[maybe_unused]] void KPoint::processTasks() {
	std::cout
			<< this->tasks
			       .size()
			<< std::endl;
	if ( !tasks.empty() ) { // ToDo tasks immer leer

		auto currentTask{ tasks.front() };

		// Create container, add it to Inventory and get the fastet reachable
		// segment
		Item item = currentTask.getItem();
		auto messageOfFastestToReachSegment{
				inv.reserveContainerOutputFromInventoryToGetItems( item )
		};
		tasks.pop_back();
		int timeNeededForWayToSegmentInSecs{
				static_cast<int>(messageOfFastestToReachSegment->getNeededTimeWithoutWaitingInQueueInSeconds())
		};
		sleep( timeNeededForWayToSegmentInSecs ); //way
		// to segment
		inv.takeContainer(
				messageOfFastestToReachSegment->getSegmentDataMessage()
		);
		timeNeededForWayToSegmentInSecs
				= messageOfFastestToReachSegment->getNeededTimeForShelfWayInSeconds();
		sleep( timeNeededForWayToSegmentInSecs ); //way back from segment to input point
	}

}