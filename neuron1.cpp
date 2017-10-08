#include "neuron1.h"


//CONSTRUCTOR
Neuron::Neuron() : membrane_potential_(V_INI), nb_spikes_(0), refractory_(false)
{}

/**********************************************************************************/

//GETTERS
double Neuron::getMembranePotential() const {
  return membrane_potential_;
}

unsigned int Neuron::getNbSpikes() const {
  return nb_spikes_;
}

vector<double> Neuron::getSpikesTimes() const {
  return spikes_times_;
}

vector<double> Neuron::getAllMembranePotentials() const {
  return allMembranePotentials_;
}

bool Neuron::isRefractory() const {
  return refractory_;
}

/**********************************************************************************/

//SETTERS
void Neuron::setMembranePotential(double potential) {
  membrane_potential_ = potential;
}

void Neuron::setNbSpikes(int nb) {
  nb_spikes_ = nb;
}

void Neuron::incrementNbSpikes(unsigned int increment) {
    setNbSpikes(nb_spikes_ + increment);
}

void Neuron::updateSpikesTimes(double spikeTime) {
    spikes_times_.push_back(spikeTime);
}

void Neuron::updateAllMembranePotentials(double potential) {
    allMembranePotentials_.push_back(potential);
}

void Neuron::setRefractory(bool state) {
  refractory_ = state;
}

/**********************************************************************************/

//METHODS
void Neuron::updateMembranePotential(double current, double h, double tau, double resistance) {
    setMembranePotential(exp(-h/tau)*membrane_potential_ + current*resistance*(1-exp(-h/tau)));
}

void Neuron::update(double t_start, double t_stop,
                    double inf, double sup,
                    double strenghtCurrent, double h,
                    double tau, double resistance) {

 double simTime(t_start);
 double input_current(0.0);
 double increment(0.0);

 while (simTime < t_stop) {

   //Value of the current according to simTime
   if ((simTime >= inf)and(simTime < sup)) {
     input_current = strenghtCurrent;
   } else { input_current = 0.0; }

   if (isRefractory()) {
     membrane_potential_ = V_REFRAC;
     if (increment > REFRAC_TIME) {
       setRefractory(false);
       membrane_potential_ = V_RESET;
     }

   } else if (membrane_potential_ > V_THRS) {
     updateSpikesTimes(simTime);
     incrementNbSpikes(1);
     setRefractory(true);
     /*At the next loop, the membrane potential will be V_RESET as the membrane potential
     exceeds the membrane potential threshold.
     We need V = V_RESET during the refractory period*/
     increment = 0.0;
   }

   updateAllMembranePotentials(membrane_potential_);
   updateMembranePotential(input_current, h, tau, resistance);

   simTime += h;

    /*We use this increment to make sure the potential will stay equal to
    V_RESET until the refractory time is reached/exceeded*/
    if (isRefractory()) increment += h;

 }
}
