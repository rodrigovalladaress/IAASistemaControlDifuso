#include "Valvula.h"
Valvula::Valvula(const float& maximaCirculacion, const float& porcentajeApertura) {
  setMaximaCirculacion(maximaCirculacion);
  setPorcentajeApertura(porcentajeApertura);
}

Valvula::Valvula(const float& maximaCirculacion) {
  setMaximaCirculacion(maximaCirculacion);
  setPorcentajeApertura(APERTURA_MAXIMA);
}

float Valvula::getFlujoSalida(void) {
  return getMaximaCirculacion() * (getPorcentajeApertura() / 100.0);
}

const float& Valvula::getPorcentajeApertura(void) {
  return porcentajeApertura;
}

const float& Valvula::getMaximaCirculacion(void) {
  return maximaCirculacion;
}

void Valvula::setPorcentajeApertura(const float& porcentajeApertura_) {
  porcentajeApertura = porcentajeApertura_;
}

void Valvula::setMaximaCirculacion(const float& maximaCirculacion_) {
  maximaCirculacion = maximaCirculacion_;
}