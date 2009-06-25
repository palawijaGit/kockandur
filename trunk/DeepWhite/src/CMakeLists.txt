PROJECT(DEEPWHITE) 

CMAKE_MINIMUM_REQUIRED(VERSION 2.4.0)

FIND_PACKAGE(Qt4)

SET(DEEPWHITE_SRCS deepwhite_main.cpp
                   sgf_parser/parser_main.cpp
                   sgf_parser/sgf_node.cpp
                   sgf_parser/sgf_tree.cpp)

QT4_AUTOMOC(${DEEPWHITE_SRCS})
INCLUDE(${QT_USE_FILE})
ADD_EXECUTABLE(dwhite ${DEEPWHITE_SRCS})
TARGET_LINK_LIBRARIES(dwhite ${QT_LIBRARIES} )
