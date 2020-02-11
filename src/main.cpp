#include "main.h"

#define SERIALTX A0
#define SERIALRX A1

void receive();

// init
Serial * pc = new Serial(USBTX, USBRX,9600);
Serial * xbee = new Serial(SERIALTX, SERIALRX, 9600);

vector<char> * buffer = new vector<char>();
vector<char> * message = new vector<char>();

void receive()
{
  /*
   * Fonction attachee sur l'interruption de la liaison serie dans le sens de la reception
  */

  buffer->push_back(xbee->getc());
  if(buffer->back() == '\n')
  {
    message = buffer;
    buffer = new vector<char>();
  }
}

void test_XBee()
{
  /*
   * A mettre dans le main et commenter ou supprimer tout ce que contient le main pour tester les xbee en mode transparent
  */

  Timer t;
  t.start();

  xbee->attach(&receive);

  pc->printf("Start!\n");

  double sample_time = 0.1;
  double last_read_time = 0.0;

  while(1)
  {
    double time = t.read();
    if(time - last_read_time > sample_time)
    {
      last_read_time = time;

      xbee->printf("MAYDAY!!\n");

      if(message->size() > 0)
      {
        pc->printf("> ");
        for(vector<char>::iterator it = message->begin(); it != message->end(); it++)
        {
            pc->printf("%c", *it);
        }
        pc->printf("\n");
        pc->printf("\n");
        buffer = new vector<char>();
      }
    }
  }

}
 
int main()
{
  

  while(1)
  {

  }
}