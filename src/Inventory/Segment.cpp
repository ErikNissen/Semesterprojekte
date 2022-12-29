//
// Created by Kim Simoski on 27.11.2022.
//

#include "Segment.h"


using namespace inventoryLib;

// constructors
Segment::Segment() = default;

//ToDo: Die Contructors löschen, die nicht gebraucht werden
Segment::Segment(unsigned int shelfNumber, unsigned int rowNumber, unsigned int columnNumber):Segment(encodeSegmentId(shelfNumber, rowNumber, columnNumber)) {
saveAsJSONFile();
}

Segment::Segment(unsigned int id) {
    PersistentFileManagement persistentFileManagement{"Segment" + std::to_string(id)};

    std::cout << "Load data from JSON Object" << std::endl;


    this->segmentId = persistentFileManagement.get("segmentId");
    this->priority = persistentFileManagement.get("priority");

    this->container = Container{persistentFileManagement.get("containerId")};


    // flags
    this->segmentReservedForContainerInput = persistentFileManagement.get("segmentReservedForContainerInput");
    this->segmentReservedForContainerOutput = persistentFileManagement.get("segmentReservedForContainerOutput");



    //ToDo: Folgende Inhalte ergänzen!!!
    /*
    //ToDo: Hier beachten, dass keine Dopplungen passieren dürfen. ergo Nummern wie z.B. Regalnummer und Segmentnummer in den Namen integrieren und beim Auslesen rausfiltern (vllt. dafür cypher und decypher als Methoden auslagern)
    //ToDo: Alternativ zur Lösung oben jeweils eine einzelne Datei anlegen, die mit der Kodierung benannt ist!
    persistentFileManagement.addOrIfExistentUpdate("priority", priority);


    // save container id for beeing able to pair segment and container in loading from json file
    persistentFileManagement.addOrIfExistentUpdate("containerId", container.getId());


    //if(!container.isEmpty()){
    container.saveAsJSONFile();
    //}

     */
    //ToDo: Hier Aufruf der Speicher-Methode des einzelnen Container einfügen!
}



Segment::Segment(unsigned int id, const Priority& priority) {
    this->segmentId = id;
    this->priority = priority;
    //item = Item(priority);
	saveAsJSONFile();
}

// for loading from json file
Segment::Segment(const unsigned int id, const Priority& priority, const Container& container) {
    this->priority = priority;
}

Segment::Segment(unsigned int shelfNumber, unsigned int rowNumber, unsigned int columnNumber,
                 const Priority &priority): Segment(encodeSegmentId(shelfNumber, rowNumber, columnNumber), priority){
}



// getters and setters


//ToDO: Durch bessere Methode ersetzen z.B. mit Unique-Pointer, so dass wirklich kein Container vorhanden ist und nicht solange ein leerer, bis einer eingestellt wird
bool Segment::containsContainer() {
    return !container.isEmpty();
}

unsigned int Segment::getId() const {
    return segmentId;
}

//ToDO: Hier überdenken, ob die Rückgabe es eine Referenz oder ein Nullpointer werden soll. Letzteres würde den Konstruktor komplizierter machen
[[maybe_unused]] const Container &Segment::getContainer() const {
    return container;
}

//ToDO: Tendenziell nur privat nutzen oder hinterher löschen und stattdessen eine addContainer-Methode erstellen
void Segment::setContainer(const Container &newContainer) {
    container = newContainer;
    saveAsJSONFile();
}


[[maybe_unused]] Priority Segment::getPriority() const {
    return priority;
}

void Segment::setPriority(const Priority& newPriority) {
    if(hasNoPriorityLevel()) {
        priority = newPriority;
        saveAsJSONFile();
    }
    else{
        throw std::invalid_argument("A container with a valid priority level has been tried to reset mistakenly. Something went wrong.");
    }
}

bool Segment::isSegmentReservedForContainerOutput() const {
    return segmentReservedForContainerOutput;
}

bool Segment::isSegmentReservedForContainerInput() const {
    return segmentReservedForContainerInput;
}

void Segment::setSegmentReservedForContainerInput(bool newSegmentReservedForContainerInputState) {
    Segment::segmentReservedForContainerInput = newSegmentReservedForContainerInputState;
    saveAsJSONFile();
}

