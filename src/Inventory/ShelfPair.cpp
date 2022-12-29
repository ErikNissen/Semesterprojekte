//
// Created by Kim Simoski on 19.11.2022.
//

#include "ShelfPair.h"


using namespace inventoryLib;
using namespace messagesLib;

// constructors


ShelfPair::ShelfPair(const unsigned int shelfPairNumber){
    PersistentFileManagement persistentFileManagement{"ShelfPair" + std::to_string(shelfPairNumber)};
    std::cout << "Load data from JSON Object" << std::endl;

    this->shelfPairNumber = persistentFileManagement.get("shelfPairNumber");

    this->shelfLeft = Shelf(shelfPairNumber * 2);
    this->shelfRight = Shelf(shelfPairNumber * 2 -1);

    //ToDo: Hardcoded numbers durch Parameter ersetzen!!!
    this->inputTransferPoint = TransferPoint(12.0f + (static_cast<float>(shelfPairNumber - 1) * 2.6f ));
    this->outputTransferPoint = TransferPoint(12.0f + (static_cast<float>(shelfPairNumber - 1) * 2.6f ));
}


//For Loading from JSON

ShelfPair::ShelfPair(const unsigned int shelfPairNumber, const unsigned long long int rowsPerShelf, const unsigned long long int segmentsPerRow,
                     const double verticalMaxVelocityInMetersPerSecond, const double verticalAccelerationInMetersPerSquareSeconds, const double horizontalMaxVelocityInMetersPerSecond, const double horizontalAccelerationInMetersPerSquareSeconds,
                     const double distanceBetweenShelvesOfPair, const double shelfWidthInMeters, const double shelfHeightInMeters, const double shelfDepthInMeters,
                     const double distanceFromFloorToInputInMeters, const double distanceFromFloorToOutputInMeters, const double distanceBetweenSegmentsInMeters,
                     const double segmentWidthInMeters, const double segmentHeightInMeters, const double segmentDepthInMeters, const double containerWidthInMeters, const double containerHeightInMeters,
                     const double containerDepthInMeters) :
//ToDo: Harcoded numbers durch Parameter ersetzen!!!
                     inputTransferPoint(TransferPoint(12.0f + (static_cast<float>(shelfPairNumber - 1) * 2.6f ))),
                     outputTransferPoint(TransferPoint(12.0f + (static_cast<float>(shelfPairNumber - 1) * 2.6f )))
{
    // log data
    this-> shelfPairNumber = shelfPairNumber;

    // measurement
    this-> distanceBetweenShelvesOfPair = distanceBetweenShelvesOfPair;

    // initiate amountOfShelves
    shelfLeft = Shelf{shelfPairNumber * 2 - 1, rowsPerShelf, segmentsPerRow, verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds,
    shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters, distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters,
    segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters, containerDepthInMeters};
    shelfRight = Shelf{shelfPairNumber * 2, rowsPerShelf, segmentsPerRow, verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds,
    shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters, distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters,
    segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters, containerDepthInMeters};
}

// for loading from json
ShelfPair::ShelfPair(const unsigned int shelfPairNumber, const unsigned long long int rowsPerShelf,
                     const unsigned long long int segmentsPerRow, const double verticalMaxVelocityInMetersPerSecond,
                     const double verticalAccelerationInMetersPerSquareSeconds, const double horizontalMaxVelocityInMetersPerSecond,
                     const double horizontalAccelerationInMetersPerSquareSeconds, const double distanceBetweenShelvesOfPair,
                     const double shelfWidthInMeters, double shelfHeightInMeters, const double shelfDepthInMeters,
                     const double distanceFromFloorToInputInMeters, const double distanceFromFloorToOutputInMeters,
                     const double distanceBetweenSegmentsInMeters, const double segmentWidthInMeters, double segmentHeightInMeters,
                     const double segmentDepthInMeters, const double containerWidthInMeters, double containerHeightInMeters,
                     const double containerDepthInMeters, const Shelf &shelfLeft, const Shelf &shelfRight):ShelfPair(shelfPairNumber, rowsPerShelf, segmentsPerRow,
verticalMaxVelocityInMetersPerSecond, verticalAccelerationInMetersPerSquareSeconds, horizontalMaxVelocityInMetersPerSecond, horizontalAccelerationInMetersPerSquareSeconds,
distanceBetweenShelvesOfPair, shelfWidthInMeters, shelfHeightInMeters, shelfDepthInMeters,
distanceFromFloorToInputInMeters, distanceFromFloorToOutputInMeters, distanceBetweenSegmentsInMeters,
segmentWidthInMeters, segmentHeightInMeters, segmentDepthInMeters, containerWidthInMeters, containerHeightInMeters,
containerDepthInMeters){

    this->shelfLeft = shelfLeft;
    this->shelfRight = shelfRight;

}

