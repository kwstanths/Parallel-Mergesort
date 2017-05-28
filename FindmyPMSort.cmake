# - Try to find myPMSort
# Once done this will define
#  myPMSort_FOUND - System has myPMSort
#  myPMSort_INCLUDE_DIRS - The myPMSort include directories
#  myPMSort_LIBRARIES - The libraries needed to use myPMSort

find_path(myPMSort_INCLUDE_DIR
	NAMES myPMSort.hpp
	HINTS ${myPMSort_ROOT}/include
	DOC "The myPMSort include directory"
)

find_library(myPMSort_LIBRARIES
	NAMES myPMSort
	HINTS ${myPMSort_ROOT}/lib
	DOC "The myPMSort library"
)

if(myPMSort_INCLUDE_DIR AND myPMSort_LIBRARIES)
	set(myPMSort_FOUND 1)
endif()

# Handle the QUIETLY and REQUIRED arguments and set LOGGING_FOUND to TRUE if all myPMSorted variables are TRUE
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(myPMSort DEFAULT_MSG myPMSort_INCLUDE_DIR myPMSort_LIBRARIES)

if(myPMSort_FOUND)
	set(myPMSort_LIBRARIES ${myPMSort_LIBRARIES} )
	set(myPMSort_INCLUDE_DIRS ${myPMSort_INCLUDE_DIR} )
endif()

# Tell cmake myPMSorts to ignore the "local" variables
mark_as_advanced(myPMSort_INCLUDE_DIR myPMSort_LIBRARIES)
