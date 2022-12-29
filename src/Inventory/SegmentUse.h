//
// Created by Kim Simoski on 04.12.2022.
//

#ifndef NP_SEMESTERPROJEKT_SEGMENTUSE_H
#define NP_SEMESTERPROJEKT_SEGMENTUSE_H


namespace inventoryLib {

    /*
     * The class SegmentUse represents the different selection criteria for searching the fastest container (Segment) to reach depending of the current purpose.
     * This class is used by the Class Shelf.
     * InitPrio is for initiating the priority of each container once depending on the percentages per priority level.
     * AddItemToContainer is used to add an amount of a specific item to a container.
     * GetItemFromContainer is used to get an amount of a specific item from a container.
     */
    //!!! Diese Klasse könnte über Nutzen von Polymorphie wegrationalisiert werden !!!
    enum class SegmentUse {
        InitPrio = 0, AddItemToContainer = 1, GetItemFromContainer = 2, AddContainerToSegment = 3
    };

} // inventoryLib

#endif //NP_SEMESTERPROJEKT_SEGMENTUSE_H


