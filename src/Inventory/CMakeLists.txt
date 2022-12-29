add_library(Inventory
        Inventory.cpp
        ShelfPair.cpp
        Shelf.cpp
        Segment.cpp
        )

target_include_directories(Inventory
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# ToDO: muss PersistentFileManagement tatsächlich noch hier gelinkt werden, wenn Item schon gelinkt ist, wo PersistentFileManagement reingelinkt ist?
target_link_libraries(Inventory
        Item
        PersistentFileManagement
        ConveyorBelt
        )

