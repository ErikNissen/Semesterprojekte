//
// Created by Kim Simoski on 19.11.2022.
//


#include "Inventory.h"


using namespace inventoryLib;
using namespace messagesLib;

// global Var
int counter = 0;
//std::mutex m, mm, mmm;

// constructors

// for loading from json file
Inventory::Inventory() {


    PersistentFileManagement persistentFileManagement{"Inventory"};
    std::cout << "Load data from JSON Object" << std::endl;

    // counts
    this->amountOfShelves = persistentFileManagement.get("amountOfShelves");
    this->rowsPerShelf = persistentFileManagement.get("rowsPerShelf");
    this->segmentsPerRow = persistentFileManagement.get("segmentsPerRow");

    // priority percentages
    this->percentageOfPriorityA = persistentFileManagement.get("percentageOfPriorityA");
    this->percentageOfPriorityB = persistentFileManagement.get("percentageOfPriorityB");
    this->percentageOfPriorityC = persistentFileManagement.get("percentageOfPriorityC");


    // inventory
    this->distanceBetweenShelves = persistentFileManagement.get("distanceBetweenShelves");
    this->conveyorBeltVelocity = persistentFileManagement.get("conveyorBeltVelocity");

    // reinitialize shelf pairs from loaded json file
    std::vector<ShelfPair> loadedShelfPairs{};



    for(unsigned int i{1}; i<= amountOfShelves/2; i++){
        loadedShelfPairs.emplace_back(ShelfPair(i));
    }

    setShelfPairs(loadedShelfPairs);

}

//!!! Anstatt alle Daten einzeln zu übergeben, vllt. Container-Object und Regal-Object usw. mit fertigen Maßen übergeben und anhanddessen Daten beziehen !!!
Inventory::Inventory(unsigned int percentageOfPriorityA, unsigned int percentageOfPriorityB, unsigned int percentageOfPriorityC, const double conveyorBeltVelocity, const unsigned int numberOfShelfPairs, const unsigned long long int rowsPerShelf, const unsigned long long int segmentsPerRow, const double verticalMaxVelocityInMetersPerSecond, const double verticalAccelerationInMetersPerSquareSeconds, const double horizontalMaxVelocityInMetersPerSecond, const double horizontalAccelerationInMetersPerSquareSeconds, const double distanceBetweenShelfPairs, const double shelfWidthInMeters, const double shelfHeightInMeters, const double shelfDepthInMeters, const double distanceFromFloorToInputInMeters, const double distanceFromFloorToOutputInMeters, const double distanceBetweenSegmentsInMeters, const double segmentWidthInMeters, const double segmentHeightInMeters, const double segmentDepthInMeters, const double containerWidthInMeters, const double containerHeightInMeters, const double containerDepthInMeters){
    // initiate shelfs
    for(unsigned int shelfPairNumber{1}; shelfPairNumber <= numberOfShelfPairs; shelfPairNumber++){
        //shelfPairs.push_back({rowsPerShelf, segmentsPerRow});
        shelfPairs.emplace_back(shelfPairNumber, rowsPerShelf, segmentsPerRow, verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds,
                                distanceBetweenShelfPairs, shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters,
                                distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters,
                                segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters,
                                containerDepthInMeters);
    }

    //!!! Daten, die zum Regal gehören entweder nur hier deklarieren, als Parametern bei Methoden durchschleifen bis zu Shelf, oder nur in Shelf speichern und Attribute, da in einer Ebene höher sind, eine Ebene darüber, dafür Daten in den Konstruktoren durchschleifen und für die Log-Datei über Methode von jeder Klasse eigene Daten holen lassen, die dann über abgestützte Methoden durch Aufrufer weiter ergänzt werden. Letzteres ist eher objektorientiert.
    // save log data

    // counts
    this->amountOfShelves = numberOfShelfPairs * 2; //!!! Attribut kann wegrationalisiert werden, da die Anzahl aus den Regalen selbst beim Holen gezogen werden kann!!!


    this->rowsPerShelf = rowsPerShelf;
    this->segmentsPerRow = segmentsPerRow;

    this->percentageOfPriorityA = percentageOfPriorityA;
    this->percentageOfPriorityB = percentageOfPriorityB;
    this->percentageOfPriorityC = percentageOfPriorityC;

    /*
    // measurements
    this->verticalMaxVelocityInMetersPerSecond = verticalMaxVelocityInMetersPerSecond;
    this->verticalAccelerationInMetersPerSquareSeconds = verticalAccelerationInMetersPerSquareSeconds;

    this->horizontalMaxVelocityInMetersPerSecond = horizontalMaxVelocityInMetersPerSecond ;
    this->horizontalAccelerationInMetersPerSquareSeconds = horizontalAccelerationInMetersPerSquareSeconds;

    //!!! evtl. alle Objekte mit Höhe, Breite, Tiefe mit gemeinsamer Vererbung umsetzen !!!
    */
    // inventory
    this->distanceBetweenShelves = distanceBetweenShelfPairs;
    this->conveyorBeltVelocity = conveyorBeltVelocity;

    /*
    // shelf
    this->shelfWidthInMeters = shelfWidthInMeters;
    this->shelfHeightInMeters = shelfHeightInMeters;
    this->shelfDepthInMeters = shelfDepthInMeters;

    this->distanceFromFloorToInputInMeters = distanceFromFloorToInputInMeters;
    this->distanceFromFloorToOutputInMeters = distanceFromFloorToOutputInMeters;

    // segment
    this->distanceBetweenSegmentsInMeters = distanceBetweenSegmentsInMeters;

    this->segmentWidthInMeters = segmentWidthInMeters;
    this->segmentHeightInMeters = segmentHeightInMeters;
    this->segmentDepthInMeters = segmentDepthInMeters;

    // container
    this->containerWidthInMeters = containerWidthInMeters;
    this->containerHeightInMeters = containerHeightInMeters;
    this->containerDepthInMeters = containerDepthInMeters;
     */

    setSegmentPrioritiesBasedOnFastestToReachSegmentsAndPrioPercentages();

    // ToDo: Vorher abfragen, ob es Daten bereits persistent gibt. Falls es sie gibt, daten von JSON laden, falls nicht, von Construktor beziehen und persistente Daten neu anlegen
    saveAsJSONFile();
}

