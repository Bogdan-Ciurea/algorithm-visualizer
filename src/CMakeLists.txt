set(SOURCES
    standalone-functions/search-algorithms.cpp
    standalone-functions/sorting-algorithms.cpp
    interface.cpp
    pillar.cpp
    sorter.cpp
    searcher.cpp
    graph.cpp
    trees.cpp
    raygui.cpp
    main.cpp
)

add_library(${PROJECT_LIBS} ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${PROJECT_LIBS})
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY "..")
