#ifndef NEURON1_H
#define NEURON1_H

#include "Constants.hpp"
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Neuron {
  public :
    //CONSTRUCTORS
    Neuron();

    //GETTERS
    double getMembranePotential() const;
    unsigned int getNbSpikes() const;
    vector<double> getSpikesTimes() const;
    vector<double> getAllMembranePotentials() const;
    bool isRefractory() const;

    //SETTER
    void setMembranePotential(double potential);
    void setNbSpikes(int nb);
    void incrementNbSpikes(unsigned int increment);
    void updateSpikesTimes(double time);
    void updateAllMembranePotentials(double potential);
    void setRefractory(bool state);

    //METHODS
    void updateMembranePotential(double current, double h, double tau, double resistance);
    void update(double t_start, double t_stop, double inf, double sup,
                double strenghtCurrent, double h, double tau, double resistance);


  private :
    double membrane_potential_;
    unsigned int nb_spikes_;
    vector<double> spikes_times_;
    bool refractory_;
    vector<double> allMembranePotentials_;
};


#endif
