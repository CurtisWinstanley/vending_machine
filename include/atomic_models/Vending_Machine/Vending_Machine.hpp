#ifndef Vending_Machine_HPP
#define Vending_Machine_HPP
#include <cadmium/modeling/devs/atomic.hpp>
// C++ Standard Library Headers
#include <limits>
#include <string>
#include <iostream>

using namespace cadmium;

// ------ Your includes list ------- 
// Include headers
#include "item_selection_t.hpp"

             
//enum for representing the states
enum class Vending_Machine_States {    
   Check_Amount, 
   ____Dispense___Beverage, 
   _____Collect____Currency, 
   ____Wait_For___Selection, 
   Output_Change 

}; //end of the enum


// Function to convert the enum for states to an enum to the corresponding string
std::string enumToString(Vending_Machine_States state) {
    switch (state) {
        case Vending_Machine_States::Check_Amount:
            return "Check_Amount" ;

        case Vending_Machine_States::____Dispense___Beverage:
            return "____Dispense___Beverage" ;

        case Vending_Machine_States::_____Collect____Currency:
            return "_____Collect____Currency" ;

        case Vending_Machine_States::____Wait_For___Selection:
            return "____Wait_For___Selection" ;

        case Vending_Machine_States::Output_Change:
            return "Output_Change" ;

        default:
            return "invalid";
    }
}


//struct that contains the state variables of the model (as well as some other stuff)
struct Vending_Machine_State {
	int nInternals, nExternals, nInputs;
	mutable double clock, sigma;
    Vending_Machine_States ___current_state___;
    //State Variables of the model
    mutable bool received_beverage_selection;
    mutable bool received_money;
    mutable item_selection_t beverage_selected;
    mutable float total_money_inserted;
    mutable float new_money;
    mutable float change_to_output;
    mutable int id_to_output;

	Vending_Machine_State(): nInternals(), nExternals(), nInputs(), clock(), sigma(std::numeric_limits<double>::infinity()), ___current_state___() {}
};
    
std::ostream &operator << (std::ostream& os, const Vending_Machine_State& x) {
    os << "[-|state|-]" << enumToString(x.___current_state___) << "[-|state|-]";
    os << "[-|sigma|-]" << x.sigma << "[-|sigma|-]";
    os << "[-|~:received_beverage_selection:~|-]" << x.received_beverage_selection << "[-|~:received_beverage_selection:~|-]";
    os << "[-|~:received_money:~|-]" << x.received_money << "[-|~:received_money:~|-]";
    os << "[-|~:beverage_selected:~|-]" << x.beverage_selected << "[-|~:beverage_selected:~|-]";
    os << "[-|~:total_money_inserted:~|-]" << x.total_money_inserted << "[-|~:total_money_inserted:~|-]";
    os << "[-|~:new_money:~|-]" << x.new_money << "[-|~:new_money:~|-]";
    os << "[-|~:change_to_output:~|-]" << x.change_to_output << "[-|~:change_to_output:~|-]";
    os << "[-|~:id_to_output:~|-]" << x.id_to_output << "[-|~:id_to_output:~|-]";

    return os;
}

class Vending_Machine: public Atomic<Vending_Machine_State> {
    protected:
        std::string model_id;
        
    public:
        Port<item_selection_t> i_beverage_selection;
        Port<float> i_money;
        Port<float> o_change;
        Port<int> o_dispense_id;


        explicit Vending_Machine(const std::string& id): Atomic<Vending_Machine_State>(id, Vending_Machine_State()) { 
            i_beverage_selection = addInPort<item_selection_t>("i_beverage_selection");
            i_money = addInPort<float>("i_money");
            o_change = addOutPort<float>("o_change");
            o_dispense_id = addOutPort<int>("o_dispense_id");

            state.___current_state___ = Vending_Machine_States::____Wait_For___Selection; //Initial state is ____Wait_For___Selection
            state.nExternals = 0;
            state.nInternals = 0;
            state.nInputs = 0;
            model_id = id;
            
            // model = std::make_shared<GenericSharedMemoryModel<Vending_Machine_shared_memory_struct>>(model_id);
            // Connect the shared memory model.
            // if(!model->connect()) {
            //     std::cout << "[ERROR]: Could not connect the " <<model_id<< " shared memory model"<< std::endl;
            // }
            
            // Initialize State Variables
            state.received_beverage_selection = false;
            state.received_money = false;
            state.beverage_selected.price = 0;
            state.beverage_selected.item_id = -1; 
            state.total_money_inserted = 0;
            state.new_money = 0;
            state.change_to_output = 0;
        }
        using Atomic<Vending_Machine_State>::internalTransition;
        using Atomic<Vending_Machine_State>::externalTransition;
        using Atomic<Vending_Machine_State>::confluentTransition;
        using Atomic<Vending_Machine_State>::output;
        using Atomic<Vending_Machine_State>::timeAdvance;

