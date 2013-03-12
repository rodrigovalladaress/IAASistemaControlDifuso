#ifndef SISTEMACONTROLDIFUSO_H_
#define SISTEMACONTROLDIFUSO_H_

#include "Valvula.cc"
#include <iostream>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>

const char* NOMBRE_FICHERO_SALIDA = "out.csv";

const float AP_MENOR_VALOR = -15.0;
const float AP_MAYOR_VALOR = 100.0;
/* Cada cuantos puntos se calcula el centroide */
const float STEP_CENTROIDE = 1.0;

using std::cout;
using std::endl;
using std::min;
using std::max;
using std::ofstream;
using std::ostringstream;
using std::string;

class SistemaControlDifuso {
private:
  Valvula* valvulaEntrada;
  Valvula* valvulaSalida;
  float alturaAguaDeposito;
  float alturaAguaDeseada;
public:
  void prueba(void);
  /* Altura agua depósito, Altura agua deseada, máxima circulación entrada, 
   * porcentaje inicial de apertura de entrada, máxima circulación salida */
  SistemaControlDifuso(const float&, const float&, const float&, const float&, const float&);
  /* Altura agua depósito, Altura agua deseada, Máxima circulación entrada, 
   * máxima circulación salida */
  SistemaControlDifuso(const float&, const float&, const float&, const float&);
  ~SistemaControlDifuso(void);
  /* Control del sistema */
  void controlarSistema(int); //Como argumento se pasa el número de horas
private:
  inline void actualizar(void);
  /* Calcular centroide */
  float centroide(void);
  inline float error(void);
  /* Grados de verdad */
  float gradoVerdadErrorNegativo(void);
  float gradoVerdadErrorCero(void);
  float gradoVerdadErrorPositivo(void);
  float gradoVerdadAperturaAbrir(const float&);
  float gradoVerdadAperturaCerrar(const float&);
  inline void setPorcentajeAperturaEntrada(const float&);
  inline void setAlturaAguaDeposito(const float&);
  inline void setAlturaAguaDeseada(const float&);
  inline const float& getAlturaAguaDeposito(void);
  inline const float& getAlturaAguaDeseada(void);
  inline const float& getPorcentajeAperturaEntrada(void);
  inline float getFlujoEntrada(void);
  inline float getFlujoSalida(void);
};

#endif