/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to mySignal.h
 */


#include "mySignal.h"

namespace wsn_energy {

mySignal::mySignal()
{
  this->incompleted = false;
  this->interferred = false;
  this->success = true;
}

mySignal::mySignal(int radioSenderID, int radioRecverID)
{
  mySignal();
  this->radioSenderID = radioSenderID;
  this->radioRecverID = radioRecverID;
}

void mySignal::setInterferred()
{
  this->interferred = true;
  this->success = false;
}

void mySignal::setIncompleted()
{
  this->incompleted = true;
  this->success = false;
}

bool mySignal::isInterferred()
{
  return this->interferred;
}

bool mySignal::isIncomplete()
{
  return this->incompleted;
}

bool mySignal::isSuccess()
{
  return this->success;
}

} /* namespace wsn_energy */
