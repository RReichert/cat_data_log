set(SOURCE_FILES data_log.cpp)
set(HEADER_FILES data_log.h)

find_package(Boost REQUIRED COMPONENTS filesystem iostreams system)

add_executable(cat_data_log cat_data_log.cpp ${SOURCE_FILES} ${HEADER_FILES})
target_include_directories(cat_data_log PUBLIC ${Boost_INCLUDE_DIRS})
target_link_libraries(cat_data_log ${Boost_LIBRARIES})
