// C++ code
#include <Servo.h>

// Servo
Servo servo1;
int PinServo = 10;
int PulsoMin = 1000;
int PulsoMax = 2000;

// Ultrasonido
int PinTrig = 12;
int PinEcho = 11;

long tiempoDemora = 0;
int distanciaCM = 0;

// Fotoresistencia
int PinFoto = A0;
int LightThreshold = 10;
int Luz = 0;

void setup()
{
	// Setea la consola
    Serial.begin(9600);
    Serial.println("ENCENDIDO");

    // Setea el Servo
    servo1.attach(PinServo, PulsoMin, PulsoMax);

    // Setea el Ultrasonido
    pinMode(PinTrig, OUTPUT);
    pinMode(PinEcho, INPUT);
    digitalWrite(PinTrig, LOW);

	// Lo inicializa en el ángulo 0
    servo1.write(0);
}

void loop()
{
	//Serial.println("");

	// Le indica al Ultrasonido a lanzar una señal por 1 microsegundo y luego detenerse
    digitalWrite(PinTrig, HIGH);
    delayMicroseconds(1);
    digitalWrite(PinTrig, LOW);

	// Lee los valores del Ultrasonido
    tiempoDemora = pulseIn(PinEcho, HIGH);
	// Calcula la distancia considerando la Velocidad del Sonido Promedio en el Aire
    distanciaCM = (int)(tiempoDemora / 59);

    // Lee la señal de la Fotoresistencia
    Luz = analogRead(PinFoto);

	
    //Serial.println("Luz:");
    //Serial.println(Luz);
  	//Serial.println("Tiempo:");
    //Serial.println(tiempoDemora);
    //Serial.println("Dist:");
    //Serial.println(distanciaCM);
	

    // Las condiciones para girar
    if ((distanciaCM >= 80) && (Luz > LightThreshold))
    {
        //Serial.println("1ra");

        servo1.write(180);
        delay(500);

    }

    else if ((distanciaCM <= 30) && (Luz < LightThreshold))
    {
        //Serial.println("2da");
        
      	servo1.write(60);
      	delay(500);
    }

    else if ((distanciaCM == 2) && (Luz == 0))
    {
        //Serial.println("3ra");
      	servo1.write(0);
     	delay(500);
    }

    else
    {
		//Serial.println("None");
    }

    delay(100);
}