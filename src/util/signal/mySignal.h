/*
 * @author
 */

#ifndef SIGNAL_H_
#define SIGNAL_H_

namespace wsn_energy {

class mySignal
{
  private:
    bool interferred;
    bool incompleted;
    bool success;

    int rssi;        // 8 bit RSSI offset

  public:
    int radioSenderID;
    int radioRecverID;

    mySignal();
    mySignal(int radioSenderID, int radioRecverID);

    void setInterferred();
    void setIncompleted();

    bool isInterferred();
    bool isIncomplete();
    bool isSuccess();
};

} /* namespace wsn_energy */

#endif /* SIGNAL_H_ */
