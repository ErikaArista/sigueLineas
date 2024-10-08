#ifndef DRV8833_H
#define DRV8833_H

#include "Arduino.h"

class DRV8833
{
public:
	DRV8833(int a1, int a2);

	void Reversa();
	void Reversa(int velocidad);
	void Adelante();
	void Adelante(int velocidad);
	void Detener();

private:
	int a1, a2;
	boolean motorConfigurado = false;
};

#endif
