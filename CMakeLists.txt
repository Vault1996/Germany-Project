# This project is designed to be built outside the Insight source tree.
cmake_minimum_required(VERSION 2.8)
PROJECT(tconvolution)

set (EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/../../../bin)

#
# Project Headers
#
SET(P_HDRS
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/dip/aConvolution.h
	${CMAKE_CURRENT_SOURCE_DIR}/../../../include/dip/aNConvolution.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/aInputOutput.h
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/aImage.h
)

#
# Project Sources
#
SET(P_SRCS
    ${CMAKE_CURRENT_SOURCE_DIR}/../../../src/dip/aConvolution.cxx
	${CMAKE_CURRENT_SOURCE_DIR}/../../../src/dip/aNConvolution.cxx
    ${CMAKE_CURRENT_SOURCE_DIR}/myfilter.cxx
)

INCLUDE_DIRECTORIES(
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../../include
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../../include/dip
)
LINK_DIRECTORIES(
                  ${CMAKE_CURRENT_SOURCE_DIR}/../../../lib
)

LINK_LIBRARIES( debug atkd optimized atk )


ADD_EXECUTABLE( ${PROJECT_NAME} main.cpp
                                ${P_HDRS}  ${P_SRCS}
)


