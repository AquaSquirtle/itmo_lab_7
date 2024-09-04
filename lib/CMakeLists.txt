add_library(test
        city/City.cpp
        city/City.h
        city/Days.h
        city/Days.cpp
        config/Config.cpp
        config/Config.h
        display/Display.h
        display/Display.cpp
)

target_link_libraries(
        test
        PRIVATE cpr::cpr
        PRIVATE nlohmann_json::nlohmann_json
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
)

target_include_directories(test PUBLIC ${PROJECT_SOURCE_DIR}/lib)
