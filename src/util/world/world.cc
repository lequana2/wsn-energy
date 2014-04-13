/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to world.h
 */

#include "world.h"
#include "radio.h"

#include <math.h>

#ifndef ANNOTATE
#define ANNOTATE 1
#endif

#ifndef DEBUG
#define DEBUG 1
#endif

namespace wsn_energy {

Define_Module(World);

void World::initialize()
{
  this->numberClient = getParentModule()->par("numberClient").doubleValue();

  /* Arrange nodes into positions */
  arrangeMotes();

  /* Create connections */
  connectNodes();
}

void World::finish()
{
  this->oss.clear();
  for (std::list<Host*>::iterator it = this->hosts.begin(); it != this->hosts.end(); it++)
  {
    (*it)->moteIDWithinTransmissionRange.clear();
    (*it)->moteIDWithinCollisionRange.clear();
  }
  this->hosts.clear();
  this->signals.clear();
}

/*
 * Arrange position of nodes in network.
 */
void World::arrangeMotes()
{
  int col = -1; // carry out
  int row = 0;
  int step = 0;
  int x, y;

  for (int i = 0; i < numberClient; i++)
  {
    switch ((int) getParentModule()->par("topology").doubleValue())
    {
      case 0: /* grid */
      {
        if (col > 10)
        {
          row++;
          col = 0;
        }
        else
          col++;

        // Partition
        x = col * 25 + 15;
        y = row * 25 + 5;

        // Randomize
        x = uniform(x - 5, x + 5);
        y = uniform(y - 5, y + 5);
        break;
      }/* grid */

      case 1: /* pyramid */
      {
        if (col >= step)
        {
          col = 0;
          row++;
          step++;
        }
        else
        {
          col++;
        }
        // Partition
        x = (int) (col * 40 + (getParentModule()->par("width").doubleValue() - 40 * step) / 2);
        y = (int) (row * 40 + 17);
        break;
      }/* pyramid */

      case 2:/* Line */
      {
        step++;
        x = 150;
        y = step*30 + 150;
        break;
      } /* Line */
    }

    char modulePath[20];
    sprintf(modulePath, "client[%d]", i);
    cModule *mote = getParentModule()->getModuleByPath(modulePath);

    mote->par("axisX").setDoubleValue(x);
    mote->par("axisY").setDoubleValue(y);

    oss.seekp(0);
    oss << x << endl;
    (&mote->getDisplayString())->setTagArg("p", 0, oss.str().c_str());

    oss.seekp(0);
    oss << y << endl;
    (&mote->getDisplayString())->setTagArg("p", 1, oss.str().c_str());
  }
}

/*
 * Create connection accords to every node
 */
void World::connectNodes()
{
  // Connect server to other(s)
  RadioDriver *server = (RadioDriver*) simulation.getModuleByPath("server.radio");
  this->deployConnection(server);

  // Connect client(s) to other(s)
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d].radio", i);
    this->deployConnection((RadioDriver*) simulation.getModuleByPath(modulePath));
  }
}

/*
 * deploy all valid connection for a given radio
 */
void World::deployConnection(RadioDriver* mote)
{
  Host *host = new Host;
  host->moteID = mote->getId();

  // Check with base station
  RadioDriver *bs = (RadioDriver*) simulation.getModuleByPath("server.radio");
  switch (this->validateConnection(mote, bs))
  {
    case WITHIN_TRANS:
      host->moteIDWithinTransmissionRange.push_front(bs->getId());
      break;

    case WITHIN_COLLI:
      host->moteIDWithinCollisionRange.push_front(bs->getId());
      break;

    case NO_CONNECTION:
      break;
  }

  // Check with other mote
  for (int i = 0; i < numberClient; i++)
  {
    char modulePath[20];
    sprintf(modulePath, "client[%d].radio", i);
    RadioDriver *otherMote = (RadioDriver*) simulation.getModuleByPath(modulePath);

    if (mote->getId() == otherMote->getId())
      continue;

    switch (this->validateConnection(mote, otherMote))
    {
      case WITHIN_TRANS:
        host->moteIDWithinTransmissionRange.push_front(otherMote->getId());
        break;

      case WITHIN_COLLI:
        host->moteIDWithinCollisionRange.push_front(otherMote->getId());
        break;

      case NO_CONNECTION:
        break;
    }
  }

  this->hosts.push_back(host);
}

/*
 * check validation between 2 radio
 */
int World::validateConnection(RadioDriver* host, RadioDriver* client)
{
  int distance = calculateDistance(host, client);

  if (distance > host->coRange || host->getId() == client->getId())
    return NO_CONNECTION;

  if (distance > host->trRange)
    return WITHIN_COLLI;

  // set up connection
  char setOutConnectionName[20];
  char setInConnectionName[20];

  cGate *outGate;
  cGate *inGate;

  sprintf(setOutConnectionName, "out %d to %d", host->getParentModule()->getId(), client->getParentModule()->getId());
  sprintf(setInConnectionName, "in %d to %d", host->getParentModule()->getId(), client->getParentModule()->getId());

  outGate = host->getParentModule()->addGate(setOutConnectionName, cGate::OUTPUT);
  inGate = client->getParentModule()->addGate(setInConnectionName, cGate::INPUT);

  outGate->connectTo(inGate);

  //hidden connection
  outGate->setDisplayString("ls=,0");

  return WITHIN_TRANS;
}

