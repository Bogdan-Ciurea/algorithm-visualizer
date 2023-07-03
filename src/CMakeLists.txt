set(SOURCES
    standalone-functions/search-algorithms.cpp
    standalone-functions/sorting-algorithms.cpp
    standalone-functions/graph-algorithms.cpp
    interfaces/graph-interface.cpp
    interfaces/main-interface.cpp
    interfaces/search-interface.cpp
    interfaces/sorting-interface.cpp
    interfaces/tree-interface.cpp
    pillar-objects.cpp
    node-objects.cpp
    raygui.cpp
    main.cpp
)

add_library(${PROJECT_LIBS} ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")
