include(FetchContent)

FetchContent_Declare(
    Spdlog
    GIT_REPOSITORY https://github.com/gabime/spdlog
    GIT_TAG 79524ddd08a4ec981b7fea76afd08ee05f83755d # 1.17.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
)

FetchContent_MakeAvailable(Spdlog)
