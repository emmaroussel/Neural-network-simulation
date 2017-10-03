#include "neuron1.h"


//CONSTRUCTOR
Neuron::Neuron() : membrane_potential_(0.0), membrane_potential_threshold_(0.0),
                   nb_spikes_(0), refractory_(false)
{
  spikes_times_ = vector<double>(0);
  allMembranePotentials_ = vector<double>(0);
}

Neuron::Neuron(double membrane_potential, double membrane_potential_threshold)
: membrane_potential_(membrane_potential),
  membrane_potential_threshold_(membrane_potential_threshold),
  nb_spikes_(0), refractory_(false)
{
  spikes_times_ = vector<double>(0);
  allMembranePotentials_ = vector<double>(0);
}

//GETTERS
double Neuron::getMembranePotential() const {
  return membrane_potential_;
}

double Neuron::getMembranePotentialThreshold() const {
  return membrane_potential_threshold_;
}

int Neuron::getNbSpikes() const {
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

//SETTER
void Neuron::setMembranePotential(double potential) {
  membrane_potential_ = potential;
}

void Neuron::setNbSpikes(int nb) {
  nb_spikes_ = nb;
}

void Neuron::incrementNbSpikes(int increment) {
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

//METHODS
void Neuron::updateMembranePotential(double current, double h, double tho, double resistance) {
    setMembranePotential(exp(-h/tho)*membrane_potential_ + current*resistance*(1-exp(-h/tho)));
}

void Neuron::update(double t_start, double t_stop,
                    double inf, double sup,
                    double strenghtCurrent, double h,
                    double tho, double resistance) {
  /*where h = the increment for time (dt), tho is a time constant (~1000ms),
  strenghtCurrent is in pA*/

 double simTime(t_start);
 double input_current(0.0);
 double refractory_time(1.0);
 //After a spike, the membran potential will be equal to 0 during the refractory time (here 1ms)
 double increment(0.0);

 while (simTime < t_stop) {
     
   //Value of the current according to simTime
   if ((simTime >= inf)and(simTime < sup)) {
     input_current = strenghtCurrent;
   } else { input_current = 0.0; }


   if (isRefractory()) {
     membrane_potential_ = 0.0;
     if (increment >= refractory_time) setRefractory(false);
       
   } else if (membrane_potential_ > membrane_potential_threshold_) {
     updateSpikesTimes(simTime);
     incrementNbSpikes(1);
     setRefractory(true);
     /*At the next loop, the membrane potential will be 0 as the membrane potential
     exceeds the membrane potential threshold.
     We need V=0 for "refractory_time" ms after the spike*/
      increment = 0.0;
   }

   updateAllMembranePotentials(membrane_potential_);
   updateMembranePotential(input_current, h, tho, resistance);
   
   simTime += h;
     
    /*We use this increment to make sure the potential will stay equal to 0 until the refractory time
     is reached/exceeded*/
    if (isRefractory()) increment += h;
     
 }
}