        const Vending_Machine_State& getState() {
            return state;
        }
        void internalTransition(Vending_Machine_State& state) const override {
            state.clock += state.sigma;
            //state.sigma = ++state.nInternals;
            switch (state.___current_state___) { 
                case Vending_Machine_States::____Dispense___Beverage:{
                    //Reset state variables
                    state.change_to_output = 0;
                    state.total_money_inserted = 0;
                    state.received_beverage_selection = false;

                    if(true)
                    {
                        state.___current_state___ = Vending_Machine_States::____Wait_For___Selection;
                        state.sigma = std::numeric_limits<double>::infinity();  // For logging
                        return; // We switched states, return
                    }
                
                return;
                }
                case Vending_Machine_States::Output_Change:{


                    if(true)
                    {
                        state.___current_state___ = Vending_Machine_States::____Dispense___Beverage;
                        state.sigma = 5;  // For logging
                        return; // We switched states, return
                    }
                
                return;
                }
                case Vending_Machine_States::Check_Amount:{
                    //Add the new money to the total
                    state.total_money_inserted += state.new_money;
                    //reset the state variable
                    state.received_money = false;

                    if((state.total_money_inserted < state.beverage_selected.price))
                    {
                        state.___current_state___ = Vending_Machine_States::_____Collect____Currency;
                        state.sigma = std::numeric_limits<double>::infinity();  // For logging
                        return; // We switched states, return
                    }
                
                    if((state.total_money_inserted >= state.beverage_selected.price))
                    {
                        state.___current_state___ = Vending_Machine_States::Output_Change;
                        state.sigma = 10;  // For logging
                        return; // We switched states, return
                    }
                
                return;
                }
                default:
                    break;
            }
            // write_to_shared_mem(state);
            return;
        }
        
        void externalTransition(Vending_Machine_State& state, double e) const override {
            state.clock += e;
            state.nExternals += 1;

            //store information about total number of inputs
            state.nInputs += (int) i_beverage_selection->size();
            state.nInputs += (int) i_money->size();
            //flags for port received
            bool ___r_i_beverage_selection = !i_beverage_selection->empty();
            bool ___r_i_money = !i_money->empty();

            switch (state.___current_state___) {
                case Vending_Machine_States::____Wait_For___Selection:{



                    state.received_beverage_selection = ___r_i_beverage_selection;



                    if(___r_i_beverage_selection){
                        state.beverage_selected = i_beverage_selection->getBag().back();
                    }



                    if((state.received_beverage_selection))
                    {
                        state.___current_state___ = Vending_Machine_States::_____Collect____Currency;
                        state.sigma = std::numeric_limits<double>::infinity(); // For logging
                        return; // We switched states, return
                    }
                    
                return;
                }
                case Vending_Machine_States::_____Collect____Currency:{



                    state.received_money = ___r_i_money;



                    if(___r_i_money){
                        state.new_money = i_money->getBag().back();
                    }



                    if((state.received_money))
                    {
                        state.___current_state___ = Vending_Machine_States::Check_Amount;
                        state.sigma = 0; // For logging
                        return; // We switched states, return
                    }
                    
                return;
                }
                default:
                    break;
            }
            // write_to_shared_mem(state);
            return;
        }
             
        void output(const Vending_Machine_State& state) const override {
            switch (state.___current_state___) { 
                case Vending_Machine_States::____Dispense___Beverage:{
                    //Set the ID to output
                    state.id_to_output = state.beverage_selected.item_id;
                    if(true)
                    {
                        o_dispense_id->addMessage(state.id_to_output);

                    }
                
                return;
                }     
                
                case Vending_Machine_States::Output_Change:{
                    state.change_to_output = state.total_money_inserted - state.beverage_selected.price;
                    if(true)
                    {
                        o_change->addMessage(state.change_to_output);

                    }
                
                return;
                }     
                
                case Vending_Machine_States::Check_Amount:{

                    if((state.total_money_inserted < state.beverage_selected.price))
                    {

                    }
                
                    if((state.total_money_inserted >= state.beverage_selected.price))
                    {

                    }
                
                return;
                }     
                
                default:
                    break;
                
            }
            return;
        }

        [[nodiscard]] double timeAdvance(const Vending_Machine_State& state) const override {
                switch (state.___current_state___) { 

            case Vending_Machine_States::Check_Amount:
                // state.sigma = 0;
                return 0;

            case Vending_Machine_States::____Dispense___Beverage:
                // state.sigma = 5;
                return 5;

            case Vending_Machine_States::_____Collect____Currency:
                // state.sigma = std::numeric_limits<double>::infinity();
                return std::numeric_limits<double>::infinity();

            case Vending_Machine_States::____Wait_For___Selection:
                // state.sigma = std::numeric_limits<double>::infinity();
                return std::numeric_limits<double>::infinity();

            case Vending_Machine_States::Output_Change:
                // state.sigma = 10;
                return 10;

            default:
                break;
            }
            return state.sigma;
        }      
};
#endif //Vending_Machine_HPP