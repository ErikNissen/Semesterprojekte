//
// Created by Kim Simoski on 27.11.2022.
//

#ifndef NUPPROJECT_SHELFCONTAINER_H
#define NUPPROJECT_SHELFCONTAINER_H

#include "../Item/Priority.h"
#include "../PersistentFileManagement/PersistentFileManagement.hpp"
#include "../../_deps/json-src/single_include/nlohmann/json.hpp"
#include "../Item/Item.h"
#include "../Messages/TransferMessage.h"
#include "../Item/Container.h"




// container for containing items with amounts and priorities in a shelf segment per container

using namespace itemLib;
using namespace messagesLib;

namespace inventoryLib {
    /*
    * The class Segment is contained by the class Shelf. It represents a segment of the shelf for containing one container which contains an amount of items (Item).
    * The class provides methods to store or restore containers. There are also methods to reserve for adding one container to the segment and for getting the container from the segment.
    * A container which contains items with a priority level can only be added to a segment with a matching priority level (Priority)
    */
    class Segment {

// attributes
//ToDo: Container evtl. stattdessen als Unique-Pointer umsetzen und dafür move-Befehle zum Bewegen nutzen und Konstruktoren anpassen
    private:
        unsigned int segmentId{};
        Priority priority{Priority::N};
        Container container{Item()};

        // if a container is send to a segment but hasn't reached it yet, the segment cannot be adressed by an other container.
        // similiar if a segment is reserved for its containers output.
        bool segmentReservedForContainerInput{false};
        bool segmentReservedForContainerOutput{false};


        // constructors
    public:
        Segment();
        explicit Segment(unsigned int shelfNumber, unsigned int rowNumber, unsigned int columnNumber);
        explicit Segment(unsigned int id);

        //ToDo: Constructors löschen, die nicht benötigt werden
        explicit Segment(unsigned int shelfNumber, unsigned int rowNumber, unsigned int columnNumber, const Priority& priority);
        explicit Segment(unsigned int id, const Priority& priority);
        Segment(unsigned int id, const Priority &priority, const Container &container);

        // getters and setters
    public:

        [[nodiscard]] unsigned int getId() const;

	    [[maybe_unused]] [[nodiscard]] Priority getPriority() const;
        void setPriority(const Priority &priority);

	    [[maybe_unused]] [[nodiscard]] const Container &getContainer() const;
        void setContainer(const Container &newContainer);

        //ToDO: Setter der flags hinterher private machen
        void setSegmentReservedForContainerInput(bool segmentReservedForContainerInput);
        void setSegmentMarkedForContainerOutput(bool segmentMarkedForContainerOutput);

        [[nodiscard]] bool isSegmentReservedForContainerOutput() const;
        [[nodiscard]] bool isSegmentReservedForContainerInput() const;

        //unsigned int getMaxAmountOfItem(); // gets max amount of contained item
        //void appendItemType(const TransferMessage &transferMessage);

        //methods
    private:


        void deleteReservationFromSegmentToAddContainer();
        void deleteReservationFromSegmentToGetContainer();


    public:

        //ToDo: evtl. später private machen, falls die Methode nur im eigenen Constructor und Destructor aufgerufen werden
        void saveAsJSONFile();

        unsigned int encodeSegmentId(const unsigned int shelfNumber, const unsigned int rowNumber, const unsigned int columnNumber);
        unsigned int getShelfNumberFromSegmentId();
        unsigned int getRowNumberFromSegmentId();
        unsigned int getColumnNumberFromSegmentId();

        void reserveSegmentToGetContainer();
        void reserveSegmentToAddContainer();

        void addContainer(const Container &newContainer);
        Container takeContainer();

        bool containsContainer();

        bool hasNoPriorityLevel(); // for initializing the containers priority levels only once to reserve percentages of container amounts for different priority levels
        bool hasMatchingPriorityLevel(const Item &item);

        bool containsNoContainerAndHasMatchingPrio(const Item &item);
        bool containsAtLeastOnePieceOfThisItemToGet(const Item& item);
        bool containsPlaceForAtLeastOnePieceOfThisItemToAdd(const Item& item);

        void print();
        void printPriority();
		std::string toString();




        /*
           private:

         void ifEmptyAndNotReservedToAddDeleteItemType(); // for getting used while taking the last items from a container if there are currently no reservations for adding to enable storing a new kind of item

        bool isEmpty();
        [[nodiscard]] bool containsAmountToGet(unsigned int amount) const;
        bool containsPlaceForAmountToAdd(unsigned int amount);
        bool containsItemsOfSameItemKind(const TransferMessage &transferMessage);
        bool hasMatchingPriorityLevel(const TransferMessage& transferMessage);

        void reserveAmountToAdd(unsigned int amount);
        void reserveAmountToTake(unsigned int amount);

        void addAmount(unsigned int amount);
        void takeAmount(unsigned int amount);
*/




        /*
        bool containsAmountToGetOfThisItem(const TransferMessage& transferMessage);
        bool containsPlaceForAmountToAddOfThisItem(const TransferMessage& transferMessage);

        //!!! Reservieren bei Wahl des Laufbands aufrufen. Hinzufügen und abziehen erst aufrufen, wenn die Bedienhilfe tatsächlich angekommen ist !!!
        //!!! bei folgenden Methoden vllt. als bool zurückgeben, ob es geklappt hat!!!
        void reserveAmountToAddForItem(const TransferMessage &transferMessage);
        void reserveAmountToTakeForItem(const TransferMessage &transferMessage);

        void addAmount(const TransferMessage &transferMessage);
        void takeAmount(const TransferMessage &transferMessage);
         */

    };
}

#endif //NUPPROJECT_SHELFCONTAINER_H
