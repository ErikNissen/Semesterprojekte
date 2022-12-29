add_library(
        PersistentFileManagement
        PersistentFileManagement.cpp
)

target_include_directories(
        PersistentFileManagement PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)