/*
 * register transmitting mote
 */
void World::registerHost(RadioDriver* mote, Raw* onAir)
{
  if (DEBUG)
    ev << "Register host " << mote->getId() << endl;

  // Search host by id
  int senderID = mote->getId();
  Host *host;

  for (std::list<Host*>::iterator it = this->hosts.begin(); it != this->hosts.end(); it++)
  {
    if ((*it)->moteID == senderID)
      host = *it;
  }

  if (host == NULL)
  {
    if (DEBUG)
      ev << "Unknown host" << endl;
    return;
  }

  host->onAir = onAir->dup();

  // create all in-transmission-range signal
  for (std::list<int>::iterator it = host->moteIDWithinTransmissionRange.begin();
      it != host->moteIDWithinTransmissionRange.end(); it++)
  {
    mySignal *signal = new mySignal(senderID, (*it));
    considerSignal(signal);

    // insert into signal manager list
    this->signals.push_front(signal);
  }

  // consider all only-in-collision-range signal
  for (std::list<int>::iterator it = host->moteIDWithinCollisionRange.begin();
      it != host->moteIDWithinCollisionRange.end(); it++)
  {
    // only increase incoming signal
    mySignal *signal = new mySignal(senderID, (*it));
    considerSignal(signal);
  }
}

/*
 * unregister transmitting mote
 */
void World::releaseHost(RadioDriver* mote)
{
  // Search host by id
  int senderID = mote->getId();
  Host *host;

  for (std::list<Host*>::iterator it = this->hosts.begin(); it != this->hosts.end(); it++)
  {
    if ((*it)->moteID == senderID)
      host = *it;
  }

  if (host == NULL)
  {
    if (DEBUG)
      ev << "Unknown host" << endl;
    return;
  }

  // release this host signal
  for (std::list<mySignal*>::iterator it = signals.begin(); it != signals.end(); it++)
    if ((*it)->radioSenderID == senderID)
    {
      // check success
      Raw* raw = host->onAir->dup();
      if ((*it)->isSuccess())
        raw->setBitError(false); // no error
      else
        raw->setBitError(true);  // error
      // send message
      (check_and_cast<RadioDriver*>(simulation.getModule(senderID)))->sendDirect(raw,
      simulation.getModule((*it)->radioRecverID)->gate("radioIn"));

      // remove signal
      signals.remove((*it--));
    }
  delete host->onAir;

  // decrease count of in-transmission-range signal
  for (std::list<int>::iterator it = host->moteIDWithinTransmissionRange.begin();
      it != host->moteIDWithinTransmissionRange.end(); it++)
    check_and_cast<RadioDriver*>(simulation.getModule(*it))->incomingSignal--;

  // decrease count of only-in-collision-range signal
  for (std::list<int>::iterator it = host->moteIDWithinCollisionRange.begin();
      it != host->moteIDWithinCollisionRange.end(); it++)
    check_and_cast<RadioDriver*>(simulation.getModule(*it))->incomingSignal--;
}

/*
 * a mote stop listening
 */
void World::stopListening(RadioDriver* mote)
{
  // Receiver ID
  int recverID = mote->getId();

  // consider incomplete signal
  for (std::list<mySignal*>::iterator it = signals.begin(); it != signals.end(); it++)
    if ((*it)->radioRecverID == recverID)
      (*it)->setIncompleted();
}

/*
 * a mote sudden listens
 */
void World::suddenListening(RadioDriver *mote)
{
// WSN consider all incoming message to note incomplete
}

/*
 * register on-air signal
 */
void World::considerSignal(mySignal* signal)
{
  // Receiver ID
  int recverID = signal->radioRecverID;

  // increase incoming signal
  (check_and_cast<RadioDriver*>(simulation.getModule(recverID)))->incomingSignal++;

  // Incomplete message
  if ((check_and_cast<RadioDriver*>(simulation.getModule(recverID)))->status != LISTENING)
    signal->setIncompleted();

  // consider interfere signal at receiver
  if ((check_and_cast<RadioDriver*>(simulation.getModule(recverID)))->incomingSignal > 1)
  {
    // from this host signal
    signal->setInterferred();

    // from other host signal
    for (std::list<mySignal*>::iterator it = signals.begin(); it != signals.end(); it++)
      if ((*it)->radioRecverID == recverID)
        (*it)->setInterferred();
  }
}

/*
 * Calculate distance util
 */
double World::calculateDistance(RadioDriver *a, RadioDriver *b)
{
  int x1 = a->getParentModule()->par("axisX");
  int y1 = a->getParentModule()->par("axisY");
  int x2 = b->getParentModule()->par("axisX");
  int y2 = b->getParentModule()->par("axisY");

  return this->calculateDistance(x1, y1, x2, y2);
}

/*
 * Calculate distance util
 */
double World::calculateDistance(int x1, int y1, int x2, int y2)
{
  int x = (x1 - x2) * (x1 - x2);
  int y = (y1 - y2) * (y1 - y2);
  return sqrt(x + y);
}

} /* namespace wsn_energy */
