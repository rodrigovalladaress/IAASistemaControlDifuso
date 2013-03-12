#include "SistemaControlDifuso.h"

void SistemaControlDifuso::prueba(void) {
  cout << "Error = " << error() << endl;
  cout << "Error negativo = " << gradoVerdadErrorNegativo() << endl;
  cout << "Error cero = " << gradoVerdadErrorCero() << endl;
  cout << "Error positivo = " << gradoVerdadErrorPositivo() << endl;
  cout << "Centroide = " << centroide() << endl;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                 Constructores //
///////////////////////////////////////////////////////////////////////////////////////////////////

SistemaControlDifuso::SistemaControlDifuso(const float& alturaInicial,
					   const float& alturaAguaDeseada,
                                           const float& maximaCirculacionEntrada,
					   const float& porcentajeAperturaEntrada,
					   const float& maximaCirculacionSalida) {
  valvulaEntrada = new Valvula(maximaCirculacionEntrada, porcentajeAperturaEntrada);
  valvulaSalida = new Valvula(maximaCirculacionSalida);
  setAlturaAguaDeposito(alturaInicial);
  setAlturaAguaDeseada(alturaAguaDeseada);
}

SistemaControlDifuso::SistemaControlDifuso(const float& alturaInicial,
					   const float& alturaAguaDeseada,
                                           const float& maximaCirculacionEntrada,
					   const float& maximaCirculacionSalida) {
  valvulaEntrada = new Valvula(maximaCirculacionEntrada);
  valvulaSalida = new Valvula(maximaCirculacionSalida);
  setAlturaAguaDeposito(alturaInicial);
  setAlturaAguaDeseada(alturaAguaDeseada);
}

SistemaControlDifuso::~SistemaControlDifuso(void) {
  delete valvulaEntrada;
  delete valvulaSalida;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                           Control del sistema //
///////////////////////////////////////////////////////////////////////////////////////////////////

void SistemaControlDifuso::controlarSistema(int horas) {
  int numeroMinutos = horas * 60;
  ofstream ficheroSalida(NOMBRE_FICHERO_SALIDA);
  if(!ficheroSalida.fail()) {
    ficheroSalida << "Minuto;Altura;Porcentaje_Apertura;Error" << endl;
    for(int i = 0; i <= numeroMinutos; i++) {
      ficheroSalida << i << ";" << getAlturaAguaDeposito() << ";";
      ficheroSalida << getPorcentajeAperturaEntrada() << ";" << error() << endl;
      setPorcentajeAperturaEntrada(centroide());
      actualizar();      
    }
  }
  else {
    cout << "Error al escribir en fichero de salida." << endl;
  }
}

void SistemaControlDifuso::actualizar(void) {
  setAlturaAguaDeposito(getAlturaAguaDeposito() + getFlujoEntrada() - getFlujoSalida());
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                                     Centroide //
///////////////////////////////////////////////////////////////////////////////////////////////////

float SistemaControlDifuso::centroide(void) {
  float numeradorCentroide = 0;
  float denominadorCentroide = 0;
  float aux;
  float errorNegativo = gradoVerdadErrorNegativo();
  float errorCero = gradoVerdadErrorCero();
  float errorPositivo = gradoVerdadErrorPositivo();
  for(float i = AP_MENOR_VALOR; i <= AP_MAYOR_VALOR; i += STEP_CENTROIDE) {
    aux = min(errorNegativo, gradoVerdadAperturaCerrar(i));
    aux = max(aux, min(errorCero, gradoVerdadAperturaCerrar(i)));
    aux = max(aux, min(errorPositivo, gradoVerdadAperturaAbrir(i)));
    numeradorCentroide += (i * aux);
    denominadorCentroide += aux;
  }
  return numeradorCentroide / denominadorCentroide;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                              Grados de verdad //
///////////////////////////////////////////////////////////////////////////////////////////////////

float SistemaControlDifuso::error(void) {
  return getAlturaAguaDeseada() - getAlturaAguaDeposito();
}

float SistemaControlDifuso::gradoVerdadErrorNegativo(void) {
  float x = error();
  if((-15 <= x) && (x <= -10))
    return 1;
  else if((-10 < x) && (x < 0))
    return -x / 10.0;
  else
    return 0;
}

float SistemaControlDifuso::gradoVerdadErrorCero(void) {
  float x = error();
  if((-5 < x) && (x <= 0))
    return (5.0 + x) / 5.0;
  else if((0 < x) && (x < 5))
    return (5.0 - x) / 5.0;
  else
    return 0;
}

float SistemaControlDifuso::gradoVerdadErrorPositivo(void) {
  float x = error();
  if((0 < x) && (x < 10))
    return x / 10.0;
  if((10 <= x) && (x <= 15))
    return 1;
  else
    return 0;
}

float SistemaControlDifuso::gradoVerdadAperturaAbrir(const float& x) {
  if((0 < x) && (x < 50))
    return x / 50.0;
  else if(50 <= x)
    return 1;
  else
    return 0;
}

float SistemaControlDifuso::gradoVerdadAperturaCerrar(const float& x) {
  if((-25 < x) && (x <= 0))
    return (25.0 + x) / 25.0;
  else if((0 <= x) && (x < 25))
    return (25.0 - x) / 25.0;
  return 0;
}

///////////////////////////////////////////////////////////////////////////////////////////////////
//                                                                               Setter y getter //
///////////////////////////////////////////////////////////////////////////////////////////////////

void SistemaControlDifuso::setPorcentajeAperturaEntrada(const float& porcentajeAperturaEntrada) {
  valvulaEntrada->setPorcentajeApertura(porcentajeAperturaEntrada);
}

void SistemaControlDifuso::setAlturaAguaDeposito(const float& alturaAguaDeposito_) {
  alturaAguaDeposito = alturaAguaDeposito_;
}

void SistemaControlDifuso::setAlturaAguaDeseada(const float& alturaAguaDeseada_) {
  alturaAguaDeseada = alturaAguaDeseada_;
}

const float& SistemaControlDifuso::getAlturaAguaDeposito(void) {
  return alturaAguaDeposito;
}

const float& SistemaControlDifuso::getAlturaAguaDeseada(void) {
  return alturaAguaDeseada;
}

const float& SistemaControlDifuso::getPorcentajeAperturaEntrada(void) {
  return valvulaEntrada->getPorcentajeApertura();
}

float SistemaControlDifuso::getFlujoEntrada(void) {
  return valvulaEntrada->getFlujoSalida();
}

float SistemaControlDifuso::getFlujoSalida(void) {
  return valvulaSalida->getFlujoSalida();
}