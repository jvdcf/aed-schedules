cmake_minimum_required(VERSION 3.26)
project(AED2324_PRJ1_G23)

set(CMAKE_CXX_STANDARD 20)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs/output")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)

    message("Doxygen build started")
    add_custom_target(Doxygen ALL
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}"
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
            COMMENT "Generating API documentation with Doxygen"
            VERBATIM)
else(DOXYGEN_FOUND)
    message("Doxygen needs to be installed to generate the documentation.")
endif(DOXYGEN_FOUND)

# Project build
add_executable(AED2324_PRJ1_G23 main.cpp
        src/CSVClasses.cpp src/CSVClasses.hpp
        src/CSVClassesPerUC.cpp src/CSVClassesPerUC.hpp
        src/CSVStudentsClasses.cpp src/CSVStudentsClasses.hpp
        src/Lesson.cpp src/Lesson.hpp
        src/ClassesPerUC.cpp src/ClassesPerUC.hpp
        src/StudentsClasses.cpp src/StudentsClasses.hpp
        src/Utils.cpp src/Utils.hpp
        src/Runtime.cpp src/Runtime.hpp
        src/ClassSchedule.cpp src/ClassSchedule.hpp
        src/Student.cpp src/Student.hpp
        src/Process.cpp src/Process.hpp)