void Segment::setSegmentMarkedForContainerOutput(bool newSegmentMarkedForContainerOutputState) {
    Segment::segmentReservedForContainerOutput = newSegmentMarkedForContainerOutputState;
    saveAsJSONFile();
}


// methods

void Segment::saveAsJSONFile(){
    PersistentFileManagement persistentFileManagement{"Segment" + std::to_string(segmentId)};  //ToDo: Hier beachten, dass keine Dopplungen passieren dürfen. ergo Nummern wie z.B. Regalnummer und Segmentnummer in den Namen integrieren und beim Auslesen rausfiltern (vllt. dafür cypher und decypher als Methoden auslagern)

    std::cout << "Add data to JSON Object" << std::endl;

    persistentFileManagement.addOrIfExistentUpdate("segmentId", segmentId);


    //ToDo: Auskommentierte Attribute eingliedern, falls sie relevant sind und dafür in den Konstruktor aufnehmen (siehe Konstruktor von Shelf)!
    /*
    persistentFileManagement.addOrIfExistentUpdate("distanceBetweenSegmentsInMeters", distanceBetweenSegmentsInMeters);

    persistentFileManagement.addOrIfExistentUpdate("segmentWidthInMeters", segmentWidthInMeters);
    persistentFileManagement.addOrIfExistentUpdate("segmentHeightInMeters", segmentHeightInMeters);
    persistentFileManagement.addOrIfExistentUpdate("segmentDepthInMeters", segmentDepthInMeters);
    */

    // flags
    persistentFileManagement.addOrIfExistentUpdate("segmentReservedForContainerInput", segmentReservedForContainerInput);
    persistentFileManagement.addOrIfExistentUpdate("segmentReservedForContainerOutput", segmentReservedForContainerOutput);

    //ToDo: Hier beachten, dass keine Dopplungen passieren dürfen. ergo Nummern wie z.B. Regalnummer und Segmentnummer in den Namen integrieren und beim Auslesen rausfiltern (vllt. dafür cypher und decypher als Methoden auslagern)
    //ToDo: Alternativ zur Lösung oben jeweils eine einzelne Datei anlegen, die mit der Kodierung benannt ist!
    persistentFileManagement.addOrIfExistentUpdate("priority", priority);


    // save container id for beeing able to pair segment and container in loading from json file
    persistentFileManagement.addOrIfExistentUpdate("containerId", container.getId());


    //if(!container.isEmpty()){
        container.saveAsJSONFile();
    //}

    //ToDo: Hier Aufruf der Speicher-Methode des einzelnen Container einfügen!
}


unsigned int Segment::encodeSegmentId(const unsigned int shelfNumber, const unsigned int rowNumber, const unsigned int columnNumber){
    return shelfNumber * 10000 + rowNumber * 100 + columnNumber; //two digits possible for every part in case of bigger shelved or more than 99 shelves the code has to be corrected
}

unsigned int Segment::getShelfNumberFromSegmentId(){
    return segmentId / 10000;
}

unsigned int Segment::getRowNumberFromSegmentId(){
    return segmentId / 100;
}

unsigned int Segment::getColumnNumberFromSegmentId(){
    return segmentId % 100;
}

void Segment::deleteReservationFromSegmentToAddContainer() {
    setSegmentReservedForContainerInput(false);
    saveAsJSONFile();
}

void Segment::deleteReservationFromSegmentToGetContainer() {
    setSegmentMarkedForContainerOutput(false);
    saveAsJSONFile();
}

void Segment::reserveSegmentToAddContainer() {
    setSegmentReservedForContainerInput(true);
    saveAsJSONFile();
}

void Segment::reserveSegmentToGetContainer() {
    setSegmentMarkedForContainerOutput(true);
}

//ToDO: !!! hier noch Abfrage ergänzen, ob Prioritäten zusammenpassen !!!
//ToDO: Evtl. mit else if oder switch case verzweigen , falls throws beibehalten werden sollen.
void Segment::addContainer(const Container &newContainer) {
    if(!containsContainer()){
        if(isSegmentReservedForContainerInput()) {
            setContainer(newContainer);
            deleteReservationFromSegmentToAddContainer();
        }
        else{
            throw std::invalid_argument("A container has been tried to be added in a not reserved segment. Something went wrong.");
        }
    }
    else{
        throw std::invalid_argument("A container has been tried to be added in an occupied segment. Something went wrong.");
    }
}

