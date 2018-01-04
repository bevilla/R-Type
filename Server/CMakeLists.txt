CMAKE_MINIMUM_REQUIRED(VERSION 3.1)

SET(EXECUTABLE_OUTPUT_PATH "${CMAKE_CURRENT_SOURCE_DIR}")

# debug
IF(UNIX)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3")
ENDIF()
# debug

SET(EXECUTABLE_NAME "rtype_server")
SET(SRC_DIR "./src/")
SET(INC_DIR "./inc/")

SET(SOCKET_DIR "./Socket/")
SET(SOCKET_SRC_DIR "${SOCKET_DIR}/src/")
SET(SOCKET_INC_DIR "${SOCKET_DIR}/inc/")

SET(SOURCES
    "${SRC_DIR}main.cpp"
    "${SRC_DIR}Server.cpp"
    "${SRC_DIR}Player.cpp"
    "${SRC_DIR}Room.cpp"
    "${SRC_DIR}Enemy.cpp"
    "${SOCKET_SRC_DIR}TcpSocket.cpp"
    "${SOCKET_SRC_DIR}TcpListener.cpp"
)

IF(WIN32)
	SET(SOURCES ${SOURCES}
	    "${SOCKET_SRC_DIR}WinTcpSocket.cpp"
	    "${SOCKET_SRC_DIR}WinTcpListener.cpp"
	   )
ELSEIF(UNIX)
	SET(SOURCES ${SOURCES}
	    "${SOCKET_SRC_DIR}UnixTcpSocket.cpp"
	    "${SOCKET_SRC_DIR}UnixTcpListener.cpp"
	   )
ENDIF()

INCLUDE_DIRECTORIES(
    "${CMAKE_CURRENT_SOURCE_DIR}/${INC_DIR}"
    "${CMAKE_CURRENT_SOURCE_DIR}/${SOCKET_INC_DIR}"
)

ADD_EXECUTABLE("${EXECUTABLE_NAME}" ${SOURCES})
