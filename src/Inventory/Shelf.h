//
// Created by Kim Simoski on 19.11.2022.
//

#include <iostream>
#include <vector>
#include <memory>
#include <cmath>
#include <algorithm>
#include <iomanip>
#include <vector>
#include <optional>
#include "../Messages/SegmentDataMessage.h"
#include "../Messages/TimeSegmentMessage.h"
#include "Segment.h"
#include "SegmentUse.h"
#include "../PersistentFileManagement/PersistentFileManagement.hpp"
#include "../../_deps/json-src/single_include/nlohmann/json.hpp"

#ifndef NUPPROJECT_SHELF_H
#define NUPPROJECT_SHELF_H

using namespace messagesLib;

namespace inventoryLib {
    //!!! Im Fall von Pointer-Gebrauch diesen zu modernerem Pointer umändern!!!
    /*
    * The class Shelf is contained by the class ShelfPair. It represents one shelf of a pair.
    * The class provides methods to store or restore items. For reservations there are also methods to reserve for adding to and to reserve for getting from the inventory.
    * The class uses methods to calculate the fastest possible ways to shelf segments for storation processes.
    * The storage positions are based on three different levels of priority of items.
    */
    class Shelf {

        // attributes
    private:


// https://riptutorial.com/cplusplus/example/17463/matrices-using-vectors
        // https://iamsorush.com/posts/shared-pointer-cpp/
        //!!! Evtl. von shared_pointer zu unique_pointer wechseln und dafür Move-Konstruktor für Container-Klasse schreiben
        std::vector<std::vector<std::shared_ptr<Segment>>> matrix;

        //!!! Log-Data bzw. Daten zum Berechnen entweder nur hier initialisieren, oder in extra Klasse, die zum Verrechnen genutzt wird oder in Inventar oder zusammengesetzt jeweils ergänzend in umklammernder Klasse, mit jeweils objektorientierter Zuteilung !!!
        // log_data

        unsigned int shelfNumber; // beginning with 1

        // counts
        unsigned long long rowsPerShelf;
        unsigned long long segmentsPerRow;


        // measurements

        //!!! Wenn man Velocity und Acceleration als Regaleigentschaft deklariert, macht man die Bedienhilfen abstrahiert zu einer Regaleigenschaft. Da müsste man dann darauf achten, dass in einem Regalpaar immer nur ein Regal gleichzeitig diese Eigenschaft nutzen kann und der aktuelle Index für alle einzelnen "Methoden", welche die Bedienhilfen widerspiegeln identisch sein muss.
        //!!! Für letzteres könnte aber der aktuelle Index aus Shelfpair als Argument in die Methoden übergeben werden, wenn diese Klasse sie aufruft. Das wäre aber eher prozedural als objektorientiert. !!!
        // transport vehicle
        double verticalMaxVelocityInMetersPerSecond;
        double verticalAccelerationInMetersPerSquareSeconds;

        double horizontalMaxVelocityInMetersPerSecond;
        double horizontalAccelerationInMetersPerSquareSeconds;

        //!!! evtl. alle Objekte mit Höhe, Breite, Tiefe mit gemeinsamer Vererbung umsetzen !!!

        // inventory

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
        /*
              // container
              double containerWidthInMeters;
              double containerHeightInMeters;
              double containerDepthInMeters;
              */


        // constructors
    public:
        Shelf() = default;
        Shelf(unsigned int shelfNumber);
        //!!! Konstruktor ergänzen, der anhand einer JSON Rand-Werte und Inhalte der Tabellen setzt!!!
        //Shelf() = default; //!!! Maybe delete later if possible. Needed for Constructor initialisation in ShelfPair !!!

        //ToDo: Constructors löschen, die nicht benötigt werden
        //Shelf(unsigned long long int rows, unsigned long long int columns);
        Shelf(unsigned int shelfNumber, unsigned long long int rowsPerShelf, unsigned long long int segmentsPerRow,
              double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds,
              double horizontalMaxVelocityInMetersPerSecond, double horizontalAccelerationInMetersPerSquareSeconds,
              double shelfWidthInMeters, double shelfHeightInMeters, double shelfDepthInMeters,
              double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters,
              double distanceBetweenSegmentsInMeters,
              double segmentWidthInMeters, double segmentHeightInMeters, double segmentDepthInMeters,
              double containerWidthInMeters, double containerHeightInMeters,
              double containerDepthInMeters);

