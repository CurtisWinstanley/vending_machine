
#ifndef Vending_Machine_Activity_RT_CLOCK_CHRONO_HPP
#define Vending_Machine_Activity_RT_CLOCK_CHRONO_HPP

#ifdef _WIN32
    #undef min // This is a Windows-specific issue
#endif

#include <iostream>
#include <chrono>
#include <optional>
#include <thread>
#include "cadmium/simulation/rt_clock/rt_clock.hpp"
#include "cadmium/exception.hpp"

#include "cadmium/modeling/devs/component.hpp" //for the interrupt
#include "cadmium/modeling/devs/coupled.hpp" //for the interrupt

#include "Vending_Machine_Activity_async_inputs.hpp"



/**
* Real-time clock based on the std::chrono library. It is suitable for Linux, MacOS, and Windows.
* @tparam T Internal clock type. By default, it uses the std::chrono::steady_clock
*/
template<typename T = std::chrono::steady_clock>
class ChronoClock : RealTimeClock {
    protected:
    std::chrono::time_point<T> rTimeLast; //!< last real system time.
    std::shared_ptr<Coupled> top_model;
    std::shared_ptr<Vending_Machine_Activity_Async_Inputs> async_handle;
    bool IE;
    double startTime;
    public:

    //! The empty constructor does not check the accumulated delay jitter.
    ChronoClock() : RealTimeClock(), rTimeLast(T::now()) {
        this->top_model = NULL;
        IE = false;
        startTime = std::chrono::duration<double>(T::now().time_since_epoch()).count();
    }

    [[maybe_unused]] explicit ChronoClock(std::shared_ptr<Coupled> model) : ChronoClock() {
    
    
        IE = true;
        this->top_model = model;
        this->async_handle = std::make_shared<Vending_Machine_Activity_Async_Inputs>();
    }

    /**
    * Starts the real-time clock.
    * @param timeLast initial simulation time.
    */
    void start(double timeLast) override {
        RealTimeClock::start(timeLast);
        rTimeLast = T::now();
    }

    /**
    * Stops the real-time clock.
    * @param timeLast last simulation time.
    */
    void stop(double timeLast) override {
        rTimeLast = T::now();
        RealTimeClock::stop(timeLast);
    }

    /**
    * Waits until the next simulation time or until an external event happens.
    *
    * @param nextTime next simulation time (in seconds) for an internal transition.
    * @return next simulation time (in seconds). Return value must be less than or equal to nextTime.
    * */
    double waitUntil(double timeNext) override {
        // Handle infinity case explicitly
        if (std::isinf(timeNext)) {
            // Set `rTimeLast` to the maximum representable time_point
            rTimeLast = T::time_point::max();
        } else {
            // Add a finite duration to rTimeLast
            auto duration = std::chrono::duration_cast<typename T::duration>(
                std::chrono::duration<double>(timeNext - vTimeLast)
            );
            rTimeLast += duration;
        }
        
        // Our own fake componentd for propagating inputs
        cadmium::Component pseudo("pseudo");
        
        // port for propagating to i_start_customer_activity
        cadmium::Port<bool> i_start_customer_activity;
        i_start_customer_activity = pseudo.addOutPort<bool>("i_start_customer_activity");
        while(T::now() < rTimeLast) {
            if(IE){
                if (async_handle->ISR_flag_i_start_customer_activity()) {
                    auto data = async_handle->ISR_decode_i_start_customer_activity();
                    auto epoch = T::now().time_since_epoch();
                    double time_now = std::chrono::duration<double>(epoch).count();
                    i_start_customer_activity->addMessage(data);
                    top_model->getInPort("i_start_customer_activity")->propagate(i_start_customer_activity);
                    rTimeLast = T::now();
                    break;
                } 
        
                // We must throttle this function because it is basically executed while(true). This destroys preformance! to remedy this:
                std::this_thread::sleep_for(std::chrono::microseconds(100));
            } else {
                std::this_thread::yield();
            }
        }

#ifdef DEBUG_DELAY
        std::cout << "[DELAY] " << std::chrono::duration_cast<std::chrono::microseconds>(T::now() - rTimeLast) << std::endl;
#endif
        auto epoch = T::now().time_since_epoch();
        double time_now = std::chrono::duration<double>(epoch).count();
        return RealTimeClock::waitUntil(std::min(timeNext, time_now - startTime));
    }
};


#endif // Vending_Machine_Activity_RT_CLOCK_CHRONO_HPP   
