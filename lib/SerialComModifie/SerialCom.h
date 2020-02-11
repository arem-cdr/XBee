#pragma once

/*--------------------TO DO--------------------------
Mettre sendData en public
Bug avec les fonctions templates
----------------------------------------------------*/




#include "mbed.h"
#include <iostream>
#include <vector>


class SerialCom // classe permettant de lire et écrire sur une liaison série
{
public :

    SerialCom();
    SerialCom(PinName rx, PinName tx);
    ~SerialCom();
    //bool buttonIsPressed(); // test et debug
    bool Traitement_DataReceived(); // à utiliser en permanance pour convertir les données reçus
    enum typeData{
      BOOL = 0, INT, FLOAT, DOUBLE, NONE
    };

private :
    //DigitalIn       *btn; // pour les tests et le debug
    Serial          *m_serial;
    Serial          *pc;
     

    char m_buffer_r[8] = {0}; //buffer received
    char m_buffer_s[10] = {0}; // buffer to send
    // dédié à traitement des data
    SerialCom::typeData type = NONE;
    bool reading = false;
    uint8_t c = 0;
    uint8_t cmax = 0;
    // stockage des données reçues
    vector<uint8_t> charWaiting;

    template <typename T> void sendData(T data, SerialCom::typeData TYPE); //fonction presque haut niveau qui envoie tout type de donnée

    template <typename T> void SerialCom::sendData(T data, SerialCom::typeData TYPE)
{
    Convert_Data_Into_Char(data, TYPE);
    for (int i = 0; i<10; i++)
    {
        m_serial->putc(m_buffer_s[i]);
        pc->printf("%d:", m_buffer_s[i]);
    }
    pc->printf("\n");
}

    void onCharReceived(); // recupère sur interruption série les charactères reçu

    template <typename T> void Convert_Data_Into_Char(T data, SerialCom::typeData TYPE ); // converti un type de data en un buffer de char

    template <typename T> void Convert_Data_Into_Value(char buffer[8], SerialCom::typeData type); // converti un buffer de char en data
  
    void cleanBuffer(char buffer[10]){ for(int i = 0; i<10;i++){ buffer[i] = '\0';}}

    
    

};