// copy constructor
ShelfPair::ShelfPair(const ShelfPair& other) {
	// Copy all of the attributes from the other object
	shelfLeft = other.shelfLeft;
	shelfRight = other.shelfRight;
	currentRow = other.currentRow;
	currentColumn = other.currentColumn;
	shelfPairNumber = other.shelfPairNumber;
	distanceBetweenShelvesOfPair = other.distanceBetweenShelvesOfPair;
	inputTransferPoint = other.inputTransferPoint;
	outputTransferPoint = other.outputTransferPoint;
}

ShelfPair& ShelfPair::operator=(const
                     inventoryLib::ShelfPair& other){
	// Check for self-assignment
	if (this == &other) {
		return *this;
	}
	// Copy all of the attributes from the other object
	shelfLeft = other.shelfLeft;
	shelfRight = other.shelfRight;
	currentRow = other.currentRow;
	currentColumn = other.currentColumn;
	shelfPairNumber = other.shelfPairNumber;
	distanceBetweenShelvesOfPair = other.distanceBetweenShelvesOfPair;
	inputTransferPoint = other.inputTransferPoint;
	outputTransferPoint = other.outputTransferPoint;
	return *this;
}

// getters and setters
unsigned int ShelfPair::getShelfPairNumber() const{
    return shelfPairNumber;
}

Shelf& ShelfPair::getShelfByShelfNumber(const unsigned int shelfNumber) {
    if(shelfLeft.getShelfNumber() == shelfNumber){
        return shelfLeft;
    }
    else if (shelfRight.getShelfNumber() == shelfNumber){
        return shelfRight;
    }
    else throw std::invalid_argument("Shelf number is not found in current shelf number. An argument has been set wrong.");
    //!!! https://cppbyexample.com/exceptions.html#:~:text=In%20C%2B%2B%20to%20raise%20or%20throw%20exceptions%20the,many%20basic%20exception%20types%20in%20the%20%3Cexception%3E%20header.
}

double ShelfPair::getDistanceBetweenShelvesOfPair() const {
    return distanceBetweenShelvesOfPair;
}

double ShelfPair::getShelfDepthInMeters(){
    return shelfLeft.getShelfDepthInMeters();
}

void ShelfPair::setSegmentsPriority(const unsigned int shelfNumber, const unsigned long long int row, const unsigned long long int column, const Priority& priority) {
    getShelfByShelfNumber(shelfNumber).setSegmentsPriority(row, column, priority);
}

// methods

void ShelfPair::saveAsJSONFile(){
    PersistentFileManagement persistentFileManagement{"ShelfPair" + std::to_string(shelfPairNumber)};
    std::cout << "Add data to JSON Object" << std::endl;

    persistentFileManagement.addOrIfExistentUpdate("shelfPairNumber", shelfPairNumber);

    //ToDo: Hier Aufruf der Speicher-Methode der einzelnen Shelves einfügen!
    shelfLeft.saveAsJSONFile();
    shelfRight.saveAsJSONFile();


    //ToDo: Hier beachten, dass keine Dopplungen passieren dürfen. ergo Nummern wie z.B. Regalnummer und Segmentnummer in den Namen integrieren und beim Auslesen rausfiltern (vllt. dafür cypher und decypher als Methoden auslagern)
    //ToDo: Alternativ zur Lösung oben jeweils eine einzelne Datei anlegen, die mit der Kodierung benannt ist!

}


