add_library(Messages
        SegmentDataMessage.cpp
        TimeSegmentMessage.cpp
        TransferMessage.cpp
        )

target_include_directories(Messages
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})