// for loading from JSON-File
Inventory::Inventory(unsigned int percentageOfPriorityA, unsigned int percentageOfPriorityB,
                     unsigned int percentageOfPriorityC, double conveyorBeltVelocity, unsigned int numberOfShelfPairs,
                     unsigned long long int rowsPerShelf, unsigned long long int segmentsPerRow,
                     double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds,
                     double horizontalMaxVelocityInMetersPerSecond,
                     double horizontalAccelerationInMetersPerSquareSeconds, double distanceBetweenShelfPairs,
                     double shelfWidthInMeters, double shelfHeightInMeters, double shelfDepthInMeters,
                     double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters,
                     double distanceBetweenSegmentsInMeters, double segmentWidthInMeters, double segmentHeightInMeters,
                     double segmentDepthInMeters, double containerWidthInMeters, double containerHeightInMeters,
                     double containerDepthInMeters, const std::vector<ShelfPair>& shelfPairs):

    Inventory(percentageOfPriorityA, percentageOfPriorityB, percentageOfPriorityC, conveyorBeltVelocity, numberOfShelfPairs, rowsPerShelf, segmentsPerRow, verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds, distanceBetweenShelfPairs, shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters, distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters, segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters, containerDepthInMeters){
        this->shelfPairs = shelfPairs;
    }


// getters and setters
ShelfPair& Inventory::getShelfPairByShelfNumber(const unsigned int shelfNumber) {
    return shelfPairs.at(getShelfPairNumberByShelfNumber(shelfNumber)-1); // the list of shelf pairs starts at 0 but with the member shelfPairNumber = 1
}

[[maybe_unused]] unsigned int Inventory::getShelfPairNumberByShelfNumber(const unsigned int shelfNumber) {
    return std::ceil(static_cast<double>(shelfNumber)/2);
}


// methods

