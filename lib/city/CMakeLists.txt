add_library(
        city
        City.cpp
        City.h
)

target_link_libraries(
        city
        PRIVATE cpr::cpr
        PRIVATE days
        PRIVATE nlohmann_json::nlohmann_json
)

target_include_directories(city PUBLIC ${PROJECT_SOURCE_DIR})
