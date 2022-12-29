//
// Created by Kim Simoski on 22.11.2022.
//

#ifndef NUPPROJECT_PRIORITY_H
#define NUPPROJECT_PRIORITY_H

namespace itemLib {
    /*
    * The class Priority represents the different priority levels of items (Item).
    * Based on the planned amount of items per priority level segments (Segment) gets reserved for managing containers which contain items of the same priority level.
    * The higher the priority (lower number/letter), the chosen containers gets put are faster to reach than the ones with lower priority levels (higher number/letter)
    * This class is used by the Class Item and the class Segment.
    * N is the representation of an uninitalized priority level.
    * A, B, C are priority levels with descending priority level.
    */
    enum class Priority {
        N = 0, A = 1, B = 2, C = 3
    };
}

#endif //NUPPROJECT_PRIORITY_H
