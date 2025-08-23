cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "5" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(editor VERSION ${PROJECT_VESRION})

configure_file(version.h.in version.h)

include_directories(
    include/
    include/system
    include/contracts
    include/model
    include/notify
    include/serialization)

add_executable(editor
    main.cpp)

add_library(lib
    lib.cpp
    include/system/Traits.h
    include/system/IInterface.h
    include/system/ISerializer.h
    include/system/IObservable.h
    include/system/IObserver.h
    include/system/IDisposable.h
    include/system/ICommand.h

    include/contracts/IModel.h
    include/contracts/IView.h
    include/contracts/IDrawingContext.h

    include/model/IDocument.h
    include/model/IGraphicalObject.h
    include/model/IShape.h
    include/model/Point.h    

    src/system/Observer.cpp
    src/system/Observable.cpp
    src/system/Disposable.cpp
    src/system/Command.cpp


    src/View.cpp
    src/Model.cpp
    src/ConsoleDrawingContext.cpp


    src/model/Document.cpp


    src/model/ShapeGraphicalObject.h
    src/model/Line.h
    src/model/Rect.h
    src/model/Polygon.h
    src/model/Line.cpp
    src/model/Rect.cpp
    src/model/Polygon.cpp
    src/model/DocumentSerializer.cpp
)

set_target_properties(editor lib PROPERTIES
    CXX_STANDARD 23
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(lib
    PRIVATE "${CMAKE_BINARY_DIR}"
)

target_link_libraries(editor PRIVATE
    lib
)

install(TARGETS editor RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)


