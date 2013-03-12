#include "src/SistemaControlDifuso.cc"
int main() {
  SistemaControlDifuso objeto(19, 20, 0.4, 0.1);
  objeto.controlarSistema(5);
}