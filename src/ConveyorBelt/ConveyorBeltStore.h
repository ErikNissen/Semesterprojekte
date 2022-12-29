/*
 * This ConveyorBelt is used only for storing Containers onto the TransferPoints.
*/

#ifndef NP_SEMESTERPROJEKT_CONVEYORBELTSTORE_H
#define NP_SEMESTERPROJEKT_CONVEYORBELTSTORE_H

#include "ConveyorBelt.h"
#include "TransferPoint.h"


class ConveyorBeltStore : public ConveyorBelt {
public:
    ConveyorBeltStore();
    void transportContainer(Container&, TransferPoint&);
};


#endif //NP_SEMESTERPROJEKT_CONVEYORBELTSTORE_H
