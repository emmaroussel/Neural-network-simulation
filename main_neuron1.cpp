#include "neuron1.h"
#include <fstream>
#include <sstream>

int main() {
  Neuron neuron(0.0, 0.1);
  double external_current(200); //200pA
  double time_interval(20); //correspond to tho
  double h(1);
  double R(10); //for resistance

  double t_start(0);
  double t_stop(500);

  /*when time will be between inf and sup, the current I will be equal to
  extrenal current, otherwise it will be 0.
  inf and sup must be between t_start and t_stop*/
  double inf(20);
  double sup(40);
  neuron.update(t_start, t_stop, inf, sup, external_current, h, time_interval, R);
    
    ofstream out;
    out.open("membrane_potential_values.txt");
    out.clear();
    if (out.fail()) {
        cerr << "Erreur lecture fichier" << endl;
    } else {
        vector<double> potential_values(neuron.getAllMembranePotentials());
        ostringstream texte;
        
        for (unsigned int i(0); i < potential_values.size(); ++i) {
            texte << potential_values[i] << endl;
        }
        
     string potentialAsString = texte.str(); //str() transforms the stream's content into string
     out << potentialAsString << endl;
     out.close();
    }
    
  return 0;
}
