#include <QTRSensors.h>
#include "DRV8833.h"

#define NUM_SENSORS   6     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   3     // emitter is controlled by digital pin 2

QTRSensorsRC qtrrc((unsigned char[]) {
  A0, A1, A2, A3, A4, A5
}, NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];

DRV8833 motorDer(5, 6);
DRV8833 motorIzq(10, 9);

unsigned int centro = 2500;
int error = 0;
int Vmax = 50, V = 0;
long int proporcional = 0;
int integral = 0;
int derivativo = 0;
double kp = 0.025, kd = 0.035, ki = 0.0027;

int errorAnterior = 0;

void setup()
{
  Serial.begin(115200);

  /*for (int i=-255; i<=255; i++)
    {
    motorDer.Adelante(i);
    delay(50);
    }*/
  //  Serial.println("Iniciando...");
  //  for (int i = 0; i < 255; i++)
  //  {
  //    motorDer.Adelante(i);
  //    delay(50);
  //  }
  //
  //  for (int i = 0; i < 255; i++)
  //  {
  //    motorIzq.Adelante(i);
  //    delay(50);
  //  }
  //
  //  Serial.println("Prueba de motores finalizada");
  pinMode(13, OUTPUT);
  digitalWrite(13, HIGH);    // turn on Arduino's LED to indicate we are in calibration mode
  for (int i = 0; i < 200; i++)  // make the calibration take about 10 seconds
  {
    qtrrc.calibrate();       // reads all sensors 10 times at 2500 us per read (i.e. ~25 ms per call)
  }
  digitalWrite(13, LOW);     // turn off Arduino's LED to indicate we are through with calibration

  // print the calibration minimum values measured when emitters were on

  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMinimumOn[i]);
    Serial.print(' ');
  }
  Serial.println();

  // print the calibration maximum values measured when emitters were on
  for (int i = 0; i < NUM_SENSORS; i++)
  {
    Serial.print(qtrrc.calibratedMaximumOn[i]);
    Serial.print(' ');
  }
  Serial.println();
  Serial.println();
  delay(1000);
}

void loop()
{
  unsigned int position = qtrrc.readLine(sensorValues);

  // print the sensor values as numbers from 0 to 1000, where 0 means maximum reflectance and
  // 1000 means minimum reflectance, followed by the line position

//  for (unsigned char i = 0; i < NUM_SENSORS; i++)
//  {
//    Serial.print(sensorValues[i]);
//    Serial.print('\t');
//  }
//  //Serial.println(); // uncomment this line if you are using raw values
//  Serial.println(position); // comment this line out if you are using raw values

  error = position - centro;


  if (error <= -2000)
  {
    motorDer.Reversa(30);
    motorIzq.Adelante(60);
  }
  else if (error >= 2500)
  {
    motorDer.Adelante(60);
    motorIzq.Reversa(30);
  }
  else
  {
    proporcional = kp * error;
    integral = ki * (error + errorAnterior);
    derivativo = kd * (error - errorAnterior);

    V = proporcional + derivativo + integral;

    if (V > Vmax)
    {
      V = Vmax;
    }
    if (V < -Vmax)
    {
      V = -Vmax;
    }

    //Serial.println((String)V);
    
    errorAnterior = error;
    motorDer.Adelante(Vmax + V);
    motorIzq.Adelante(Vmax - V);
  }

}
