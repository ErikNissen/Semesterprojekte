//
// Created by Kim Simoski on 19.11.2022.
//

#include "Shelf.h"



using namespace inventoryLib;
// constructors
//!!! Konstruktor für Initialisierung aus Persistenten Daten mit komplettem Datensatz erstellen und von Inventar durch entsprechende Konstruktoren durchreichen, die aus einer JSON lesen !!!

//ToDo: Constructor löschen, falls nicht verwendet!
/*
 Shelf::Shelf(){
//ToDo: Load from JSON-File!
    PersistentFileManagement persistentFileManagement{"Inventory"};
    std::cout << "Load data from JSON Object" << std::endl;
}*/

// for loading from json file
Shelf::Shelf(unsigned int shelfNumber){
    PersistentFileManagement persistentFileManagement{"Shelf" + std::to_string(shelfNumber)};

    std::cout << "Load data from JSON Object" << std::endl;

    // identification
    this->shelfNumber = persistentFileManagement.get("shelfNumber");
    this->rowsPerShelf = persistentFileManagement.get("rowsPerShelf");
    this->segmentsPerRow = persistentFileManagement.get("segmentsPerRow");

    // measurements
    this->verticalMaxVelocityInMetersPerSecond = persistentFileManagement.get("verticalMaxVelocityInMetersPerSecond");
    this->verticalAccelerationInMetersPerSquareSeconds = persistentFileManagement.get("verticalAccelerationInMetersPerSquareSeconds");

    this->horizontalMaxVelocityInMetersPerSecond = persistentFileManagement.get("horizontalMaxVelocityInMetersPerSecond");
    this->horizontalAccelerationInMetersPerSquareSeconds = persistentFileManagement.get("horizontalAccelerationInMetersPerSquareSeconds");

    // shelf

    this->shelfWidthInMeters = persistentFileManagement.get("shelfWidthInMeters");
    this->shelfHeightInMeters = persistentFileManagement.get("shelfHeightInMeters");
    this->shelfDepthInMeters = persistentFileManagement.get("shelfDepthInMeters");

    this->distanceFromFloorToInputInMeters = persistentFileManagement.get("distanceFromFloorToInputInMeters");
    this->distanceFromFloorToOutputInMeters = persistentFileManagement.get("distanceFromFloorToOutputInMeters");

    this->segmentsPerRow = persistentFileManagement.get("segmentsPerRow");

    //ToDo: Hier einzelne Segmente laden
    matrix = {rowsPerShelf, std::vector<std::shared_ptr<Segment>>{segmentsPerRow}}; // sets a matrix with a set size and Containers with default priority N which means no valid priority level

    for (unsigned int row = 0; row < rowsPerShelf; row++) {
        for (unsigned int column{0}; column < segmentsPerRow; column++) {
            matrix.at(row).at(column) = std::make_shared<Segment>(Segment{shelfNumber, row, column});
        }
    }
}