        Shelf(unsigned int shelfNumber, unsigned long long int rowsPerShelf, unsigned long long int segmentsPerRow,
                          double verticalMaxVelocityInMetersPerSecond, double verticalAccelerationInMetersPerSquareSeconds, double horizontalMaxVelocityInMetersPerSecond, double horizontalAccelerationInMetersPerSquareSeconds,
                          double shelfWidthInMeters, double shelfHeightInMeters, double shelfDepthInMeters,
                          double distanceFromFloorToInputInMeters, double distanceFromFloorToOutputInMeters, double distanceBetweenSegmentsInMeters,
                          double segmentWidthInMeters, double segmentHeightInMeters, double segmentDepthInMeters, double containerWidthInMeters, double containerHeightInMeters,
                          double containerDepthInMeters, const std::vector<std::vector<std::shared_ptr<Segment>>>& matrix);

        // getters and setters
    public:
        [[nodiscard]] double getShelfDepthInMeters() const;
        [[nodiscard]] unsigned int getShelfNumber() const;
        void setSegmentsPriority(unsigned long long int row, unsigned long long int column, const Priority& priority);

        // methods
    private:



        // based on the vertical speed and vertical difference and horizontal speed and horizontal difference
        double calculateWayTimeToSegmentInSeconds(const SegmentDataMessage& currentSegment, const SegmentDataMessage& goalSegment);

        //double Shelf::calculateTimeInSecondsFromWayInMeters(const double wayInMetersHorizonzal, double wayInMetersVertical);
        //!!! Bezug der Parameter evtl. klassenintern gestalten, anstatt Parameter zu verwenden. Evtl. auch extra Klasse als Service erstellen, die sich um reale Werte und Berechnungen von Zeiten und Strecken kümmert, so dass die einzelnen Regale nur eine Liste an möglichen Positionen zurückgeben ergänzt um Infos zur Regalnummer/Ansteuerung !!!
        double calculateTimeInSecondsFromWayInMeters(double wayInMeters, double maxVelocityInMetersPerSecond,
                                                     double accelerationInMetersPerSquareSeconds);

        double calculateTimeNeededForHorizontalWayInSeconds(double wayInMeters);
        double calculateTimeNeededForVerticalWayInSeconds(double wayInMeters);

        //!!! Weg anhand des aktuellen Ortes der Bedienhilfe ermitteln, indem dieser Wert von ShelfPair übergeben wird
        [[nodiscard]] double calculateHorizontalWayFromArrayIndicesDifference(int arrayIndicesDifference) const;
        [[nodiscard]] double calculateVerticalWayFromArrayIndicesDifference(int arrayIndicesDifference) const;

        int calculateHorizontalArrayIndicesDifference(const SegmentDataMessage& currentSegmentOfThisShelfPair, const SegmentDataMessage& goalSegment);
        int calculateVerticalArrayIndicesDifference(const SegmentDataMessage& currentSegmentOfThisShelfPair, const SegmentDataMessage& goalSegment);

        bool static compareTwoElements(const TimeSegmentMessage& leftElement, const TimeSegmentMessage& rightElement);

    public:
        //!!! Für folgende Methoden aktuelle Position der Bedienhilfen berücksichtigen, falls diese gerade frei sind. Dies aber eher mit Überladung der Methode machen, weil die generelle Regalzeilung ja schon vor dem Warten an der Warteschlange gemacht wird.
        //!!! -> Wenn die Berechnungen soweit implementiert sind, dass auch die Wartezeiten in der Schlange im Voraus bekannt sind, Methoden noch einmal ergänzen !!!
        void reserveSegmentToAddContainer(const SegmentDataMessage &goalSegment);
        void reserveSegmentToGetContainer(const SegmentDataMessage &goalSegment);

        void addContainer(const SegmentDataMessage &goalSegment, const Container &newContainer);
        Container takeContainer(const SegmentDataMessage &goalSegment);

        std::vector<SegmentDataMessage> getListOfSegmentsBasedOnUse(const SegmentUse &containerUse, const Item& item);
        std::optional<TimeSegmentMessage> getFastestToReachSegmentsBasedOnUse(const SegmentDataMessage& currentSegment, const SegmentUse& containerUse, const Item& item);
        //!!! Folgende Methode noch aufheben, um ggf. die darüber nochmal effizienter zu gestalten !!!
        //TimeSegmentMessage getFastestToReachEmptyContainerAlt(const SegmentDataMessage& currentSegment);

        void printShelfSegments();

        void saveAsJSONFile() const;

	    std::string toString();
    };
}

#endif //NUPPROJECT_SHELF_H
