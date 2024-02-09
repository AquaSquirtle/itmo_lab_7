add_library(
        config
        Config.h
        Config.cpp
)

target_link_libraries(config PRIVATE nlohmann_json::nlohmann_json)