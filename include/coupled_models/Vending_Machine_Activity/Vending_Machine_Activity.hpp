#ifndef Vending_Machine_Activity_HPP
#define Vending_Machine_Activity_HPP

#include <cadmium/modeling/devs/coupled.hpp>

#include <iostream>
// C++ Standard Library Headers
#include <limits>
#include <string>

using namespace cadmium;

// ------ Your includes list ------- 

 //Includes for submodels
#include "atomic_models/VM_Purchase/VM_Purchase.hpp"
#include "atomic_models/Customers/Customers.hpp"
#include "atomic_models/VM_Audio/VM_Audio.hpp"



/**
* @class Vending_Machine_Activity
* @brief This model used to organize the environment of the Vending_Machine_Activity DEVS model.
*/
class Vending_Machine_Activity : public Coupled {
    protected:
        std::string model_id;
	public:
        Port<bool> i_start_customer_activity;
        Port<int> o_logged_dispense_id;

		/**
		* Constructor function for the model.
		* @param id ID of the model.
		*/
		Vending_Machine_Activity(const std::string& id) : Coupled(id) {
            i_start_customer_activity = addInPort<bool>("i_start_customer_activity");
            o_logged_dispense_id = addOutPort<int>("o_logged_dispense_id");

            model_id = id;
        
 
            auto VM_Purchase_863366135 = addComponent<VM_Purchase>(model_id + "_1" );
            auto Customers_559098369 = addComponent<Customers>(model_id + "_2" );
            auto VM_Audio_3341052146 = addComponent<VM_Audio>(model_id + "_3" );
            //EICs
            addCoupling(i_start_customer_activity, Customers_559098369->i_start_customer_activity);
            //EOCs
            //ICs
            addCoupling(VM_Purchase_863366135->o_change, Customers_559098369->i_change_owed);
            addCoupling(VM_Purchase_863366135->o_dispense_id, Customers_559098369->i_dispensed_beverage);
            addCoupling(Customers_559098369->o_selected_beverage, VM_Purchase_863366135->i_beverage_selection);
            addCoupling(Customers_559098369->o_money, VM_Purchase_863366135->i_money);
            addCoupling(VM_Purchase_863366135->o_audio_message, VM_Audio_3341052146->i_message_to_speak);

		}

};

#endif //Vending_Machine_Activity_HPP








