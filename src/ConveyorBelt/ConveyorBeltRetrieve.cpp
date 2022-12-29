//
// Created by alexn on 21.11.2022.
//

#include "ConveyorBeltRetrieve.h"

ConveyorBeltRetrieve::ConveyorBeltRetrieve(KPoint& _kPoint) : ConveyorBelt(), kPoint{_kPoint} {}

// Transport a Container from a TransferPoint to the K-Point
void ConveyorBeltRetrieve::transportContainer(Container &_container, float distance) {
    // Calculate the time it takes to transport the Container the TransferPoint to the K-Point
    float timeOfTransport = distance / this->getSpeed();
    _container.getTimer().addSeconds(timeOfTransport);
    std::cout << "Transported Container \"" << _container.getId() << "\" via ConveyorBelt. Took " << timeOfTransport <<
              " seconds. Timer now at: " << _container.getTimer().getTimeInSeconds() << std::endl;
    kPoint.addContainer(_container);
}
