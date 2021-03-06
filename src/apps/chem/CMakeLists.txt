# src/apps/chem

add_definitions(-DMRA_CHEMDATA_DIR=\"${CMAKE_CURRENT_SOURCE_DIR}\")

# Set the CHEM sources and header files
set(MADCHEM_HEADERS
    correlationfactor.h molecule.h molecularbasis.h corepotential.h atomutil.h
    SCF.h xcfunctional.h mp2.h nemo.h potentialmanager.h gth_pseudopotential.h
    molecular_optimizer.h projector.h TDA.h TDA_XC.h TDA_guess.h TDA_exops.h
    SCFOperators.h CCOperators.h CCStructures.h CC2.h CISOperators.h
    electronic_correlation_factor.h cheminfo.h vibanal.h)
set(MADCHEM_SOURCES
    correlationfactor.cc molecule.cc molecularbasis.cc corepotential.cc
    atomutil.cc lda.cc cheminfo.cc distpm.cc SCF.cc gth_pseudopotential.cc 
    nemo.cc mp2.cc SCFOperators.cc TDA.cc TDA_XC.cc CC2.cc CCOperators.cc 
    CISOperators.cc vibanal.cc)
if(LIBXC_FOUND)
  list(APPEND MADCHEM_SOURCES xcfunctional_libxc.cc)
else()
  list(APPEND MADCHEM_SOURCES xcfunctional_ldaonly.cc)
endif()

# Create the MADchem library
add_mad_library(chem MADCHEM_SOURCES MADCHEM_HEADERS "mra" "chem/")

# Add dependencies for MADchem
target_include_directories(MADchem PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/src/apps/>)
if(LIBXC_FOUND)
  target_include_directories(MADchem PUBLIC ${LIBXC_INCLUDE_DIRS})
  target_link_libraries(MADchem PUBLIC ${LIBXC_LIBRARIES})
endif()

# Add executables
add_executable(plotxc plotxc.cc xcfunctional.h)
target_link_libraries(plotxc MADchem)

# Install files
install(FILES sto-3g sto-6g 6-31g coredata/mcp coredata/mcp2 coredata/mcp_guess
    DESTINATION "${MADNESS_INSTALL_DATADIR}"
    COMPONENT chem)

# Add unit tests    
if(ENABLE_UNITTESTS)
  
  # The list of unit test source files
  set(CHEM_TEST_SOURCES test_SCFOperators.cc test_dft.cc)
  
  add_unittests(chem CHEM_TEST_SOURCES "MADchem;MADgtest")
  
  # Create other test executables not included in the unit tests
  set(CHEM_OTHER_TESTS testxc)
  foreach(_test ${CHEM_OTHER_TESTS})  
    add_executable(${_test} EXCLUDE_FROM_ALL ${_test}.cc)
    target_link_libraries(${_test} MADchem)
  endforeach()
  
endif()