Shelf::Shelf(const unsigned int shelfNumber, const unsigned long long int rowsPerShelf, const unsigned long long int segmentsPerRow,
             const double verticalMaxVelocityInMetersPerSecond, const double verticalAccelerationInMetersPerSquareSeconds, const double horizontalMaxVelocityInMetersPerSecond, const double horizontalAccelerationInMetersPerSquareSeconds,
             const double shelfWidthInMeters, const double shelfHeightInMeters, const double shelfDepthInMeters,
             const double distanceFromFloorToInputInMeters, const double distanceFromFloorToOutputInMeters, const double distanceBetweenSegmentsInMeters,
             const double segmentWidthInMeters, const double segmentHeightInMeters, const double segmentDepthInMeters, const double containerWidthInMeters, const double containerHeightInMeters,
             const double containerDepthInMeters){

    // initiate shelf
    //!!! Bezeichner überdenken !!!

    //!!! Muss eigenen Vector erstellen. Die Üblichen können nur Standard-Datentypen beinhalten!!! Alternativ einen Vector of Pointer (unique oder shared. Eher unique)
    // https://www.geeksforgeeks.org/program-to-create-custom-vector-class-in-c/
    // https://www.programiz.com/cpp-programming/vectors
    matrix = {rowsPerShelf, std::vector<std::shared_ptr<Segment>>{segmentsPerRow}}; // sets a matrix with a set size and Containers with default priority N which means no valid priority level

    for (unsigned int row = 0; row < rowsPerShelf; row++) {
        for (unsigned int column{0}; column < segmentsPerRow; column++) {
            matrix.at(row).at(column) = std::make_shared<Segment>(Segment{shelfNumber, row, column, Priority::N});
        }
    }

    // identification
    this->shelfNumber = shelfNumber;

    // counts
    this->rowsPerShelf = rowsPerShelf;
    this->segmentsPerRow = segmentsPerRow;

    // measurements
    this->verticalMaxVelocityInMetersPerSecond = verticalMaxVelocityInMetersPerSecond;
    this->verticalAccelerationInMetersPerSquareSeconds = verticalAccelerationInMetersPerSquareSeconds;

    this->horizontalMaxVelocityInMetersPerSecond = horizontalMaxVelocityInMetersPerSecond ;
    this->horizontalAccelerationInMetersPerSquareSeconds = horizontalAccelerationInMetersPerSquareSeconds;

    //!!! evtl. alle Objekte mit Höhe, Breite, Tiefe mit gemeinsamer Vererbung umsetzen !!!

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

     /*
    // container
    this->containerWidthInMeters = containerWidthInMeters;
    this->containerHeightInMeters = containerHeightInMeters;
    this->containerDepthInMeters = containerDepthInMeters;
     */
}


// for loading from json-file
//ToDo: Attribute als Parameter löschen, die in Matrix schon vorhanden sind und in shelf selbst nicht als Attribute gespeichert werden
Shelf::Shelf(const unsigned int shelfNumber, const unsigned long long int rowsPerShelf, const unsigned long long int segmentsPerRow,
                  const double verticalMaxVelocityInMetersPerSecond, const double verticalAccelerationInMetersPerSquareSeconds, const double horizontalMaxVelocityInMetersPerSecond, const double horizontalAccelerationInMetersPerSquareSeconds,
                  const double shelfWidthInMeters, const double shelfHeightInMeters, const double shelfDepthInMeters,
                  const double distanceFromFloorToInputInMeters, const double distanceFromFloorToOutputInMeters, const double distanceBetweenSegmentsInMeters,
                  const double segmentWidthInMeters, const double segmentHeightInMeters, const double segmentDepthInMeters, const double containerWidthInMeters, const double containerHeightInMeters,
                  const double containerDepthInMeters, const std::vector<std::vector<std::shared_ptr<Segment>>>& matrix):Shelf(shelfNumber, rowsPerShelf, segmentsPerRow,
                                                                                                                               verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds,
                                                                                                                               shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters,
                                                                                                                               distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters,
                                                                                                                               segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters,
                                                                                                                               containerDepthInMeters){
    this->matrix = matrix;
}

// getters and setters
double Shelf::getShelfDepthInMeters() const{
    return shelfDepthInMeters;
}

unsigned int Shelf::getShelfNumber() const {
    return shelfNumber;
}

void Shelf::setSegmentsPriority(const unsigned long long int row, const unsigned long long int column, const Priority& priority) {
    matrix.at(row).at(column)->setPriority(priority); // Zuweisung wird irgendwie nicht umgesetzt, obwohl debugging bis hier kommt!
}


// methods