void Inventory::saveAsJSONFile() const{
    PersistentFileManagement pfm{ "Inventory"};
    std::cout << "Add data to JSON Object" << std::endl;

    // counts
    pfm.addOrIfExistentUpdate( "amountOfShelves", amountOfShelves);
    pfm.addOrIfExistentUpdate( "rowsPerShelf", rowsPerShelf);
    pfm.addOrIfExistentUpdate( "segmentsPerRow", segmentsPerRow);

    // priority percentages
    pfm.addOrIfExistentUpdate( "percentageOfPriorityA", percentageOfPriorityA);
    pfm.addOrIfExistentUpdate( "percentageOfPriorityB", percentageOfPriorityB);
    pfm.addOrIfExistentUpdate( "percentageOfPriorityC", percentageOfPriorityC);

    // inventory
    pfm.addOrIfExistentUpdate( "distanceBetweenShelves", distanceBetweenShelves);
    pfm.addOrIfExistentUpdate( "conveyorBeltVelocity", conveyorBeltVelocity);

    //ToDo: Hier Aufruf der Speicher-Methode der einzelnen ShelfPairs einfügen! / Alternativ immer jeweils intern im Konstruktor aufrufen. Dann müssten aber z.B. bei Container, die nicht immer im gleichen Segment sind, die Zuordnung zum Segment kodiert werden als Name, Attribut oder Liste
    for( auto shelfPair: shelfPairs){
        shelfPair.saveAsJSONFile();
    }
}





void Inventory::setSegmentPrioritiesBasedOnFastestToReachSegmentsAndPrioPercentages(){
    unsigned int totalAmountOfShelfSegments{amountOfShelves * static_cast<unsigned int>(rowsPerShelf) * static_cast<unsigned int> (segmentsPerRow)};
    //!!! Prio-Handhabe ggf. komplett auf Maps oder Liste umstellen und durch Liste iterieren,anstatt alle Werte einzeln zu beziehen!!!
    unsigned int amountOfSegmentsReservedForPrioA{percentageOfPriorityA * totalAmountOfShelfSegments / 100};
    unsigned int amountOfSegmentsReservedForPrioB{percentageOfPriorityB * totalAmountOfShelfSegments / 100};
    unsigned int amountOfSegmentsReservedForPrioC{percentageOfPriorityC * totalAmountOfShelfSegments / 100};

    /*
    unsigned int amountOfSegmentsReservedForPrioA{static_cast<unsigned int> (std::round(static_cast<double>(percentageOfPriorityA)/100 * totalAmountOfShelfSegments))};
    unsigned int amountOfSegmentsReservedForPrioB{static_cast<unsigned int> (std::round(static_cast<double>(percentageOfPriorityB)/100 * totalAmountOfShelfSegments))};
    unsigned int amountOfSegmentsReservedForPrioC{static_cast<unsigned int> (std::round(static_cast<double>(percentageOfPriorityC)/100 * totalAmountOfShelfSegments))};
    */

    //!!! Stattdessen Liste aller Bestandteile machen und hier mithilfe von Mapping über alle iterieren. Alternativ Deklarationsschleife als Methode auslagern und da Parameter reinstecken !!!
    // priorityA
    initiateContainerPriorities(amountOfSegmentsReservedForPrioA, Priority::A);

    // priorityB
    initiateContainerPriorities(amountOfSegmentsReservedForPrioB, Priority::B);

    // priorityC
    initiateContainerPriorities(amountOfSegmentsReservedForPrioC, Priority::C);

    //!!! FOR DEBUGGING
    std::cout << "Prios have been reserved for Containers in Segments." << std::endl;
}

//ToDo:Bezeichner überarbeiten und vor allem kürzen!
//ToDo: Folgende Listen-Methoden nutzen, falls Listen noch woanders weiter ausgewertet werden (z.B. am I-Punkt, um Warteschlangen zu berücksichtigen vor Reservierung)
//ToDo: Hier noch Rückwege ergänzen
[[maybe_unused]] std::vector<TimeSegmentMessage>
Inventory::getListOfFastestToReachContainerWithoutSetPriorityPerShelfOnlyShelfWay() {
    return getListOfFastestToReachSegmentsWayTimePerShelfOnlyShelfWay(SegmentUse::InitPrio, {});
}

[[maybe_unused]] std::vector<TimeSegmentMessage>
Inventory::getListOfFastestToReachSegmentForContainerInputPerShelfOnlyShelfWay(const Container& container) {
    return getListOfFastestToReachSegmentsWayTimePerShelfOnlyShelfWay(SegmentUse::AddContainerToSegment, container.getItem());
}


