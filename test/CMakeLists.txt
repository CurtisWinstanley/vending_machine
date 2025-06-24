###---Vending_Machine CONFIG BEGIN---###
add_executable(td_Vending_Machine "Vending_Machine/td_Vending_Machine.cpp")


if(WIN32)
    # CMake configurations for windows
    target_link_libraries(td_Vending_Machine wsock32 ws2_32)
    target_include_directories(td_Vending_Machine PUBLIC ${includes_list})
endif()


if(UNIX)
    # CMake configurations for unix
    target_include_directories(td_Vending_Machine PUBLIC ${includes_list})
endif()


if(APPLE)
    # CMake configurations for apple
    target_link_directories(td_Vending_Machine PUBLIC /usr/local/opt/icu4c/lib)
    target_link_libraries(td_Vending_Machine icudata)
    target_include_directories(td_Vending_Machine PUBLIC ${includes_list})
endif()
###---Vending_Machine CONFIG END---###
