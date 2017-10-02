#include <neuron1.h>

int main() {
  Neuron neuron;
  double external_current(200); //200pA
  double time_interval(1000); //1000ms, correspond to tho
  double h(0.1);
  double R(1); //pour résistance
  update.neuron(0, 5000, external_current, h, time_interval, R);
  //t_start = 0, t_end = 5000ms


  return 0;
}