[[maybe_unused]] std::vector<TimeSegmentMessage>
Inventory::getListOfFastestToReachContainerForItemInputPerShelfOnlyShelfWay(const Item& item) {
    return getListOfFastestToReachSegmentsWayTimePerShelfOnlyShelfWay(SegmentUse::AddItemToContainer, item);
}

[[maybe_unused]] std::vector<TimeSegmentMessage> Inventory::getListOfFastestToReachContainerForItemOutputPerShelfOnlyShelfWay(const Item& item) {
    return getListOfFastestToReachSegmentsWayTimePerShelfOnlyShelfWay(SegmentUse::GetItemFromContainer, item);
}

std::vector<TimeSegmentMessage> Inventory::getListOfFastestToReachSegmentsWayTimePerShelfOnlyShelfWay(const SegmentUse& containerUse, const Item& item) {
    std::vector<TimeSegmentMessage> fastestToReachSegmentPerShelfPairOfAllShelfPairs{};
    for(ShelfPair shelfPair:shelfPairs){
        auto fastestToReachSegmentBasedOnUse{shelfPair.getFastestToReachSegmentBasedOnUse(containerUse, item)};
        if(fastestToReachSegmentBasedOnUse) {
            fastestToReachSegmentPerShelfPairOfAllShelfPairs.emplace_back(fastestToReachSegmentBasedOnUse.value());
        }
    }
    return fastestToReachSegmentPerShelfPairOfAllShelfPairs;
}

// ToDo: generate mainThread who open the Function below (std::jthread
//  threadMain(mainThreadX);) this func is is mutex

//!!! Diese Methode berechnet den Weg vom ersten Einlagerungseinstellplatz über das Laufband bis zum jeweiligen Einlagerungseinstellplatz mit ein, aber beachtet dessen Warteschlange mit den jeweiligen Wartezeiten noch nicht. !!!
//!!! Analoge Methode ergänzen, die separat die Zeiten für die Einlagerung kennt. Dann könnten die für das Log gleich mitgegeben und für den Countdown an den Wartestationen. Ggf. aber auch woanders implementieren. Aber jeweils nur für das Zielsegment des insgesamt kürzesten Weges!!!
//!!! Beachtet noch nicht die jeweils aktuelle Position oder die Interaktion mit Ausgabeprozessen !!!
std::optional<TimeSegmentMessage> Inventory::getFastestToReachSegmentBasedOnUse(const SegmentUse& containerUse, const Item& item) {
//// ToDo: here we open 10 threads to look wich is the fastest way (std::jthread tm1(searchFunc, ShelfNummer);
//// ToDo: after the searchFunc we give the fastest way of the Pair to a new Function who have mutex and use the globale variable to save the Value
    double shortestTimeInSeconds {-1};

    std::optional<TimeSegmentMessage> segmentWithFastestWay;

    for(ShelfPair& shelfPair: shelfPairs){
        //!!! Bezeichner kürzen!!!
        auto fastestToReachSegmentOfShelfPair{shelfPair.getFastestToReachSegmentBasedOnUse(containerUse, item)};

        if(fastestToReachSegmentOfShelfPair) {
            double neededTimeForReachingSegmentFromInputWaitingPlaceInSeconds{
                    fastestToReachSegmentOfShelfPair->getNeededTimeWithoutWaitingInQueueInSeconds()};
            double neededTimeForReachingPairFromFirstPairsViaConveyorBeltInSeconds{
                    calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(shelfPair.getShelfPairNumber())};
            double neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds{
                    neededTimeForReachingSegmentFromInputWaitingPlaceInSeconds +
                    neededTimeForReachingPairFromFirstPairsViaConveyorBeltInSeconds};

            if (shortestTimeInSeconds < 0 ||
                neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds < shortestTimeInSeconds) {
                shortestTimeInSeconds = neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds;
                segmentWithFastestWay = std::optional<TimeSegmentMessage>{{
                                                                                  neededTimeForReachingSegmentFromInputWaitingPlaceInSeconds,
                                                                                  neededTimeForReachingSegmentFromFirstPairsInputWaitingPlaceInSeconds,
                                                                                  fastestToReachSegmentOfShelfPair->getSegmentDataMessage()}};
            }
        }
    }
    if (segmentWithFastestWay){
        return segmentWithFastestWay;
    }
    else{
        throw std::out_of_range("Cannot find empty space. All shelves are full.");
    }
}


