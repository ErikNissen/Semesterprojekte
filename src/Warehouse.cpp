//
// Created by alexn on 19.12.2022.
//

#include "Warehouse.h"

// initialize all parts of the system
Warehouse::Warehouse() : iPoint {inventory}, kPoint{inventory, iPoint}, conveyorRetrieve{kPoint}, inventory{
                                   8, 90, 2, 2.6, 10, 5, 5,
                                   0.8, 0.5, 3.5, 0.4,
                                   1.2, 49.6, 28.0, 0.7,
                                   1.5, 0.0, 0.1,
                                   0.45, 0.45, 0.65, 0.4, 0.4,
                                   0.6}
                                   {
                                       inventory.printShelfSegments();
                                   }

IPoint Warehouse::getIPoint() const {
    return iPoint;
}

KPoint Warehouse::getKPoint() const {
    return kPoint;
}

// methods

void Warehouse::sendTaskForStoringItems(){
	//for(auto i{0}; i<20; i++) {
		sleep( 0.5 );
		auto t = TransferMessage(Item(1, Priority::A, 5),2);
		this->iPoint.sendTaskForStoringItems(t);
	//}
}

void Warehouse::sendTaskForRetrievingItems(){
	//for(auto i{0}; i<20; i++) {
		sleep( 0.5 );
		auto t = TransferMessage(Item(1, Priority::A, 5),2);
		this->kPoint.sendTaskForRetrievingItems(t);
	//}
}


void Warehouse::orderIPointToExecuteFirstTask(){
	this->iPoint.processTasks();
}

void Warehouse::orderKPointToExecuteFirstTask(){
	this->kPoint.processTasks();
}

// random tests
void Warehouse::testing() {
// test adding containers
    Item item{1, Priority::A, 5};
    Container container{item};
    container.addAmount(container.getAmountOfPlacesForItem() - 1);

    auto pfm = PersistentFileManagement("log");

    using namespace std::chrono_literals;
    std::chrono::duration<int> minTime = std::chrono::seconds(5s);
    std::chrono::duration<int> maxTime = std::chrono::seconds(7s);
    pfm.log(minTime, maxTime, inventory.toString());

    //ToDO: Fehlerkommentare in Englisch übersetzen
    // test reserving segment for container input at the fastest to reach segment
    auto fastestToReachSegmentToAddContainer{inventory.reserveContainerToAddToInventory(container)};
    if (fastestToReachSegmentToAddContainer) {
        std::cout
                << "Das aktuell schnellste zu erreichende Segment mit passender Priorität zum Hinzufügen eines Containers: "
                << std::endl;
        inventory.addContainer(fastestToReachSegmentToAddContainer->getSegmentDataMessage(), container);
    } else {
        std::cout << "Aktuell steht kein Segment zum Hinzufügen eines Containers dieser Priorität zur Verfügung."
                  << std::endl;
    }

    std::cout
            << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> after adding container to shelf 1, row 1, segment 1: <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<"
            << std::endl;
    inventory.printShelfSegments();

    /*
    // test reserving segment for container output for adding item to fastest to reach container
    auto fastestToReachContainerToAddItems{inventory.reserveContainerOutputFromInventoryToAddItems(item)};
    if(fastestToReachContainerToAddItems) {
        std::cout << "Der aktuell schnellste zu erreichende Container zum Hinzufügen von Items: " << std::endl;
        fastestToReachContainerToAddItems->print();
    }
    else{
        std::cout << "Aktuell steht kein Container zum Hinzufügen von Items zur Verfügung." << std::endl;
    }
    */

    // test reserving segment for container output for adding item to fastest to reach container
    auto fastestToReachContainerToGetItems{inventory.reserveContainerOutputFromInventoryToGetItems(item)};
    if (fastestToReachContainerToGetItems) {
        std::cout << "Der aktuell schnellste zu erreichende Container zum Entnehmen von Items: " << std::endl;
        fastestToReachContainerToGetItems->print();
    } else {
        std::cout << "Aktuell steht kein Container zum Entnehmen von Items zur Verfügung." << std::endl;
    }
}
