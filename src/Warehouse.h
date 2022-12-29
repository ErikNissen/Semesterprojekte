//
// Created by alexn on 19.12.2022.
//

#ifndef NP_SEMESTERPROJEKT_WAREHOUSE_H
#define NP_SEMESTERPROJEKT_WAREHOUSE_H


#include "Inventory.h"
#include "IPoint.h"
#include "KPoint.h"
#include "ConveyorBeltRetrieve.h"
#include <unistd.h>
//#include <ntgdi.h>

class Warehouse {
public:
	// constructors
    Warehouse();

	// getters and setters
	[[nodiscard]] IPoint getIPoint() const;
	[[nodiscard]] KPoint getKPoint() const;

private:
	// attributes
    inventoryLib::Inventory inventory;
    IPoint iPoint;
    KPoint kPoint;
    ConveyorBeltStore conveyorStore;
    ConveyorBeltRetrieve conveyorRetrieve;


	void testing();

	// methods
public:
	void sendTaskForStoringItems();
	void orderIPointToExecuteFirstTask(); //For sequentiell testing
	void sendTaskForRetrievingItems();
	void orderKPointToExecuteFirstTask();
};


#endif //NP_SEMESTERPROJEKT_WAREHOUSE_H