//!!! Zugriffsweg auf distanceBetweenShelvesOfPair und shelfDepthInMeters überdenken!!!
//!!! Methodenbezeichner kürzen !!!
//!!! Für Debugging public gemacht. Hinterher wieder private machen !!!
double Inventory::calculateTimeForReachingPairFromFirstPairViaConveyorBeltInSeconds(const int unsigned shelfPairNumber) {
    return static_cast<double>(shelfPairNumber - 1) * (shelfPairs.at(0).getDistanceBetweenShelvesOfPair() + 2 * shelfPairs[0].getShelfDepthInMeters())/conveyorBeltVelocity;
}

//!!! Methoden zum Setzen der Prioritäten private machen!!!
void Inventory::setSegmentsPriority(const SegmentDataMessage& segmentDataMessage,
                                    const itemLib::Priority &priority) {
    //!!! FOR DEBUGGING !!!
    auto num{segmentDataMessage.getShelfNumber()};
    auto row{segmentDataMessage.getRow()};
    auto seg{segmentDataMessage.getColumn()};
    setSegmentsPriority(num, row, seg, priority);

    //setSegmentsPriority(segmentDataMessage.getShelfNumber(), segmentDataMessage.getRow(), segmentDataMessage.getColumn(), priority);
}

void Inventory::setSegmentsPriority(const unsigned int shelfNumber, const unsigned long long int row, const unsigned long long int column,
                                    const Priority& priority) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(shelfNumber)};
    shelfPair.setSegmentsPriority(shelfNumber, row, column, priority);
}


void Inventory::initiateContainerPriorities(const unsigned int amountOfSegmentsReservedForPrio, const Priority& priority) {
    for (unsigned int i{0}; i < amountOfSegmentsReservedForPrio; i++) {
        auto fastestToReachEmptyContainer{getFastestToReachContainerWithoutSetPriority()->getSegmentDataMessage()};
        setSegmentsPriority(fastestToReachEmptyContainer, priority);
    }
}


std::optional<TimeSegmentMessage>
Inventory::getFastestToReachContainerWithoutSetPriority() {
    return Inventory::getFastestToReachSegmentBasedOnUse(SegmentUse::InitPrio, {});
}

std::optional<TimeSegmentMessage>
Inventory::getFastestToReachSegmentForContainerInput(const Container& container) {
    return Inventory::getFastestToReachSegmentBasedOnUse(SegmentUse::AddContainerToSegment, container.getItem());
}


std::optional<TimeSegmentMessage>
Inventory::getFastestToReachContainerForItemInput(const Item& item) {
    return getFastestToReachSegmentBasedOnUse(SegmentUse::AddItemToContainer, item);
}

std::optional<TimeSegmentMessage>
Inventory::getFastestToReachContainerForItemOutput(const Item& item) {
    return getFastestToReachSegmentBasedOnUse(SegmentUse::GetItemFromContainer, item);
}


//ToDO: Segmente müssen reserviert werden für: Ausgabe des Containers zum Befüllen, Ausgabe des Containers zum Herausnehmen, Einfügen des Containers in ein Segment

[[maybe_unused]] std::optional<TimeSegmentMessage> Inventory::reserveContainerToAddToInventory(const Container& container) {
    auto fastestToReachContainer{getFastestToReachSegmentForContainerInput(container)};
    if(fastestToReachContainer) {
        reserveSegmentToAddContainer(fastestToReachContainer->getSegmentDataMessage());
    }
    return fastestToReachContainer;
}

