#ifndef Vending_Machine_HPP
#define Vending_Machine_HPP

#include <cadmium/modeling/devs/coupled.hpp>

#include <iostream>
// C++ Standard Library Headers
#include <limits>
#include <string>

using namespace cadmium;

// ------ Your includes list ------- 

 //Includes for submodels
#include "atomic_models/VM_Purchase/VM_Purchase.hpp"
#include "atomic_models/VM_Audio/VM_Audio.hpp"



/**
* @class Vending_Machine
* @brief This model used to organize the environment of the Vending_Machine DEVS model.
*/
class Vending_Machine : public Coupled {
    protected:
        std::string model_id;
	public:
        Port<item_selection_t> i_beverage_selection;
        Port<float> i_money;

		/**
		* Constructor function for the model.
		* @param id ID of the model.
		*/
		Vending_Machine(const std::string& id) : Coupled(id) {
            i_beverage_selection = addInPort<item_selection_t>("i_beverage_selection");
            i_money = addInPort<float>("i_money");

            model_id = id;
        
 
            auto VM_Purchase_2023769544 = addComponent<VM_Purchase>(model_id + "_1" );
            auto VM_Audio_2852446593 = addComponent<VM_Audio>(model_id + "_2" );
            //EICs
            addCoupling(i_beverage_selection, VM_Purchase_2023769544->i_beverage_selection);
            addCoupling(i_money, VM_Purchase_2023769544->i_money);
            //EOCs
            //ICs
            addCoupling(VM_Purchase_2023769544->o_audio_message, VM_Audio_2852446593->i_message_to_speak);

		}

};

#endif //Vending_Machine_HPP