void Shelf::saveAsJSONFile() const{
    PersistentFileManagement persistentFileManagement{"Shelf" + std::to_string(shelfNumber)};  //ToDo: Hier beachten, dass keine Dopplungen passieren dürfen. ergo Nummern wie z.B. Regalnummer und Segmentnummer in den Namen integrieren und beim Auslesen rausfiltern (vllt. dafür cypher und decypher als Methoden auslagern)

    std::cout << "Add data to JSON Object" << std::endl;

    // identification
    persistentFileManagement.addOrIfExistentUpdate("shelfNumber", shelfNumber);
    persistentFileManagement.addOrIfExistentUpdate("rowsPerShelf", rowsPerShelf);
    persistentFileManagement.addOrIfExistentUpdate("segmentsPerRow", segmentsPerRow);

    // measurements
    persistentFileManagement.addOrIfExistentUpdate("verticalMaxVelocityInMetersPerSecond", verticalMaxVelocityInMetersPerSecond);
    persistentFileManagement.addOrIfExistentUpdate("verticalAccelerationInMetersPerSquareSeconds", verticalAccelerationInMetersPerSquareSeconds);

    persistentFileManagement.addOrIfExistentUpdate("horizontalMaxVelocityInMetersPerSecond", horizontalMaxVelocityInMetersPerSecond);
    persistentFileManagement.addOrIfExistentUpdate("horizontalAccelerationInMetersPerSquareSeconds", horizontalAccelerationInMetersPerSquareSeconds);

    // shelf
    persistentFileManagement.addOrIfExistentUpdate("shelfWidthInMeters", shelfWidthInMeters);
    persistentFileManagement.addOrIfExistentUpdate("shelfHeightInMeters", shelfHeightInMeters);
    persistentFileManagement.addOrIfExistentUpdate("shelfDepthInMeters", shelfDepthInMeters);

    persistentFileManagement.addOrIfExistentUpdate("distanceFromFloorToInputInMeters", distanceFromFloorToInputInMeters);
    persistentFileManagement.addOrIfExistentUpdate("distanceFromFloorToOutputInMeters", distanceFromFloorToOutputInMeters);

    persistentFileManagement.addOrIfExistentUpdate("segmentsPerRow", segmentsPerRow);

    //ToDo: Hier save-Methode von Segment aufrufen (dabei über Kodierung Einzigartigkeit der Value-Keys garantieren oder alternativ jeweils eine eigene Klasse erstellen mit unikatem verschlüsseltem Namen, der über Methode erstellt und entschlüsselt werden kann)
    //ToDo: Evtl. stattdessen Speichern einzelner Segmentente nur in dessen Constructor und Destructor aufrufen
    for(unsigned long long i{0} ; i < rowsPerShelf; i++) {
        for (unsigned long long j{0}; j < segmentsPerRow; j++) {
            matrix.at(i).at(j)->saveAsJSONFile();
        }
    }


    /*
    // container
    persistentFileManagement.addOrIfExistentUpdate("containerWidthInMeters", containerWidthInMeters);
    persistentFileManagement.addOrIfExistentUpdate("containerHeightInMeters", containerHeightInMeters);
    persistentFileManagement.addOrIfExistentUpdate("containerDepthInMeters", containerDepthInMeters);
    */

}

void Shelf::reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment) {
    matrix.at(goalSegment.getRow()).at(goalSegment.getColumn())->reserveSegmentToAddContainer();
}

void Shelf::reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment) {
    matrix.at(goalSegment.getRow()).at(goalSegment.getColumn())->reserveSegmentToGetContainer();
}

void Shelf::addContainer(const SegmentDataMessage& goalSegment, const Container& newContainer) {
    matrix.at(goalSegment.getRow()).at(goalSegment.getColumn())->addContainer(newContainer);
}

Container Shelf::takeContainer(const SegmentDataMessage& goalSegment) {
    return matrix.at(goalSegment.getRow()).at(goalSegment.getColumn())->takeContainer();
}


