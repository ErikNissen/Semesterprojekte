//
// Created by alexn on 13.12.2022.
//

/*
 * This class handles the retrieving of Items from the Inventory.
 * It can receive tasks (TransferMessages) to retrieve a certain amount of a certain Item
 * and will try to fulfill them by requesting Containers from the Inventory and removing the Items from them.
 * When a Container is not empty after checking through all current tasks,
 * it is send to the IPoint for re-storing into the Inventory.
 * Empty Containers are discarded.
 */

#ifndef NP_SEMESTERPROJEKT_KPOINT_H
#define NP_SEMESTERPROJEKT_KPOINT_H

#include "Inventory.h"
#include "IPoint.h"


class [[maybe_unused]] KPoint {

	// attributes
private:
	std::queue<Container> containersToCheck; //ToDo
	inventoryLib::Inventory& inv;
	std::vector<TransferMessage> tasks; //ToDo: Von außen (Warehouse)
	// zufällige Tasks erzeugen und hier einfügen über sendTaskToInventory()
	IPoint& iPoint;

	//methods
public:
	[[maybe_unused]] explicit KPoint(inventoryLib::Inventory&, IPoint&);

	[[maybe_unused]] void addContainer(Container&);

	[[maybe_unused]] bool processNextContainerInQueue();

	[[maybe_unused]] void sendTaskForRetrievingItems(TransferMessage&);

	void processTasks();

	auto sendTaskToInventory(TransferMessage&);




};


#endif //NP_SEMESTERPROJEKT_KPOINT_H
