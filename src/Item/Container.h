//
// Created by Kim Simoski on 27.11.2022.
//

#ifndef NUPPROJECT_CONTAINER_H
#define NUPPROJECT_CONTAINER_H

#include "Priority.h"
#include "Item.h"
#include "Timer.h"
#include "Container.h"
#include "../../_deps/json-src/single_include/nlohmann/json.hpp"
#include "../PersistentFileManagement/PersistentFileManagement.hpp"


// container for containing items with amounts and priorities in a shelf segment per container

using namespace itemLib;

class Container {
    // attributes
private:
    unsigned int containerId{};
    Item item{};
    unsigned int currentAmountOfItem{};

    Timer timer; // Tracks the time a Container is getting transported

    // measurements
    constexpr static float length = 0.4;
    constexpr static float width = 0.6;
    constexpr static float height = 0.4;


    // constructors
public:
    explicit Container(unsigned int id);
    explicit Container(const Item& item);
    explicit Container(const Item& item, unsigned int id, unsigned int currentAmount);

    [[nodiscard]] unsigned int getId() const;

    // getters and setters
public:

    [[nodiscard]] unsigned int getCurrentAmountOfItem() const;
    [[nodiscard]] unsigned int getAmountOfPlacesForItem() const;
    [[nodiscard]] Timer getTimer() const;
    static const float getLength();
    static const float getWidth();
    static const float getHeight();

    [[nodiscard]] const Item &getItem() const;
    [[nodiscard]] unsigned int getMaxAmountOfItem() const; // gets max amount of contained item
    [[nodiscard]] Priority getItemsPriority() const;
    void appendItemType(const Item& item);


    // methods
private:
    [[nodiscard]] bool containsAmountToGet(unsigned int amount) const;
    bool containsPlaceForAmountToAdd(unsigned int amount);

public:

    //ToDO: evtl. hinterher private machen, falls die Methode nur von eigenem Constructor und Destructor aufgerufen wird
    void saveAsJSONFile() const;

    bool containsItemsOfSameItemKind(const Item& item);
    [[nodiscard]] bool isEmpty() const;

    bool containsAtLeastOnePieceOfThisItemToGet(const Item& item);
    bool containsPlaceForAtLeastOnePieceOfThisItemToAdd(const Item& item);

    //bool containsAmountToGetOfThisItem(const TransferMessage& transferMessage);
    //bool containsPlaceForAmountToAddOfThisItem(const TransferMessage& transferMessage);

    void addAmount(unsigned int amount);
    void takeAmount(unsigned int amount);
    void print();
	// ToDo Erik Nissen
	std::string toString();
};

#endif //NUPPROJECT_CONTAINER_H
