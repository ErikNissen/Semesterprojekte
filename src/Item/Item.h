//
// Created by Kim Simoski on 22.11.2022.
//

#ifndef NUPPROJECT_ITEM_H
#define NUPPROJECT_ITEM_H

#include <bits/stdc++.h>
#include "Priority.h"
#include "../../_deps/json-src/single_include/nlohmann/json.hpp"
#include "../PersistentFileManagement/PersistentFileManagement.hpp"

namespace itemLib {

    /*
     * The class Item represents different items with different priority levels (Priority), a specific maximum amount of this item per container (Segment).
     * Items get moved by the conveyor belt to a waiting queue of a shelf pair for adding them to the inventory.
     * Items get moved by one transport vehicle per shelf pair beetween the waiting point for the input, the shelf pair and the waiting point for the output.
     */
    class Item {

        // attributes
    private:
        unsigned int itemID{};
        Priority priority{Priority::N};
        unsigned int maxAmountPerContainer{};

        // constructors
    public:
        Item() = default;
        explicit Item(const unsigned int itemId);
        //explicit Item(const Priority& priority);
        Item(unsigned int itemId, Priority priority, unsigned int maxAmountPerContainer);

        // getters and setters
    public:
        [[nodiscard]] unsigned int getItemId() const;
        [[nodiscard]] Priority getPriority() const;
        [[nodiscard]] unsigned int getMaxAmountPerContainer() const;

        // methods
    private:
        void printPriority();

    public:

        //ToDo: evtl. später wieder private machen, falls die Methode nur in Constructor und Destructor aufgerufen wird
        void saveAsJSONFile() const;

        void print();
		// ToDo Erik Nissen
		std::string toString();

    };
}


#endif //NUPPROJECT_ITEM_H
