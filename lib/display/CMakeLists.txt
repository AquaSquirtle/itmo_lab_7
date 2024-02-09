add_library(
        display
        Display.cpp
        Display.h
)
target_link_libraries(
        display
        PRIVATE ftxui::screen
        PRIVATE ftxui::dom
        PRIVATE ftxui::component
        PRIVATE city
        PRIVATE day
)

target_include_directories(display PUBLIC ${PROJECT_SOURCE_DIR})