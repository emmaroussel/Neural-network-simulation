#include <neuron1.h>

using namespace std;

//CONSTRUCTOR
Neuron::Neuron() : membrane_potential_(0.0), membrane_potential_threshold_(0.0),
                   nb_spikes_(O)
{
  spikes_times_ = vector(1, 0);
}

Neuron::Neuron(double membrane_potential, double membrane_potential_threshold)
: membrane_potential_(membrane_potential),
  membrane_potential_threshold_(membrane_potential_threshold),
  nb_spikes_(O)
{
  spikes_times_ = vector(1, 0);
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

//SETTER
void Neuron::setMembranePotential(double potential) {
  membrane_potential_ = potential;
}

void Neuron::setNbPikes(int nb) {
  nb_spikes_ = nb;
}

void Neuron::updateSpikesTimes(double spikeTime) {
  if (spikes_times_.size() == 1) {
    spikes_times_[0] = spikeTime;
  } else {
    spikes_times_.pushback(spikeTime);
  }
}

bool Neuron::isRefractory() const {
  return refractory_;
}

//METHODS
void Neuron::update(double t_start, double t_stop, double strenghtCurrent, double h,
                    double tho, double resitance) {
  //where h = the increment for time (dt), tho is a time constant (~1000ms),
  //strenghtCurrent is in pA

 //INITIALIZE ?
 
 double simtime(t_start);
 double imput_current(strenghtCurrent);

 while (simtime < t_stop) {
   //imput_current = I(t) --> change en fonction du temps !
   if (isRefractory()) {
     membrane_potential_ = 0.0;
   } else if (membrane_potential_ > membrane_potential_threshold_) {
     updateSpikesTimes(simTime);
   }

   updateMembranePotential(imput_current, h, tho, resistance);
 }

}

void Neuron::updateMembranePotential(double current, double h, double tho, double resistance) {
  setMembranePotential(
    exp(-h/tho)*membrane_potential_ + current*(resistance/tho)*(1-exp(-h/tho));
  );
}
