include(FetchContent)

FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.5.2
)

FetchContent_MakeAvailable(Catch2)

file(GLOB TEST_SOURCES
        test_*.cpp
)

add_executable(gt_tests
        ${TEST_SOURCES}
)

target_include_directories(gt_tests PUBLIC ../src)

target_link_libraries(gt_tests PRIVATE
        game
        search
        agents
        Catch2::Catch2WithMain
)

enable_testing()
add_test(NAME GeneralizedTTTTests COMMAND gt_tests)
