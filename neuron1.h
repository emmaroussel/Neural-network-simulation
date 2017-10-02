#ifndef NEURON1_HPP
#define NEURON1_HPP

using namespace std;
#include <iostream>
#include <vector>
#include <cmaths>

class Neuron {
  public :
    //CONSTRUCTOR
    Neuron();
    Neuron(double membrane_potential, double membrane_potential_threshold);

    //GETTERS
    double getMembranePotential() const;
    double getMembranePotentialThreshold() const;
    int getNbSpikes() const;
    vector<double> getSpikesTimes() const;
    bool isRefractory() const;

    //SETTER
    void setMembranePotential(double);
    void setNbPikes(int);
    void updateSpikesTimes(double time);
    void setRefractory(bool state);

    //METHODS
    void update(double t_start, double t_end, double current, double h);
    void updateMembranePotential(double current, double h, double tho, double resistance);


  private :
    double membrane_potential_;
    double membrane_potential_threshold_;
    /*unsigned*/ int nb_spikes_;
    vector<double> spikes_times_;
    bool refractory_;
};


#endif
