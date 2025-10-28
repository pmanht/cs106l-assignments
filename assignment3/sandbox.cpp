/*
 * CS106L Assignment 3: Make a Class
 * Created by Fabio Ibanez with modifications by Jacob Roberts-Baca.
 */
#include "class.h"

void sandbox() {
  // STUDENT TODO: Construct an instance of your class!
  std::string src = "192.168.30.11";
  std::string dst = "192.168.30.22";
  std::string payload = "what is going on here?";
  
  NetworkPacket packet(src, dst, payload);
  packet.PrintInfo();
  packet.Execute();

  /* check double-free the payload if the 
     default copy constructor and assignment 
     operator do shallow copies.
  */
  // NetworkPacket packet1 = packet;
  // packet1.Execute();
}