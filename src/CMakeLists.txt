add_executable(kc 
  main.cpp
  fs/fs.cpp
  fs/FileEntry.cpp
  parse/Link.cpp
  parse/FileContext.cpp
  parse/FileContextCache.cpp
  logging.cpp
  config.cpp
)

FetchContent_Declare(
  Boost
  GIT_REPOSITORY https://github.com/boostorg/boost.git
  GIT_TAG boost-1.82.0
)
FetchContent_MakeAvailable(Boost)

target_link_libraries(kc PRIVATE Boost::program_options Boost::log Boost::date_time Boost::filesystem Boost::system Boost::thread Boost::log_setup Boost::chrono Boost::atomic library)