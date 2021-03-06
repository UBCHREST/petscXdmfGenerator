# Download google test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0
)

FetchContent_MakeAvailable(googletest)

add_executable(tests "")
target_link_libraries(tests PUBLIC gtest gtest_main petscXdmfGeneratorLibrary ${HDF5_LIBRARIES})
default_target_compile_options(tests)

target_sources(tests
        PRIVATE
        integrationTests.cpp
        )

gtest_discover_tests(tests
        # set a working directory so your project root so that you can find test data via paths relative to the project root
        WORKING_DIRECTORY ${PROJECT_DIR}
        PROPERTIES VS_DEBUGGER_WORKING_DIRECTORY "${PROJECT_DIR}"
        )

add_custom_command(
        TARGET tests
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/outputs/
        $<TARGET_FILE_DIR:tests>/outputs
)

add_custom_command(
        TARGET tests
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/inputs/
        $<TARGET_FILE_DIR:tests>/inputs
)
