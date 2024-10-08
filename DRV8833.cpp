#include "Arduino.h"
#include "DRV8833.h"

DRV8833::DRV8833(int a1, int a2)
{
  pinMode(a1, OUTPUT);
  pinMode(a2, OUTPUT);
  this->a1 = a1;
  this->a2 = a2;
  this->motorConfigurado = true;
}

void DRV8833::Reversa()
{
  if (this->motorConfigurado)
  {
    digitalWrite(this->a1, LOW);
    digitalWrite(this->a2, HIGH);
  }
}

void DRV8833::Reversa(int velocidad)
{
  if (this->motorConfigurado)
  {
    analogWrite(this->a1, LOW);
    digitalWrite(this->a2, velocidad);
  }
}

void DRV8833::Adelante()
{
  if (this->motorConfigurado)
  {
    digitalWrite(this->a1, HIGH);
    digitalWrite(this->a2, LOW);
  }
}

void DRV8833::Adelante(int velocidad)
{
  if (this->motorConfigurado)
  {
    analogWrite(this->a1, velocidad);
    digitalWrite(this->a2, LOW);
  }
}

void DRV8833::Detener()
{
  if (this->motorConfigurado)
  {
    digitalWrite(this->a1, HIGH);
    digitalWrite(this->a2, HIGH);
  }
}