//ToDo: Ausgabe und Leeren eleganter lösen (tendenziell mit unique-Pointer)!
Container Segment::takeContainer() {
    if(containsContainer()){
        if(isSegmentReservedForContainerOutput()) {
            auto returnContainer{container};
            container = Container(Item());
            deleteReservationFromSegmentToGetContainer();
            return returnContainer;
        }
        else{
            throw std::invalid_argument("A container has been tried to be taken from a not reserved segment. Something went wrong.");
        }
    }
    else{
        throw std::invalid_argument("A container has been tried to be taken from an unoccupied segment. Something went wrong.");
    }
}


bool Segment::hasNoPriorityLevel() {
    return (priority == Priority::N);
}

bool Segment::hasMatchingPriorityLevel(const Item& item) {
    return (priority == item.getPriority());
}

bool Segment::containsNoContainerAndHasMatchingPrio(const Item& item) {
    return !containsContainer() && hasMatchingPriorityLevel(item);
}

bool Segment::containsAtLeastOnePieceOfThisItemToGet(const Item& item) {
    return container.containsAtLeastOnePieceOfThisItemToGet(item);
}

bool Segment::containsPlaceForAtLeastOnePieceOfThisItemToAdd(const Item& item) {
    return container.containsPlaceForAtLeastOnePieceOfThisItemToAdd(item);
}

void Segment::print() {
    std::cout << "********************************"<< std::endl;
    container.print();
    printPriority();
    std::cout << "********************************"<< std::endl;

}

// https://stackoverflow.com/questions/66488850/how-to-print-the-enum-value-from-its-index
void Segment::printPriority() {
    switch (this->priority) {
        case Priority::A:
            std::cout << "Container-Priority: A" << std::endl;
            break;
        case Priority::B:
            std::cout << "Container-Priority: B" << std::endl;
            break;
        case Priority::C:
            std::cout << "Container-Priority: C" << std::endl;
            break;
        case Priority::N:
            std::cout << "Container-Priority not initialized" << std::endl;
            break;
        default:
            std::cout << "Container-Priority not available" << std::endl;
            //code to be executed, if the expression doesn't matched to  any constant_1(case 1)
            break;
    }
}

std::string Segment::toString() {
	nlohmann::json data;
	data["priority"] = this->priority;
	data["Container"] = nlohmann::json::parse(this->container.toString());
	data["segmentReservedForContainerInput"] =
			this->segmentReservedForContainerInput;
	data["segmentReservedForContainerOutput"] =
			this->segmentReservedForContainerOutput;
	return data.dump();
}


