//!!! Berücksichtigt noch nicht, dass Eingabe und Ausgabe unterschiedliche Höhen und damit unterschiedliche Strecken haben!!!
std::optional<TimeSegmentMessage> ShelfPair::getFastestToReachSegmentBasedOnUse(const SegmentUse& containerUse, const Item& item) {
    auto timeSegmentMessageOfFastestWayToSegmentShelfLeft{
            shelfLeft.getFastestToReachSegmentsBasedOnUse({1, 0, 0}, containerUse, item)};
    auto timeSegmentMessageOfFastestWayToSegmentShelfRight{
            shelfRight.getFastestToReachSegmentsBasedOnUse({1, 0, 0}, containerUse, item)};

    if(timeSegmentMessageOfFastestWayToSegmentShelfLeft && timeSegmentMessageOfFastestWayToSegmentShelfRight) {
        if (timeSegmentMessageOfFastestWayToSegmentShelfLeft->getNeededTimeWithoutWaitingInQueueInSeconds() <=
            timeSegmentMessageOfFastestWayToSegmentShelfRight->getNeededTimeWithoutWaitingInQueueInSeconds()) {
            return timeSegmentMessageOfFastestWayToSegmentShelfLeft;
        } else {
            return timeSegmentMessageOfFastestWayToSegmentShelfRight;
        }
    }
    else if(timeSegmentMessageOfFastestWayToSegmentShelfLeft){
        return (timeSegmentMessageOfFastestWayToSegmentShelfLeft);
    }
    else if(timeSegmentMessageOfFastestWayToSegmentShelfRight){
        return (timeSegmentMessageOfFastestWayToSegmentShelfRight);
    }
    else {
        return {};
    }
}


void ShelfPair::reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment) {
	std::lock_guard<std::mutex> lock(m);
    getShelfByShelfNumber(goalSegment.getShelfNumber()).reserveSegmentToAddContainer(goalSegment);
}

void ShelfPair::reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment) {
	std::lock_guard<std::mutex> lock(m);
    getShelfByShelfNumber(goalSegment.getShelfNumber()).reserveSegmentToGetContainer(goalSegment);
}

void ShelfPair::addContainer(const SegmentDataMessage &goalSegment, const Container &newContainer) {
	std::lock_guard<std::mutex> lock(m);
    getShelfByShelfNumber(goalSegment.getShelfNumber()).addContainer(goalSegment, newContainer);
}

//ToDo: get und take einheitlich benennen
Container ShelfPair::takeContainer(const SegmentDataMessage &goalSegment) {
	std::lock_guard<std::mutex> lock(m);
    return getShelfByShelfNumber(goalSegment.getShelfNumber()).takeContainer(goalSegment);
}

void ShelfPair::printAllShelfSegments() {
    shelfLeft.printShelfSegments();
    shelfRight.printShelfSegments();
}

TransferPoint &ShelfPair::getOutputTransferPoint() {
    return outputTransferPoint;
}

TransferPoint &ShelfPair::getInputTransferPoint() {
    return inputTransferPoint;
}


std::string ShelfPair::toString() {
	nlohmann::json data;
	data["shelfLeft"] = nlohmann::json::parse(this->shelfLeft.toString());
    data["shelfRight"] = nlohmann::json::parse(this->shelfRight.toString());
	data["currentRow"] = this->currentRow;
	data["currentColumn"] = this->currentColumn;
	data["shelfPairNumber"] = this->shelfPairNumber;
	data["distanceBetweenShelvesOfPair"] = this->distanceBetweenShelvesOfPair;
	return data.dump();
}

const Shelf &inventoryLib::ShelfPair::getShelfLeft() const {
	return shelfLeft;
}

const Shelf &inventoryLib::ShelfPair::getShelfRight() const {
	return shelfRight;
}

const std::mutex &inventoryLib::ShelfPair::getM() const {
	return m;
}

int inventoryLib::ShelfPair::getCurrentRow() const {
	return currentRow;
}

int inventoryLib::ShelfPair::getCurrentColumn() const {
	return currentColumn;
}