//!!! Berücksichtigt noch nicht, dass Eingabe und Ausgabe unterschiedliche Höhen und damit unterschiedliche Strecken haben!!!
std::optional<TimeSegmentMessage> Shelf::getFastestToReachSegmentsBasedOnUse(const SegmentDataMessage &currentSegment,
                                                                             const SegmentUse &containerUse, const Item &item) {
    std::vector<SegmentDataMessage> listOfMatchingContainersForUse{getListOfSegmentsBasedOnUse(containerUse, item)};

    if(!listOfMatchingContainersForUse.empty()){
        std::vector<TimeSegmentMessage> listOfTimeSegmentMessages{};

        // add the needed way times to the segments and save new message in new list
        for(SegmentDataMessage goalsSegmentDataMessage:listOfMatchingContainersForUse){
            double timeNeededForWayInSeconds{calculateWayTimeToSegmentInSeconds(currentSegment, goalsSegmentDataMessage)};
            listOfTimeSegmentMessages.emplace_back(timeNeededForWayInSeconds, 0 , goalsSegmentDataMessage);
        }

        TimeSegmentMessage segmentWithFastestWay;
        segmentWithFastestWay = *std::min_element(listOfTimeSegmentMessages.begin(), listOfTimeSegmentMessages.end(),
                                                  compareTwoElements);
        return segmentWithFastestWay;
    }
    else{//!!! https://en.cppreference.com/w/cpp/utility/optional !!! // if no value is returned, optional contains an empty value which tranlates to a false bool value
        return {};
    }
}

/*
//!!! Performances überprüfen und nur diese Methode oder die darüber nutzen!
TimeSegmentMessage Shelf::getFastestToReachEmptyContainerAlt(const SegmentDataMessage& currentSegment) {
    std::vector<SegmentDataMessage> listOfFreeContainers{getListOfFreeContainers()};

    double shortestTimeInSeconds {-1}; //!!! Workaround, brächte aber Fehler, wenn kein freies Segment gefunden wird!!!

    TimeSegmentMessage* segmentWithFastestWay; //!!! Pointer-Handhabe überarbeiten zu neueren Cpp-Standards !!!

    for(SegmentDataMessage segmentDataMessage:listOfFreeContainers){
        double timeNeededForWayInSeconds{calculateWayTimeToSegmentInSeconds(currentSegment, segmentDataMessage)};

        if(shortestTimeInSeconds < 0 || timeNeededForWayInSeconds < shortestTimeInSeconds){
            shortestTimeInSeconds = timeNeededForWayInSeconds;
            *segmentWithFastestWay  = {shortestTimeInSeconds, segmentDataMessage};
        }
    }
    return *segmentWithFastestWay; //!!! Fehler werfen oder null_ptr zurückgeben und an aufrufenden Stellen auf null_ptr abfragen, falls kein Element gefunden wird und die Liste ergo leer ist
}
 */


//!!! Hier TransferMessage als weiteres Argument einfügen und in entsprechenden Methoden von Segment, um direkt zu gucken, welcher Container aktuell zum Item und der Anzahl passt !!!
std::vector<SegmentDataMessage> Shelf::getListOfSegmentsBasedOnUse(const SegmentUse& containerUse, const Item& item) { //!!! Hier noch später Reservierung für Warenprioritäten berücksichtigen!!!
    std::vector<SegmentDataMessage> listOfEmptyMatchingSegmentsOrContainers;
    for(unsigned long long i{0} ; i < rowsPerShelf; i++)
    {
        for(unsigned long long j{0}; j < segmentsPerRow; j++)
        {

            switch(containerUse)
            {
                case SegmentUse::InitPrio:
                    if(matrix.at(i).at(j)->hasNoPriorityLevel()) {
                        listOfEmptyMatchingSegmentsOrContainers.emplace_back(shelfNumber, i, j);
                    }
                    break;

                case SegmentUse::AddItemToContainer:
                    if(matrix.at(i).at(j)->containsPlaceForAtLeastOnePieceOfThisItemToAdd(item)) {
                        listOfEmptyMatchingSegmentsOrContainers.emplace_back(shelfNumber, i, j);
                    }
                    break;

                case SegmentUse::GetItemFromContainer:
                    if(matrix.at(i).at(j)->containsAtLeastOnePieceOfThisItemToGet(item)) {
                        listOfEmptyMatchingSegmentsOrContainers.emplace_back(shelfNumber, i, j);
                    }
                    break;

                case SegmentUse::AddContainerToSegment:
                    if(matrix.at(i).at(j)->containsNoContainerAndHasMatchingPrio(item)) {
                        listOfEmptyMatchingSegmentsOrContainers.emplace_back(shelfNumber, i, j);
                    }
                    break;

                default:
                    break;
            }
        }
    }
    return listOfEmptyMatchingSegmentsOrContainers;
}

