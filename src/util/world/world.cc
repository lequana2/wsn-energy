/*
 *  created on : Mar 5, 2014
 *      author : Mr.Quan LE
 *      email  : lequana2@gmail.com
 *
 *  functioning: refer to world.h
 */

#include <math.h>
#include <statistic.h>
#include <world.h>
#include <cstdio>
#include <list>
#include <sstream>
#include <string>

#ifndef ANNOTATE
#define ANNOTATE 0
#endif

#ifndef DEBUG
#define DEBUG 0
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
  for (std::list<Mote*>::iterator it = this->hosts.begin(); it != this->hosts.end(); it++)
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

        // Partition, 1 cell = 50*50
        x = col * 35 + 15;
        y = row * 35 + 15;

        // Randomize
        x = intuniform(x - 5, x + 5);
        y = intuniform(y - 5, y + 5);
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
        x = 240;
        y = 30 * step;
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
  Mote *host = new Mote;
  host->moteID = mote->getId();

  // Check with base station
  RadioDriver *bs = (RadioDriver*) simulation.getModuleByPath("server.radio");
  switch (this->validateConnection(mote, bs))
  {
    case WITHIN_TRANS:
      host->moteIDWithinTransmissionRange.push_front(bs->getId());
      host->moteIDWithinCollisionRange.push_front(bs->getId());
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

    switch (this->validateConnection(mote, otherMote))
    {
      case WITHIN_TRANS:
        // bytecount: calculate number of server neighbor
        if (getModuleByPath("^")->par("isPollingCount").boolValue())
        {
          if (mote->getParentModule()->getId() == simulation.getModuleByPath("server")->getId())
            check_and_cast<Statistic*>(simulation.getModuleByPath("statistic"))->registerStatistic(
            LIFE_TIME_INCREASE_SERVER_NEIGHBOR);
        }

        host->moteIDWithinTransmissionRange.push_front(otherMote->getId());
        host->moteIDWithinCollisionRange.push_front(otherMote->getId());
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
  if (host->getId() == client->getId())
    return NO_CONNECTION;

  int distance = calculateDistance(host, client);

  if (distance > host->coRange)
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
  Mote *host = NULL;

  for (std::list<Mote*>::iterator it = this->hosts.begin(); it != this->hosts.end(); it++)
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

  // checking point
  host->onAir = onAir->dup();

  // create all in-transmission-range signal
  for (std::list<int>::iterator it = host->moteIDWithinTransmissionRange.begin();
      it != host->moteIDWithinTransmissionRange.end(); it++)
  {
    // create signal
    mySignal *signal = new mySignal(senderID, (*it));

    // insert into signal manager list
    this->signals.push_front(signal);

    // consider validation of signal
    considerSignal(signal);
  }

  // consider all only-in-collision-range signal
  for (std::list<int>::iterator it = host->moteIDWithinCollisionRange.begin();
      it != host->moteIDWithinCollisionRange.end(); it++)
  // increase incoming signal
  {
    check_and_cast<RadioDriver*>(simulation.getModule(*it))->incomingSignal++;
    check_and_cast<RadioDriver*>(simulation.getModule(*it))->ccaIsFreeChannel = false;
  }

  // draw range
  if (ANNOTATE)
  {
    oss.seekp(0);
    oss << mote->trRange << endl;
    (&mote->getParentModule()->getDisplayString())->setTagArg("r", 0, oss.str().c_str());
  }
}

/*
 * unregister transmitting mote
 */
void World::releaseHost(RadioDriver* mote)
{
  // Search host by id
  int senderID = mote->getId();
  Mote* host = NULL;

  for (std::list<Mote*>::iterator it = this->hosts.begin(); it != this->hosts.end(); it++)
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
  {
    if ((*it)->radioSenderID == senderID)
    {
      // check success
      Raw* raw = host->onAir->dup();
      if ((*it)->getIsCorrupted())
        raw->setBitError(true); // no error
      else
        raw->setBitError(false);  // error

      // send message
      (check_and_cast<RadioDriver*>(simulation.getModule(senderID)))->sendDirect(raw,
      simulation.getModule((*it)->radioRecverID)->gate("radioIn"));

      // remove signal
      signals.remove((*it--));
    }
  }

  // clear buffer
  if (host->onAir != NULL)
  {
    delete host->onAir;
    host->onAir = NULL;
  }

// decrease count of only-in-collision-range signal
  for (std::list<int>::iterator it = host->moteIDWithinCollisionRange.begin();
      it != host->moteIDWithinCollisionRange.end(); it++)
  {
// consider host incoming signal
    check_and_cast<RadioDriver*>(simulation.getModule(*it))->incomingSignal--;
    if (check_and_cast<RadioDriver*>(simulation.getModule(*it))->incomingSignal == 0)
      check_and_cast<RadioDriver*>(simulation.getModule(*it))->ccaIsFreeChannel = true;
  }

// draw range
  if (ANNOTATE)
  {
    (&mote->getParentModule()->getDisplayString())->setTagArg("r", 0, "0");
  }
}

/*
 * a mote sudden listens
 */
void World::beginListening(RadioDriver *mote)
{
// Receiver ID
  int recverID = mote->getId();

  mote->ccaIsFreeChannel = true;

// consider all incoming message to note incomplete
  for (std::list<mySignal*>::iterator it = signals.begin(); it != signals.end(); it++)
    if ((*it)->radioRecverID == recverID)
    {
      mote->ccaIsFreeChannel = false;
      (*it)->corrupt();
    }
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
      (*it)->corrupt();

  mote->ccaIsFreeChannel = true;
}

/*
 * register on-air signal
 */
void World::considerSignal(mySignal* signal)
{
// Receiver ID
  int recverID = signal->radioRecverID;

  // Incomplete message
  if ((check_and_cast<RadioDriver*>(simulation.getModule(recverID)))->status != LISTENING)
    signal->corrupt();

// is this singal interferenced
  if ((check_and_cast<RadioDriver*>(simulation.getModule(recverID)))->incomingSignal != 0)
    // interfere others signal
    for (std::list<mySignal*>::iterator it = signals.begin(); it != signals.end(); it++)
      if ((*it)->radioRecverID == recverID)
        (*it)->corrupt();
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
