#ifndef NEURON1_H
#define NEURON1_H

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

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
    vector<double> getAllMembranePotentials() const;
    bool isRefractory() const;

    //SETTER
    void setMembranePotential(double);
    void setNbSpikes(int);
    void incrementNbSpikes(int increment);
    void updateSpikesTimes(double time);
    void updateAllMembranePotentials(double potential);
    void setRefractory(bool state);

    //METHODS
    void updateMembranePotential(double current, double h, double tho, double resistance);
    void update(double t_start, double t_stop, double inf, double sup, 
                double strenghtCurrent, double h, double tho, double resistance);


  private :
    double membrane_potential_;
    double membrane_potential_threshold_;
    /*unsigned*/ int nb_spikes_;
    vector<double> spikes_times_;
    bool refractory_;
    vector<double> allMembranePotentials_;
};


#endif
