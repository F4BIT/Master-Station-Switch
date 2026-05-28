// Arduino Nano TRX Mic and CW Switch V0.1
// LCD 16x2 
// Stéphane F4BIT/N4BIT
// stephane@mangeolle.fr
// Copyleft@2025 for Hamradio
/*
=========================================================
 ARDUINO NANO + NEXTION + 2 CARTES 8 RELAIS
=========================================================

CONFIGURATION NEXTION
Pour la SSB
BOUTON 1 -> RELAIS 1 à 8 IC7300
BOUTON 2 -> RELAIS 1 à 8 IC9700
Pour la CW
BOUTON 3 -> RELAIS 9 à 12 IC7300
BOUTON 4 -> RELAIS 9 à 12 IC9700

=========================================================
 RELAIS
=========================================================

Relais 1  -> D2
Relais 2  -> D3
Relais 3  -> D4
Relais 4  -> D5
Relais 5  -> D6
Relais 6  -> D7
Relais 7  -> D8
Relais 8  -> D9

Relais 9  -> D12
Relais 10 -> D13
Relais 11 -> A0
Relais 12 -> A1

=========================================================
 NEXTION
=========================================================

TX -> D10
RX -> D11

=========================================================
*/

#include <SoftwareSerial.h>

SoftwareSerial nextion(10, 11);

//--------------------------------------------------
// RELAIS 1 A 8
//--------------------------------------------------

const int relais1_8[] =
{
  2,3,4,5,6,7,8,9
};

//--------------------------------------------------
// RELAIS 9 A 12
//--------------------------------------------------

const int relais9  = 12;
const int relais10 = 13;
const int relais11 = A0;
const int relais12 = A1;

//==================================================
// SETUP
//==================================================

void setup()
{
    Serial.begin(9600);

    nextion.begin(9600);

    //----------------------------------------------
    // RELAIS 1 A 8
    //----------------------------------------------

    for(int i = 0; i < 8; i++)
    {
        pinMode(relais1_8[i], OUTPUT);

        // RELAIS OFF AU DEMARRAGE
        digitalWrite(relais1_8[i], HIGH);
    }

    //----------------------------------------------
    // RELAIS 9 A 12
    //----------------------------------------------

    pinMode(relais9, OUTPUT);
    pinMode(relais10, OUTPUT);
    pinMode(relais11, OUTPUT);
    pinMode(relais12, OUTPUT);

    digitalWrite(relais9, HIGH);
    digitalWrite(relais10, HIGH);
    digitalWrite(relais11, HIGH);
    digitalWrite(relais12, HIGH);

    Serial.println("SYSTEME DEMARRE");
}

//==================================================
// LOOP
//==================================================

void loop()
{
    lireNextion();
}

//==================================================
// LECTURE NEXTION
//==================================================

void lireNextion()
{
    while(nextion.available())
    {
        char c = nextion.read();

        //------------------------------------------
        // BOUTON 1
        // RELAIS 1 A 8 ON
        //------------------------------------------

        if(c == '1')
        {
            relais1_8_ON();
        }

        //------------------------------------------
        // BOUTON 2
        // RELAIS 1 A 8 OFF
        //------------------------------------------

        if(c == '2')
        {
            relais1_8_OFF();
        }

        //------------------------------------------
        // BOUTON 3
        // RELAIS 9 A 12 ON
        //------------------------------------------

        if(c == '3')
        {
            relais9_12_ON();
        }

        //------------------------------------------
        // BOUTON 4
        // RELAIS 9 A 12 OFF
        //------------------------------------------

        if(c == '4')
        {
            relais9_12_OFF();
        }
    }
}

//==================================================
// RELAIS 1 A 8 ON
//==================================================

void relais1_8_ON()
{
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(relais1_8[i], LOW);
    }

    Serial.println("RELAIS 1 A 8 ON");

    boutonVert("b0");
    boutonRouge("b1");
}

//==================================================
// RELAIS 1 A 8 OFF
//==================================================

void relais1_8_OFF()
{
    for(int i = 0; i < 8; i++)
    {
        digitalWrite(relais1_8[i], HIGH);
    }

    Serial.println("RELAIS 1 A 8 OFF");

    boutonRouge("b0");
    boutonVert("b1");
}

//==================================================
// RELAIS 9 A 12 ON
//==================================================

void relais9_12_ON()
{
    digitalWrite(relais9, LOW);
    digitalWrite(relais10, LOW);
    digitalWrite(relais11, LOW);
    digitalWrite(relais12, LOW);

    Serial.println("RELAIS 9 A 12 ON");

    boutonVert("b2");
    boutonRouge("b3");
}

//==================================================
// RELAIS 9 A 12 OFF
//==================================================

void relais9_12_OFF()
{
    digitalWrite(relais9, HIGH);
    digitalWrite(relais10, HIGH);
    digitalWrite(relais11, HIGH);
    digitalWrite(relais12, HIGH);

    Serial.println("RELAIS 9 A 12 OFF");

    boutonRouge("b2");
    boutonVert("b3");
}

//==================================================
// BOUTON VERT
//==================================================

void boutonVert(String bouton)
{
    nextion.print(bouton + ".bco=2016");

    nextion.write(0xFF);
    nextion.write(0xFF);
    nextion.write(0xFF);
}

//==================================================
// BOUTON ROUGE
//==================================================

void boutonRouge(String bouton)
{
    nextion.print(bouton + ".bco=63488");

    nextion.write(0xFF);
    nextion.write(0xFF);
    nextion.write(0xFF);
}
