CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
INCLUDE_DIRECTORIES(./includes)
LINK_DIRECTORIES( ./lib/arm)
#/opt/eclipse_hinge/plugins/configure/include ./lib/arm /opt/poky/2.4.2/sysroots/aarch64-poky-linux/lib
AUX_SOURCE_DIRECTORY(./src DIR_SRCS)

ADD_EXECUTABLE(SoftwareUpdate ${DIR_SRCS})

TARGET_LINK_LIBRARIES(SoftwareUpdate pthread PocoFoundation PocoUtil jsconfig PocoXML PocoZip com log boost_filesystem boost_system boost_thread cgroup dlt doip fileaccess keyvaluestorage ostree-1 PocoFoundation someip-sd)