double Shelf::calculateWayTimeToSegmentInSeconds(const SegmentDataMessage& currentSegment, const SegmentDataMessage& goalSegment) {

    int horizontalArrayIndicesDifference{calculateHorizontalArrayIndicesDifference(currentSegment, goalSegment)};
    int verticalArrayIndicesDifference{calculateVerticalArrayIndicesDifference(currentSegment, goalSegment)};

    double horizontalWayInMeters{calculateHorizontalWayFromArrayIndicesDifference(horizontalArrayIndicesDifference)};
    double verticalWayInMeters{calculateVerticalWayFromArrayIndicesDifference(verticalArrayIndicesDifference)};

    double timeNeededForHorizontalWayInSeconds{calculateTimeNeededForHorizontalWayInSeconds(horizontalWayInMeters)};
    double timeNeededForVerticalWayInSeconds{calculateTimeNeededForVerticalWayInSeconds(verticalWayInMeters)};

    return std::max(timeNeededForHorizontalWayInSeconds, timeNeededForVerticalWayInSeconds); // the whole waytime is determined by the slower direction if both happen to run parallel
}

//!!! Methoden für Auslagerung und Einlagerung überlagern, um zusätzliche Strecke zu berücksichtigen!!!
double Shelf::calculateTimeNeededForHorizontalWayInSeconds(const double wayInMeters) {
    return calculateTimeInSecondsFromWayInMeters(wayInMeters, horizontalMaxVelocityInMetersPerSecond,
                                                 horizontalAccelerationInMetersPerSquareSeconds);
}

double Shelf::calculateTimeNeededForVerticalWayInSeconds(const double wayInMeters) {
    return calculateTimeInSecondsFromWayInMeters(wayInMeters, verticalMaxVelocityInMetersPerSecond,
                                                 verticalAccelerationInMetersPerSquareSeconds);
}

//!!! Methoden zum Umrechnen mit physikalischen Größen evtl. in eine extra Klasse als Service auslagern !!!
// https://www.johannes-strommer.com/formeln/weg-geschwindigkeit-beschleunigung-zeit/
double Shelf::calculateTimeInSecondsFromWayInMeters(const double wayInMeters, const double maxVelocityInMetersPerSecond,
                                                    const double accelerationInMetersPerSquareSeconds) {
    double wayNeededForReachingMaxVelocityInMeters = maxVelocityInMetersPerSecond*maxVelocityInMetersPerSecond/(2 * accelerationInMetersPerSquareSeconds);

    // https://www.johannes-strommer.com/formeln/weg-geschwindigkeit-beschleunigung-zeit/
    // the reference is two times the way needed for accelerating up to the max velocity because the same way is needed for stopping the vehicle
    if(wayInMeters > 2 * wayNeededForReachingMaxVelocityInMeters){
        return maxVelocityInMetersPerSecond / accelerationInMetersPerSquareSeconds + wayInMeters / maxVelocityInMetersPerSecond;
    }
    else if(wayInMeters == 2 * wayNeededForReachingMaxVelocityInMeters){
        return 2 * maxVelocityInMetersPerSecond / accelerationInMetersPerSquareSeconds;
    }
    else{ //case: wayInMeters < wayNeededForReachingMaxVelocityInMeters
        return 2 * std::sqrt(wayInMeters/accelerationInMetersPerSquareSeconds);
    }
}

double Shelf::calculateHorizontalWayFromArrayIndicesDifference(const int arrayIndicesDifference) const {
    return arrayIndicesDifference * (distanceBetweenSegmentsInMeters + segmentWidthInMeters);
}

double Shelf::calculateVerticalWayFromArrayIndicesDifference(const int arrayIndicesDifference) const {
    return arrayIndicesDifference * (segmentHeightInMeters); //!!! Hier muss ggf. noch die Bodenhöhe ergänzt werden !!!
}

