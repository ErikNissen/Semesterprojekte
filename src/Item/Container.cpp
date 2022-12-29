//
// Created by Kim Simoski on 07.12.2022.
//

#include "Container.h"
#include "../PersistentFileManagement/PersistentFileManagement.hpp"


// constructors

// for loading from json file
Container::Container(const unsigned int id) {

    //ToDo: Load from JSON-File!
    PersistentFileManagement persistentFileManagement{"Container" + std::to_string(containerId)};

    std::cout << "Load data from JSON Object" << std::endl;

    // identification
    this->containerId = persistentFileManagement.get("containerId");
    this->item = Item(persistentFileManagement.get("itemId"));
    this->currentAmountOfItem = persistentFileManagement.get("currentAmountOfItem");

    /*
    this->timer = Timer(persistentFileManagement.get("timerId"));

    // measurements
    this->length = persistentFileManagement.get("length");
    this->width = Item(persistentFileManagement.get("width"));
    this->height = persistentFileManagement.get("height");
    */



}

Container::Container(const Item& item) {
    this->item = item;
    timer = Timer();
}

Container::Container(const Item& item, const unsigned int id, const unsigned int currentAmount) {
    this->containerId = id;
    this->item = item;
    this->currentAmountOfItem = currentAmount;
    this->timer = Timer();
	saveAsJSONFile();
}


// getters and setters
unsigned int Container::getId() const {
    return containerId;
}

Timer Container::getTimer() const {
    return timer;
}

const float Container::getLength() {
    return length;
}

const float Container::getWidth() {
    return width;
}

const float Container::getHeight() {
    return height;
}

const Item &Container::getItem() const {
    return item;
}

unsigned int Container::getMaxAmountOfItem() const {
    return item.getMaxAmountPerContainer();
}

unsigned int Container::getCurrentAmountOfItem() const {
    return currentAmountOfItem;
}

unsigned int Container::getAmountOfPlacesForItem() const {
    return item.getMaxAmountPerContainer() - currentAmountOfItem;
}

Priority Container::getItemsPriority() const {
    return item.getPriority();
}

void Container::appendItemType(const Item& externalItem) {
    this->item = externalItem;
}

// methods

void Container::saveAsJSONFile() const{
    PersistentFileManagement persistentFileManagement{"Container" + std::to_string(this->containerId)};

    std::cout << "Add data to JSON Object" << std::endl;

    persistentFileManagement.addOrIfExistentUpdate("containerId",
												   this->containerId);

    persistentFileManagement.addOrIfExistentUpdate("currentAmountOfItem", this->currentAmountOfItem);

    // measurements
    persistentFileManagement.addOrIfExistentUpdate("length", this->length);
    persistentFileManagement.addOrIfExistentUpdate("width", this->width);
    persistentFileManagement.addOrIfExistentUpdate("height", this->height);

    // save item id for beeing able to pair container and item in loading from json file
    persistentFileManagement.addOrIfExistentUpdate("itemId", this->item.getItemId());
	persistentFileManagement.save();
    //??ToDo: Hier Aufruf der Speicher-Methode des Countdowns einfügen??
    //ToDo: Hier Aufruf der Speicher-Methode des Items einfügen!
    // ToDo: this doesnt work!!
//    item.saveAsJSONFile();

}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
// checks for an amount to get in regards of already reserved amounts to get but not amounts to add. Cause latter ones are not yet added. But first ones are not allowed to be booked twice.
bool Container::containsAmountToGet(const unsigned int amount) const {
    return this->currentAmountOfItem >= amount;
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool Container::containsPlaceForAmountToAdd(const unsigned int amount) {
    //!!! folgend erst überprüfen, ob item schon vorhanden ist. Falls nicht, ist Platz da, weil der Container dann leer ist. !!! Analog bei allen Abfragen, die Daten von Item abfragen!!!
    return currentAmountOfItem + amount <= item.getMaxAmountPerContainer();
}

bool Container::containsItemsOfSameItemKind(const Item& externalItem) {
    return this->item.getItemId() == externalItem.getItemId();
}

void Container::addAmount(unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)) {
        currentAmountOfItem += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

void Container::takeAmount(unsigned int amount) {
    if(containsAmountToGet(amount)) {
        currentAmountOfItem -= amount;
    }
    else {
        throw std::invalid_argument("The minimum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

bool Container::containsAtLeastOnePieceOfThisItemToGet(const Item &externalItem) {
    return containsItemsOfSameItemKind(externalItem) && containsAmountToGet(1);
}

bool Container::containsPlaceForAtLeastOnePieceOfThisItemToAdd(const Item &externalItem) {
    return (containsItemsOfSameItemKind(externalItem) && containsPlaceForAmountToAdd(1)) || isEmpty();
}

bool Container::isEmpty() const {
    return (currentAmountOfItem == 0);
}

void Container::print() {
    item.print();
    std::cout << "current amount of item: " << currentAmountOfItem << std::endl;
}

std::string Container::toString() {
	nlohmann::json data;
	data["Item"] = nlohmann::json::parse(this->item.toString());
	data["currentAmountOfItem"] = this->currentAmountOfItem;
	data["length"] = this->length;
	data["width"] = this->width;
	data["height"] = this->height;
	data["id"] = this->containerId;
	data["timer"] = this->timer.getTimeInSeconds();
	return data.dump();
}