/*
// getters and setters
unsigned int Segment::getMaxAmountOfItem() {
    return item.getMaxAmountPerContainer();
}

//!!! Vor dem Setzen der Prio im Container selbst immer testen, ob der Container leer und auch nicht für das  Hinzufügen reserviert ist.
void Segment::setPriority(const Priority& newPriority) {
    if(hasNoPriorityLevel()) {
        priority = newPriority;
    }
    else{
        throw std::invalid_argument("A container with a valid priority level has been tried to reset mistakenly. Something went wrong.");
    }
}

//!!! vllt. stattdessen einfach Item ersetzen !!!
void Segment::appendItemType(const TransferMessage& transferMessage) {
    item = transferMessage.getItem();
}

// methods
//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!

bool Segment::containsPlaceForAmountToAddOfThisItem(const TransferMessage& transferMessage) {
    return (hasMatchingPriorityLevel(transferMessage) && (containsItemsOfSameItemKind(transferMessage)||isEmpty()) && (containsPlaceForAmountToAdd(transferMessage.getAmountToTransfer())));
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool Segment::containsPlaceForAmountToAdd(const unsigned int amount) {
    //!!! folgend erst überprüfen, ob item schon vorhanden ist. Falls nicht, ist Platz da, weil der Container dann leer ist. !!! Analog bei allen Abfragen, die Daten von Item abfragen!!!
    return (currentAmountOfItem + reservedToAddAmount + amount <= item.getMaxAmountPerContainer());
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!

bool Segment::containsAmountToGetOfThisItem(const TransferMessage &transferMessage) {
    return (containsItemsOfSameItemKind(transferMessage) && containsAmountToGet(transferMessage.getAmountToTransfer()));
}

// checks for an amount to get in regards of already reserved amounts to get but not amounts to add. Cause latter ones are not yet added. But first ones are not allowed to be booked twice.
bool Segment::containsAmountToGet(const unsigned int amount) const {
    return ((this->currentAmountOfItem - this->reservedToGetAmount) >= amount);
}

//!!! Darauf achten, dass die Art von Item (entspricht Attribut item von Klasse Item) gelöscht wird, wenn die tatsächliche Menge irgendwo auf Null reduziert wird und aktuell eine Einlagerung reserviert ist.!!!
bool Segment::isEmpty() {
    return (item.getItemId() == 0);
}

bool Segment::hasNoPriorityLevel(){
    return (priority == Priority::N);
}

//!!![MUTEX-NUTZUNG]!!!
//!!! Checks müssen zusammen mit der direkten Reservierung passender Plätze im Regal in einem Mutex stattfinden, sonst kommt es bei Ein- und/oder Auslagerung zu Doppelbuchungen, zu falschen Sendungen und Überschreitungen maximaler Anzahlen!!!
bool Segment::containsItemsOfSameItemKind(const TransferMessage& transferMessage) {
    return (this->item.getItemId() == transferMessage.getItem().getItemId());
}

bool Segment::hasMatchingPriorityLevel(const TransferMessage& transferMessage) {
    return (priority == transferMessage.getItem().getPriority());
}

//!!! Prüfen, ob der Konstruktoraufruf von Item so klappt. Ansonsten ggf. Werte manuell auf Null setzen !!!
void Segment::ifEmptyAndNotReservedToAddDeleteItemType() {
    if((currentAmountOfItem == 0) && (reservedToAddAmount == 0)){
        item = Item{};
        //!!! vermutlich gleichbedeutend mit: item.getItemId() == 0
    }
}


void Segment::reserveAmountToAddForItem(const TransferMessage &transferMessage) {
    if(containsPlaceForAmountToAddOfThisItem(transferMessage)){
        if(isEmpty()){ // if currently the container is empty there is no reference values for max limits therefore it needs to be appended first
            appendItemType(transferMessage);
        }
        reserveAmountToAdd(transferMessage.getAmountToTransfer());
    }

}

void Segment::reserveAmountToAdd(const unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)){
        reservedToAddAmount += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container is exceeded. Something went wrong.");
    }
}

void Segment::reserveAmountToTakeForItem(const TransferMessage& transferMessage) {
    if(containsAmountToGetOfThisItem(transferMessage)){
        reserveAmountToTake(transferMessage.getAmountToTransfer());
    }
}

void Segment::reserveAmountToTake(const unsigned int amount) {
    if(containsAmountToGet(amount)){
        reservedToAddAmount += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this reservation to add. Something went wrong.");
    }
}

//!!! Zugriffe auf Mengen mit MUTEX regeln, da es sonst zu Unstimmigkeiten kommt. Es darf immer nur abgezogen oder hinzugefügt, zum Holen oder Hinzufügen reserviert werden!!!
//!!! Methode mit TransferMessage als Parameter erstellen!!!

void Segment::addAmount(const TransferMessage& transferMessage) { // amounts get only added if this amount is reserved to be added. The itemType gets appended by the reservation.
    if(containsItemsOfSameItemKind(transferMessage)){
        addAmount(transferMessage.getAmountToTransfer());
    }
}


void Segment::addAmount(unsigned int amount) {
    if(containsPlaceForAmountToAdd(amount)) {
        reservedToAddAmount -= amount;
        currentAmountOfItem += amount;
    }
    else {
        throw std::invalid_argument("The maximum amount of the used container would be exceeded by this addition. Something went wrong.");
    }
}

void Segment::takeAmount(const TransferMessage& transferMessage) {
    if(containsItemsOfSameItemKind(transferMessage)){
        takeAmount(transferMessage.getAmountToTransfer());
    }
}

void Segment::takeAmount(unsigned int amount) {
    if(containsAmountToGet(amount)) {
        reservedToGetAmount -= amount;
        currentAmountOfItem -= amount;
        ifEmptyAndNotReservedToAddDeleteItemType();
    }
    else {
        throw std::invalid_argument("The amount exceeds the available amount of the used container. Something went wrong.");
    }
}
 */













