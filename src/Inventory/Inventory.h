//
// Created by Kim Simoski on 19.11.2022.
//

#ifndef NUPPROJECT_INVENTORY_H
#define NUPPROJECT_INVENTORY_H

#include "ShelfPair.h"
#include "SegmentUse.h"
#include "../PersistentFileManagement/PersistentFileManagement.hpp"
#include "../../_deps/json-src/single_include/nlohmann/json.hpp"
#include <cmath>

namespace inventoryLib {
    /*
     * The class Inventory represents the whole inventory containing several shelfpairs (ShelfPair) which contain two shelves (Shelf) per pair. Each shelf has rows with coloumns as segments containting containers (Segment) for containing items (Item)
     * The class provides methods to store or restore items. For reservations there are also methods to reserve for adding to and to reserve for getting from the inventory.
     * The class uses methods to calculate the fastest possible ways to shelf segments for storation processes.
     * The storage positions are based on three different levels of priority of items.
     */
    //!!! Segment und Container nicht synonym verwenden. Für Methoden Entscheidung für eins der beiden Treffen und Bezeichner überarbeiten !!!
    class Inventory {

        //attributes
    private:

        std::vector<ShelfPair> shelfPairs;
    public:
	    void setShelfPairs( const std::vector<ShelfPair> &shelfPairs );

    private:

	    // log_data


        // counts
        [[maybe_unused]] unsigned int amountOfShelves;

	    [[maybe_unused]] unsigned long long int rowsPerShelf;
	    [[maybe_unused]] unsigned long long int segmentsPerRow;


        // measurements

        // conveyor belt
        [[maybe_unused]] double conveyorBeltVelocity; // needed for finding the matching segment with the shortest way by regarding the way between shelf pairs

        /*
        // transport vehicle
        double verticalMaxVelocityInMetersPerSecond;
        double verticalAccelerationInMetersPerSquareSeconds;

        double horizontalMaxVelocityInMetersPerSecond;
        double horizontalAccelerationInMetersPerSquareSeconds;

        //!!! evtl. alle Objekte mit Höhe, Breite, Tiefe mit gemeinsamer Vererbung umsetzen !!!
        */
        // inventory
        [[maybe_unused]] double distanceBetweenShelves;

	    [[maybe_unused]] unsigned int percentageOfPriorityA;
	    [[maybe_unused]] unsigned int percentageOfPriorityB;
	    [[maybe_unused]] unsigned int percentageOfPriorityC;

        /*
        // shelf
        double shelfWidthInMeters;
        double shelfHeightInMeters;
        double shelfDepthInMeters;

        double distanceFromFloorToInputInMeters;
        double distanceFromFloorToOutputInMeters;

        // segment
        double distanceBetweenSegmentsInMeters;

        double segmentWidthInMeters;
        double segmentHeightInMeters;
        double segmentDepthInMeters;

        // container
        double containerWidthInMeters;
        double containerHeightInMeters;
        double containerDepthInMeters;
        */

        // constructors
    public:
        Inventory();

        Inventory(unsigned int percentageOfPriorityA, unsigned int percentageOfPriorityB, unsigned int percentageOfPriorityC, double conveyorBeltVelocity, unsigned int numberOfShelfPairs, unsigned long long int rowsPerShelf,
                  unsigned long long int segmentsPerRow,
                  double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds,
                  double horizontalMaxVelocityInMetersPerSecond, double horizontalAccelerationInMetersPerSquareSeconds,
                  double distanceBetweenShelfPairs, double shelfWidthInMeters, double shelfHeightInMeters,
                  double shelfDepthInMeters,
                  double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters,
                  double distanceBetweenSegmentsInMeters,
                  double segmentWidthInMeters, double segmentHeightInMeters, double segmentDepthInMeters,
                  double containerWidthInMeters, double containerHeightInMeters,
                  double containerDepthInMeters);

        //ToDo: Hier im Konstruktor ggf. die Größen löschen, die in shelfPairs dann schon beinhaltet sind!
                Inventory(unsigned int percentageOfPriorityA, unsigned int percentageOfPriorityB, unsigned int percentageOfPriorityC, double conveyorBeltVelocity, unsigned int numberOfShelfPairs, unsigned long long int rowsPerShelf,
                  unsigned long long int segmentsPerRow,
                  double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds,
                  double horizontalMaxVelocityInMetersPerSecond, double horizontalAccelerationInMetersPerSquareSeconds,
                  double distanceBetweenShelfPairs, double shelfWidthInMeters, double shelfHeightInMeters,
                  double shelfDepthInMeters,
                  double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters,
                  double distanceBetweenSegmentsInMeters,
                  double segmentWidthInMeters, double segmentHeightInMeters, double segmentDepthInMeters,
                  double containerWidthInMeters, double containerHeightInMeters,
                  double containerDepthInMeters, const std::vector<ShelfPair>& shelfPairs);



        // getters and setters
    private:
	    [[maybe_unused]] static unsigned int getShelfPairNumberByShelfNumber(unsigned int shelfNumber);

