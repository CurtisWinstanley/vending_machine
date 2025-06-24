#ifndef Example_Coupled_Model_HPP
#define Example_Coupled_Model_HPP

#include <cadmium/modeling/devs/coupled.hpp>

#include <iostream>
// C++ Standard Library Headers
#include <limits>
#include <string>

using namespace cadmium;

// ------ Your includes list ------- 

 //Includes for submodels
#include "atomic_models/Example_Atomic_Model/Example_Atomic_Model.hpp"
#include "atomic_models/Example_Atomic_Model2/Example_Atomic_Model2.hpp"
#include "coupled_models/Example_Coupled_Model2/Example_Coupled_Model2.hpp"



/**
* @class Example_Coupled_Model
* @brief This model used to organize the environment of the Example_Coupled_Model DEVS model.
*/
class Example_Coupled_Model : public Coupled {
    protected:
        std::string model_id;
	public:
        Port<int> CoupledInput1;
        Port<float> CoupledOutput;

		/**
		* Constructor function for the model.
		* @param id ID of the model.
		*/
		Example_Coupled_Model(const std::string& id) : Coupled(id) {
            CoupledInput1 = addInPort<int>("CoupledInput1");
            CoupledOutput = addOutPort<float>("CoupledOutput");

            model_id = id;
        
 
            auto Example_Atomic_Model_4047377077 = addComponent<Example_Atomic_Model>(model_id + "_1" );
            auto Example_Atomic_Model2_370608149 = addComponent<Example_Atomic_Model2>(model_id + "_2" );
            auto Example_Coupled_Model2_1945197320 = addComponent<Example_Coupled_Model2>(model_id + "_3" );
            //EICs
            addCoupling(CoupledInput1, Example_Atomic_Model2_370608149->Input1);
            addCoupling(CoupledInput1, Example_Coupled_Model2_1945197320->Input1);
            //EOCs
            addCoupling(Example_Atomic_Model2_370608149->Output2, CoupledOutput);
            //ICs
            addCoupling(Example_Atomic_Model2_370608149->Output1, Example_Atomic_Model_4047377077->Input1);

		}

};

#endif //Example_Coupled_Model_HPP








