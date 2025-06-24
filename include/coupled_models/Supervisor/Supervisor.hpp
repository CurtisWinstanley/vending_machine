#ifndef Supervisor_HPP
#define Supervisor_HPP

#include <cadmium/modeling/devs/coupled.hpp>

#include <iostream>
// C++ Standard Library Headers
#include <limits>
#include <string>

using namespace cadmium;

// ------ Your includes list ------- 

 //Includes for submodels
#include "coupled_models/External_Messages/External_Messages.hpp"
#include "atomic_models/Takeoff/Takeoff.hpp"
#include "atomic_models/Waypoint_Follow/Waypoint_Follow.hpp"
#include "atomic_models/Landing/Landing.hpp"



/**
* @class Supervisor
* @brief This model used to organize the environment of the Supervisor DEVS model.
*/
class Supervisor : public Coupled {
    protected:
        std::string model_id;
	public:
        Port<int> abort;
        Port<int> complete;

		/**
		* Constructor function for the model.
		* @param id ID of the model.
		*/
		Supervisor(const std::string& id) : Coupled(id) {
            abort = addInPort<int>("abort");
            complete = addOutPort<int>("complete");

            model_id = id;
        
 
            auto External_Messages_927918088 = addComponent<External_Messages>(model_id + "_1" );
            auto Takeoff_779531715 = addComponent<Takeoff>(model_id + "_3" );
            auto Waypoint_Follow_3657918440 = addComponent<Waypoint_Follow>(model_id + "_2" );
            auto Landing_3654129461 = addComponent<Landing>(model_id + "_4" );
            //EICs
            addCoupling(abort, Takeoff_779531715->abort_takeoff);
            addCoupling(abort, Landing_3654129461->abort_landing);
            //EOCs
            addCoupling(Landing_3654129461->landing_complete, complete);
            //ICs
            addCoupling(External_Messages_927918088->message, Waypoint_Follow_3657918440->waypoint);
            addCoupling(External_Messages_927918088->message, Takeoff_779531715->takeoff_point);
            addCoupling(External_Messages_927918088->message, Landing_3654129461->landing_point);

		}

};

#endif //Supervisor_HPP








