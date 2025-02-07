
// Platform specific include order fix for Windows.
#ifdef _WIN32
#include <WinSock2.h>
#undef min
#undef max
#endif      
#include "cadmium/simulation/rt_root_coordinator.hpp"
#include "coupled_models/Example_Coupled_Model/Example_Coupled_Model.hpp"
#include <cadmium/simulation/rt_clock/chrono.hpp>
        
#ifndef NO_LOGGING
    #include "cadmium/simulation/logger/csv.hpp"
#endif

//helpers
#include "td_helpers.hpp"

//c++ headers
#include <limits>
#include <filesystem>


int main() {
    std::filesystem::path cpp_file_path = __FILE__;
    std::string log_file = get_log_file_dir(cpp_file_path, "Example_Coupled_Model");
        
   

    
    std::shared_ptr<Example_Coupled_Model> model = std::make_shared<Example_Coupled_Model>("0"
    
    );
    cadmium::ChronoClock<std::chrono::steady_clock> clock;
    auto rootCoordinator = cadmium::RealTimeRootCoordinator<ChronoClock<std::chrono::steady_clock>> (model, clock);

    #ifndef NO_LOGGING
    rootCoordinator.setLogger<cadmium::CSVLogger>(log_file, ";");
    #endif

    rootCoordinator.start();

    rootCoordinator.simulate(std::numeric_limits<double>::infinity());

    rootCoordinator.stop();	

    return 0;
}