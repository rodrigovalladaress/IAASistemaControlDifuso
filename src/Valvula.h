#ifndef VALVULA_H_
#define VALVULA_H_

const float APERTURA_MAXIMA = 100;

class Valvula {
private:
  float porcentajeApertura;
  float maximaCirculacion; // Circulación del agua con apertura al 100%
public:
  Valvula(const float&, const float&); // Máxima circulación del agua y porcentaje apertura inicial
  Valvula(const float&); // Máxima circulación del agua, el porcentaje inicial por defecto es 100%
  float getFlujoSalida(void);
  inline const float& getPorcentajeApertura(void);
  inline const float& getMaximaCirculacion(void);
public:
  inline void setPorcentajeApertura(const float&);
private:
  inline void setMaximaCirculacion(const float&);
};

#endif