###---Example_Coupled_Model CONFIG BEGIN---###
add_executable(Example_Coupled_Model "Example_Coupled_Model/Example_Coupled_Model.cpp")

if(WIN32)
    # CMake configurations for windows
    target_link_libraries(Example_Coupled_Model wsock32 ws2_32)
    target_include_directories(Example_Coupled_Model PUBLIC ${includes_list})
endif()

if(UNIX)
    # CMake configurations for unix
      target_include_directories(Example_Coupled_Model PUBLIC ${includes_list})
endif()

if(APPLE)
    # CMake configurations for apple
    target_link_directories(Example_Coupled_Model PUBLIC /usr/local/opt/icu4c/lib)
    target_link_libraries(Example_Coupled_Model icudata)
    target_include_directories(Example_Coupled_Model PUBLIC ${includes_list})
endif()
###---Example_Coupled_Model CONFIG END---###
###---Vending_Machine_Activity CONFIG BEGIN---###
add_executable(Vending_Machine_Activity "Vending_Machine_Activity/Vending_Machine_Activity.cpp")

if(WIN32)
    # CMake configurations for windows
    target_link_libraries(Vending_Machine_Activity wsock32 ws2_32)
    target_include_directories(Vending_Machine_Activity PUBLIC ${includes_list})
endif()

if(UNIX)
    # CMake configurations for unix
    target_include_directories(Vending_Machine_Activity PUBLIC ${includes_list})
endif()

if(APPLE)
    # CMake configurations for apple
    target_link_directories(Vending_Machine_Activity PUBLIC /usr/local/opt/icu4c/lib)
    target_link_libraries(Vending_Machine_Activity icudata)
    target_include_directories(Vending_Machine_Activity PUBLIC ${includes_list})
endif()
###---Vending_Machine_Activity CONFIG END---###
###---Supervisor CONFIG BEGIN---###
add_executable(Supervisor "Supervisor/Supervisor.cpp")


if(WIN32)
    # CMake configurations for windows
    target_link_libraries(Supervisor wsock32 ws2_32)
    target_include_directories(Supervisor PUBLIC ${includes_list})
endif()


if(UNIX)
    # CMake configurations for unix
     target_include_directories(Supervisor PUBLIC ${includes_list})
endif()


if(APPLE)
    # CMake configurations for apple
    target_link_directories(Supervisor PUBLIC /usr/local/opt/icu4c/lib)
    target_link_libraries(Supervisor icudata)
    target_include_directories(Supervisor PUBLIC ${includes_list})
endif()
###---Supervisor CONFIG END---###
