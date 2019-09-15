cmake_minimum_required(VERSION 3.0)
project(CprimesGmp LANGUAGES NONE)

if (NOT WIN32)
    message(WARNING "This file only exists to download MPIR on Windows. If you see this message, you might be doing something wrong.")
endif()

include(FetchContent)

# set(MPIR_URL "${CMAKE_SOURCE_DIR}/gmp/vcpkg-export-mpir.zip")
set(MPIR_URL "https://github.com/Chris--B/Cprimes/releases/download/cmake-cleanup-rc/vcpkg-export-mpir.zip")
FetchContent_Declare(gmp
    URL     ${MPIR_URL}
    URL_MD5 F3A7EAE0DE897C9D37D1F105795778F1
)

FetchContent_GetProperties(gmp)
if (NOT ${gmp_POPULATED})

    message(STATUS "[GMP] Populating from \"${MPIR_URL}\"")
    FetchContent_Populate(gmp)

    if (CMAKE_SIZEOF_VOID_P EQUAL 4)
        # Windows 32-bit
        set(gmp_imported_prefix ${gmp_SOURCE_DIR}/installed/x86-windows-static)
    elseif (CMAKE_SIZEOF_VOID_P EQUAL 8)
        # Windows 64-bit
        set(gmp_imported_prefix ${gmp_SOURCE_DIR}/installed/x64-windows-static)
    else()
        message(FATAL_ERROR "Unexpectedly found CMAKE_SIZEOF_VOID_P=${CMAKE_SIZEOF_VOID_P}")
    endif()

    add_library(gmp STATIC IMPORTED GLOBAL)
    set(GMPLIB gmp PARENT_SCOPE)

    set_target_properties(gmp
        PROPERTIES
            IMPORTED_LOCATION               ${gmp_imported_prefix}/lib/mpir.lib
            IMPORTED_LOCATION_DEBUG         ${gmp_imported_prefix}/debug/lib/mpir.lib
    )
    target_include_directories(gmp INTERFACE ${gmp_imported_prefix}/include)

endif()

