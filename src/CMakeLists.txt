add_executable(kc
    main.cpp
    appcontext.cpp
    fs/fs.cpp
    fs/FileEntry.cpp
    parse/Link.cpp
    parse/FileContext.cpp
    parse/FileContextCache.cpp
    valid/link.cpp
    logging.cpp
    config.cpp
    print/print.cpp
    task/task.cpp
    task/current_tasks.cpp
    net/ntfy.cpp
    net/http.cpp
)

FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.87.0
)
FetchContent_MakeAvailable(Boost)

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

if(OPENCV)
add_compile_definitions(WITH_OPENCV)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
target_sources(kc PRIVATE image/img.cpp)
endif()

target_link_libraries(kc PRIVATE Boost::program_options Boost::log Boost::date_time Boost::filesystem Boost::system Boost::thread Boost::log_setup Boost::chrono Boost::atomic Boost::asio Boost::beast Boost::json Boost::algorithm ${OPENSSL_LIBRARIES} ${OpenCV_LIBS})