        void setSegmentsPriority(const SegmentDataMessage &segmentDataMessage, const Priority &priority);
        void setSegmentsPriority(unsigned int shelfNumber, unsigned long long int row, unsigned long long int column, const Priority& priority);


        // methods
    private:
        void saveAsJSONFile() const;

        void setSegmentPrioritiesBasedOnFastestToReachSegmentsAndPrioPercentages();
        void initiateContainerPriorities(unsigned int amountOfSegmentsReservedForPrio, const Priority &priority);

        //!!! Aktuellen Punkt der Bedienhilfen berücksichtigen (Allerdings muss für die Einlagerung die Bedienhilfe am Ausgangspunkt sein. Dafür müssten dann auch die Dauern für Rückfahrten der Bedienhilfen vom vorherigen (Ziel)Segment bestimmt werden. Die Strecke des vorher wartenden Containers wird also immer doppelt gefahren. Dazu kommt noch, dass ggf. auf gleichem Weg noch eine Auslieferung getätigt wird.) !!!
        //!!! Wo wird das aktuelle Segment gespeichert und wo ist dessen Abfrage relevant ??? !!!
        // The method gets the TimeSegmentMessage which contain the Segments coordinates and the time needed for the way (waiting time in queues excluded)

        std::optional<TimeSegmentMessage> getFastestToReachContainerWithoutSetPriority(); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference
        std::optional<TimeSegmentMessage> getFastestToReachSegmentForContainerInput(const Container& container);
        std::optional<TimeSegmentMessage> getFastestToReachContainerForItemInput(const Item& item); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference
        std::optional<TimeSegmentMessage> getFastestToReachContainerForItemOutput(const Item& item); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference

        std::optional<TimeSegmentMessage> getFastestToReachSegmentBasedOnUse(const SegmentUse& containerUse, const Item& item); // based on the vertical speed and vertical difference and horizontal speed and horizontal difference

        double calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(unsigned int shelfPairNumber);

    public:

        //ToDo: evtl. später wieder private machen
        ShelfPair& getShelfPairByShelfNumber(unsigned int shelfNumber);

        //!!! Für die folgenden beiden Methoden aktuelle Position der Bedienhilfen berücksichtigen, falls diese gerade frei sind. Dies aber eher mit Überladung der Methode machen, weil die generelle Regalzeilung ja schon vor dem Warten an der Warteschlange gemacht wird.
        //!!! -> Wenn die Berechnungen soweit implementiert sind, dass auch die Wartezeiten in der Schlange im Voraus bekannt sind, Methoden noch einmal ergänzen !!!
        [[maybe_unused]] std::optional<TimeSegmentMessage> reserveContainerOutputFromInventoryToGetItems(const Item& item);

		//ToDo
	    [[maybe_unused]] std::optional<TimeSegmentMessage> reserveContainerOutputFromInventoryToAddItems(const Item &item);

	    [[maybe_unused]] std::optional<TimeSegmentMessage> reserveContainerToAddToInventory(const Container& container);


        void reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment);
        void reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment);

		//ToDo
	    [[maybe_unused]] void addContainer(const SegmentDataMessage& goalSegment, const Container& newContainer);

	    [[maybe_unused]] Container takeContainer(const SegmentDataMessage& goalSegment);

        //ToDo: Diese Methode in AlternativMethoden für verschiedene SegmentUse's nutzen und evtl. später anstatt der anderen nutzen!
        //!!! Diese Methode in ConveyorBelt oder an I-Punkt aufrufen, damit dieser anhand der Warteschlangen nochmal berechnen kann, welches Segment insgesamt inklusive der Warteschlangen zum Zeitpunkt des Ankommens am optimalsten ist!!!
        std::vector<TimeSegmentMessage> getListOfFastestToReachSegmentsWayTimePerShelfOnlyShelfWay(const SegmentUse &containerUse, const Item &item);

	    [[maybe_unused]] void printShelfSegments();

        //ToDO: Folgende Listen-Methoden nutzen, falls Listen noch woanders weiter ausgewertet werden (z.B. am I-Punkt, um Warteschlangen zu berücksichtigen vor Reservierung)
        [[maybe_unused]] std::vector<TimeSegmentMessage> getListOfFastestToReachContainerWithoutSetPriorityPerShelfOnlyShelfWay();

	    [[maybe_unused]] std::vector<TimeSegmentMessage>
        getListOfFastestToReachSegmentForContainerInputPerShelfOnlyShelfWay(const Container &container);

	    [[maybe_unused]] std::vector<TimeSegmentMessage>
        getListOfFastestToReachContainerForItemInputPerShelfOnlyShelfWay(const Item &item);

	    [[maybe_unused]] std::vector<TimeSegmentMessage>
        getListOfFastestToReachContainerForItemOutputPerShelfOnlyShelfWay(const Item &item);

		// ToDo Erik Nissen
		std::string toString();
    };
}

#endif //NUPPROJECT_INVENTORY_H