//ToDO: Im besten Fall diese Methode erst beim Punkt aufrufen, der das Laufband mit ansteuert und dafür noch eine Ebene aufrufen, die das schnellste zu erreichende Segment unter Berücksichtung der Warteschlangen berechnet
//!!! Die Methoden zum Reservieren evtl. so anpassen, dass noch vor dem Aufruf die aktuellen Wartezeiten in den Schlangen berücksichtigt werden können, was so direkt nicht der Fall ist. Aber zwischen Abfrage der Liste und Reservierung darf keine Zeit liegen. Dann müsste ggf. das Laufband beides gleichzeitig in einer Methode machen, die ein Mutex ist !!!
[[maybe_unused]] std::optional<TimeSegmentMessage> Inventory::reserveContainerOutputFromInventoryToGetItems(const Item& item) {
    auto fastestToReachContainer{getFastestToReachContainerForItemOutput(item)};
    if(fastestToReachContainer) {
        reserveSegmentToGetContainer(fastestToReachContainer->getSegmentDataMessage());
    }
    return fastestToReachContainer;
}

//ToDO: Im besten Fall diese Methode erst beim Punkt aufrufen, der das Laufband mit ansteuert und dafür noch eine Ebene aufrufen, die das schnellste zu erreichende Segment unter Berücksichtung der Warteschlangen berechnet
//!!! Die Methoden zum Reservieren evtl. so anpassen, dass noch vor dem Aufruf die aktuellen Wartezeiten in den Schlangen berücksichtigt werden können, was so direkt nicht der Fall ist. Aber zwischen Abfrage der Liste und Reservierung darf keine Zeit liegen. Dann müsste ggf. das Laufband beides gleichzeitig in einer Methode machen, die ein Mutex ist !!!
[[maybe_unused]] std::optional<TimeSegmentMessage> Inventory::reserveContainerOutputFromInventoryToAddItems(const Item& item) {
    auto fastestToReachContainer{getFastestToReachContainerForItemInput(item)};
    if(fastestToReachContainer) {
        reserveSegmentToGetContainer(fastestToReachContainer->getSegmentDataMessage());
    }
    return fastestToReachContainer;
}

//!!! the selection process of the fastest to reach matching shelf segment and the reservation (this method) have to be called simultaneously
void Inventory::reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(goalSegment.getShelfNumber())};
    shelfPair.reserveSegmentToAddContainer(goalSegment);
}

//!!! the selection process in of the fastest to reach matching shelf segment and the reservation (this method) have to be called simultaneously
void Inventory::reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(goalSegment.getShelfNumber())};
    shelfPair.reserveSegmentToGetContainer(goalSegment);
}

//!!! for getting called after waiting at a shelfPairs input waiting point
[[maybe_unused]] void Inventory::addContainer(const SegmentDataMessage &goalSegment, const Container &newContainer) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(goalSegment.getShelfNumber())};
    shelfPair.addContainer(goalSegment, newContainer);
}

//!!! for getting called after waiting at a shelfPairs input waiting point
[[maybe_unused]] Container Inventory::takeContainer(const SegmentDataMessage &goalSegment) {
    ShelfPair& shelfPair{getShelfPairByShelfNumber(goalSegment.getShelfNumber())};
    return shelfPair.takeContainer(goalSegment);
}


[[maybe_unused]] void Inventory::printShelfSegments() {
    std::cout << "!! All shelf segments: " << std::endl;
    for(auto shelfPair:shelfPairs){
        shelfPair.printAllShelfSegments();
    }
}

std::string Inventory::toString() {
	nlohmann::json data, sP;
	std::stringstream ss;
	for(auto i = 0; i < this->shelfPairs.size(); ++i){
		sP[i] = nlohmann::json::parse(this->shelfPairs[i].toString());
	}
	data["shelfPairs"] = sP;
	data["amountOfShelves"] = this->amountOfShelves;
	data["rowsPerShelf"] = this->rowsPerShelf;
	data["segmentsPerRow"] = this->segmentsPerRow;
	data["conveyorBeltVelocity"] = this->conveyorBeltVelocity;
	data["distanceBetweenShelves"] = this->distanceBetweenShelves;
	data["percentageOfPriorityA"] = this->percentageOfPriorityA;
	data["percentageOfPriorityB"] = this->percentageOfPriorityB;
	data["percentageOfPriorityC"] = this->percentageOfPriorityC;

	return data.dump();
}

void Inventory::setShelfPairs( const std::vector<ShelfPair> &shelfPairs ) {
	Inventory::shelfPairs = shelfPairs;
}






















