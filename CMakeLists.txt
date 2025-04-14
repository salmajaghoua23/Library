cmake_minimum_required(VERSION 3.16)

project(DigitalLibrary LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

# 🔍 Important : Assure que Qt6Charts est bien détecté
set(Qt6Charts_DIR "C:/Qt/6.9.0/mingw_64/lib/cmake/Qt6Charts")
#file(COPY resources/html/map.html DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
find_package(Qt6 REQUIRED COMPONENTS Core Gui Sql Widgets Charts)

#qt_add_resources(RESOURCE_FILES html.qrc)
set(SOURCES
    addbook.cpp
    addmember.cpp
    authorslist.cpp
    booklist.cpp
    deletebook.cpp
    deletemember.cpp
    digitallibrary.cpp
    editbook.cpp
    editmember.cpp
    genrelist.cpp
    login.cpp
    main.cpp
    manageauthors.cpp
    managebooks.cpp
    memberslist.cpp
    mapviewer.cpp
    newpasswd.cpp
    signup.cpp
   # stats.cpp
    studentlibrary.cpp
    ${RESOURCE_FILES}
)

set(HEADERS
    addbook.h
    addmember.h
    authorslist.h
    booklist.h
    deletebook.h
    deletemember.h
    digitallibrary.h
    editbook.h
    editmember.h
    genrelist.h
    login.h
    manageauthors.h
    managebooks.h
    memberslist.h
    mapviewer.h
    newpasswd.h
    signup.h
   # stats.h
    studentlibrary.h
    ${RESOURCE_FILES}
)

set(UIS
    addbook.ui
    addmember.ui
    authorslist.ui
    booklist.ui
    deletebook.ui
    deletemember.ui
    digitallibrary.ui
    editbook.ui
    editmember.ui
    genrelist.ui
    login.ui
    manageauthors.ui
    managebooks.ui
    memberslist.ui
    mapviewer.ui
    newpasswd.ui
    signup.ui
    studentlibrary.ui
    #stats.ui
)

set(RESOURCES
    icons.qrc
    html.qrc
)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${UIS}
    ${RESOURCES}
    statistic.h statistic.cpp statistic.ui
    mapviewer.h mapviewer.cpp mapviewer.ui
    historique.h historique.cpp historique.ui
    cart.h cart.cpp cart.ui
)

target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Gui
    Qt6::Sql
    Qt6::Widgets
    Qt6::Charts
  #  Qt6::WebEngineWidgets
)
