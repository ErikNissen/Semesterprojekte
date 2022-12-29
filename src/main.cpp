#include "main.hpp"
#include <algorithm>
#include "Inventory.h"
#include "ConveyorBeltStore.h"
#include "ConveyorBeltRetrieve.h"
#include "PersistentFileManagement/PersistentFileManagement.hpp"
#include <thread>

int main (int argc, char *argv[]) {
	Warehouse warehouse{};
//	warehouse.testing();

// everything what need to be endless
    endlessThread(warehouse);

    return 0;
}

void endlessThread(Warehouse& warehouse){
    std::jthread iHandler( endlessThreadHandlerIPoint, std::ref( warehouse));
    std::jthread kHandler( endlessThreadHandlerKPoint, std::ref( warehouse));
}

[[noreturn]] void endlessThreadHandlerIPoint( Warehouse& warehouse) {
    while (true) {
        warehouse.getIPoint().processNextContainerInQueue();
		warehouse.sendTaskForStoringItems();
	    warehouse.orderIPointToExecuteFirstTask(); //!!! for testing
	    sleep(0);
    }
}

[[noreturn]] void endlessThreadHandlerKPoint( Warehouse& warehouse) {
    while (true) {
        warehouse.getKPoint().processNextContainerInQueue();
	    warehouse.sendTaskForStoringItems();
		warehouse.sendTaskForRetrievingItems();
	    sleep(0);
    }
}