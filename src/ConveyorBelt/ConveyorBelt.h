/*
 * ConveyorBelt to transport Containers between the K- or I-Points and the TransferPoints
 * There is a subclass for both of these directions.
*/

#ifndef NP_SEMESTERPROJEKT_CONVEYORBELT_H
#define NP_SEMESTERPROJEKT_CONVEYORBELT_H

#include <string>


class ConveyorBelt {
public:
    ConveyorBelt();
    [[nodiscard]] float getSpeed() const;
protected:
    const float speed = 2.6f;
};


#endif //NP_SEMESTERPROJEKT_CONVEYORBELT_H
