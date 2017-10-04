#include "neuron1.h"
//#include "Constants.hpp"
#include <fstream>
#include <sstream>

int main() {
  Neuron neuron;

  /*When time will be between inf and sup, the current I will be equal to the
  external current, otherwise it will be 0.
  inf and sup must be between t_start and t_stop*/
  double inf(20);
  double sup(50);
  if ((inf < T_START) or (sup > T_STOP) or (inf > sup)) {
    cerr << "Incorrect values of inf/sup" << endl;
    return 0;
  }

  neuron.update(T_START, T_STOP, inf, sup, EXT_CURRENT, H, TAU, RESISTANCE);

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