//!!! Folgende beiden Methode in einer Aufrufen, die Start-und Ziel-Koordinaten kennt und jeweils die Differenz in y und in x-Richtung als Argument übergibt. Dabei ggf. Extraweg bis Ausgabestelle beachten und darauf, dass nicht zwingend immer vom Startpunkt gefahren wird!!!
//!!! Für Nutzung der Methode für Initialisierung ist es aber vom Startpunkt des Regals richtig !!!
int Shelf::calculateHorizontalArrayIndicesDifference(const SegmentDataMessage& currentSegmentOfThisShelfPair, const SegmentDataMessage& goalSegment){
    return std::abs(static_cast<int>(currentSegmentOfThisShelfPair.getColumn()) - static_cast<int>(goalSegment.getColumn()));
}

//!!! Später currentSegementOfThisShelf implementieren und berücksichtigen, um nicht jedes Mal vom Ausgangspunkt zu rechnen. Für Nutzung der Methode für Initialisierung ist es aber vom Startpunkt des Regals richtig!!!
int Shelf::calculateVerticalArrayIndicesDifference(const SegmentDataMessage& currentSegmentOfThisShelfPair, const SegmentDataMessage& goalSegment){
    return std::abs(static_cast<int>(currentSegmentOfThisShelfPair.getRow()) - static_cast<int>(goalSegment.getRow()));
}

bool Shelf::compareTwoElements(const TimeSegmentMessage& leftElement, const TimeSegmentMessage& rightElement){
    return (leftElement.getNeededTimeWithoutWaitingInQueueInSeconds() < rightElement.getNeededTimeWithoutWaitingInQueueInSeconds());
}

void Shelf::printShelfSegments() {
    std::cout << "------------------------------------------------------------" << std::endl;
    std::cout << "--[Shelf number: " << shelfNumber << "]--------------------------------------" << std::endl;
    std::cout << "------------------------------------------------------------" << std::endl;

    for(unsigned long long i{0}; i < rowsPerShelf; ++i)
    {
        for(unsigned int j {0}; j < segmentsPerRow; ++j)
        {
            std::cout << "Row: " << i << "; " << "Segment: " << j << ":" << std::endl;
            matrix[i][j]->print();
        }
    }
}

std::string Shelf::toString() {
	using ull = unsigned long long;
	nlohmann::json data, mtx;
	std::stringstream ss;
	for(ull i = 0; i < this->rowsPerShelf; ++i){
		for (unsigned int j = 0; j < this->segmentsPerRow; ++j){
			mtx[i][j] = nlohmann::json::parse(this->matrix[i][j]->toString());
		}
	}
	data["Matrix"] = mtx;
	data["rowsPerShelf"] = this->rowsPerShelf;
	data["segmentsPerRow"] = this->segmentsPerRow;
	data["verticalMaxVelocityInMetersPerSecond"] =
			this->verticalMaxVelocityInMetersPerSecond;
	data["verticalAccelerationInMetersPerSquareSeconds"] =
			this->verticalAccelerationInMetersPerSquareSeconds;
	data["horizontalMaxVelocityInMetersPerSecond"] =
			this->horizontalMaxVelocityInMetersPerSecond;
	data["horizontalAccelerationInMetersPerSquareSeconds"] =
			this->horizontalAccelerationInMetersPerSquareSeconds;
	data["shelfWidthInMeters"] = this->shelfWidthInMeters;
	data["shelfHeightInMeters"] = this->shelfHeightInMeters;
	data["shelfDepthInMeters"] = this->shelfDepthInMeters;
	data["distanceFromFloorToInputInMeters"] =
			this->distanceFromFloorToInputInMeters;
	data["distanceFromFloorToOutputInMeters"] =
			this->distanceFromFloorToOutputInMeters;
	data["distanceBetweenSegmentsInMeters"] =
			this->distanceBetweenSegmentsInMeters;
	data["segmentWidthInMeters"] = this->segmentWidthInMeters;
	data["segmentHeightInMeters"] = this->segmentHeightInMeters;
	data["segmentDepthInMeters"] = this->segmentDepthInMeters;
	/*
    data["containerWidthInMeters"] = this->containerWidthInMeters;
	data["containerHeightInMeters"] = this->containerHeightInMeters;
	data["containerDepthInMeters"] = this->containerDepthInMeters;
	 */

	return data.dump();
}



















