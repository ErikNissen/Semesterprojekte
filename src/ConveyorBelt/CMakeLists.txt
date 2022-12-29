add_library(ConveyorBelt
        ConveyorBelt.cpp
        ConveyorBeltRetrieve.cpp
        ConveyorBeltStore.cpp
        TransferPoint.cpp
        IPoint.cpp
        KPoint.cpp)

target_include_directories(ConveyorBelt
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(ConveyorBelt
        Item
        Inventory
        Messages
        )