//
// Generated file, do not edit! Created by opp_msgc 4.4 from packet/packet.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "packet_m.h"

USING_NAMESPACE

// Template rule which fires if a struct or class doesn't have operator<<
template<typename T>
std::ostream& operator<<(std::ostream& out,const T&) {return out;}

// Another default rule (prevents compiler from choosing base class' doPacking())
template<typename T>
void doPacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doPacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}

template<typename T>
void doUnpacking(cCommBuffer *, T& t) {
    throw cRuntimeError("Parsim error: no doUnpacking() function for type %s or its base class (check .msg and _m.cc/h files!)",opp_typename(typeid(t)));
}



namespace wsn_energy {

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::MESSAGE_KIND");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::MESSAGE_KIND"));
    e->insert(DATA, "DATA");
    e->insert(COMMAND, "COMMAND");
    e->insert(RESULT, "RESULT");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::SPECIAL_EVENT");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::SPECIAL_EVENT"));
    e->insert(NODE_STARTUP, "NODE_STARTUP");
    e->insert(OUT_OF_ENERGY, "OUT_OF_ENERGY");
    e->insert(NODE_DESTRUCT, "NODE_DESTRUCT");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::COMMAND_APP");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::COMMAND_APP"));
    e->insert(APP_ENVIRON_FLAG, "APP_ENVIRON_FLAG");
    e->insert(APP_SENSING_FLAG, "APP_SENSING_FLAG");
    e->insert(APP_WORKING_FLAG, "APP_WORKING_FLAG");
    e->insert(RPL_CONSTRUCT, "RPL_CONSTRUCT");
    e->insert(RPL_SET_UP_DELAY, "RPL_SET_UP_DELAY");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::COMMAND_NET");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::COMMAND_NET"));
    e->insert(NET_TIMER_DIO, "NET_TIMER_DIO");
    e->insert(NET_TIMER_DIS, "NET_TIMER_DIS");
    e->insert(NET_CHECK_BUFFER, "NET_CHECK_BUFFER");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::RESULT_NET");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::RESULT_NET"));
    e->insert(NET_DIO_SENT, "NET_DIO_SENT");
    e->insert(NET_DIS_SENT, "NET_DIS_SENT");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::IP_PACKET_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::IP_PACKET_TYPE"));
    e->insert(NET_DATA, "NET_DATA");
    e->insert(NET_ICMP_RPL, "NET_ICMP_RPL");
    e->insert(NET_ICMP_DIO, "NET_ICMP_DIO");
    e->insert(NET_ICMP_DIS, "NET_ICMP_DIS");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::COMMAND_MAC");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::COMMAND_MAC"));
    e->insert(CHANNEL_CCA_REQUEST, "CHANNEL_CCA_REQUEST");
    e->insert(MAC_BEGIN_SEND_FRAME, "MAC_BEGIN_SEND_FRAME");
    e->insert(MAC_END_SEND_FRAME, "MAC_END_SEND_FRAME");
    e->insert(MAC_EXPIRE_IFS, "MAC_EXPIRE_IFS");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::RESULT_FROM_MAC");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::RESULT_FROM_MAC"));
    e->insert(MAC_SEND_DEAD_NEIGHBOR, "MAC_SEND_DEAD_NEIGHBOR");
    e->insert(MAC_FINISH_PHASE, "MAC_FINISH_PHASE");
    e->insert(MAC_SEND_END_TRANSMIT, "MAC_SEND_END_TRANSMIT");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::COMMAND_RDC");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::COMMAND_RDC"));
    e->insert(RDC_TRANSMIT, "RDC_TRANSMIT");
    e->insert(RDC_LISTEN, "RDC_LISTEN");
    e->insert(RDC_IDLE, "RDC_IDLE");
    e->insert(RDC_WAIT_FOR_ACK, "RDC_WAIT_FOR_ACK");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::RESULT_RDC");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::RESULT_RDC"));
    e->insert(RDC_SEND_OK, "RDC_SEND_OK");
    e->insert(RDC_SEND_NO_ACK, "RDC_SEND_NO_ACK");
    e->insert(RDC_SEND_FATAL, "RDC_SEND_FATAL");
    e->insert(RDC_SEND_COL, "RDC_SEND_COL");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::COMMAND_PHY");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::COMMAND_PHY"));
    e->insert(PHY_BEGIN_CCA, "PHY_BEGIN_CCA");
    e->insert(PHY_END_CCA, "PHY_END_CCA");
    e->insert(PHY_SWITCH_TRANSMIT, "PHY_SWITCH_TRANSMIT");
    e->insert(PHY_SWITCH_LISTEN, "PHY_SWITCH_LISTEN");
    e->insert(PHY_SWITCH_IDLE, "PHY_SWITCH_IDLE");
    e->insert(PHY_BEGIN_TRANSMIT, "PHY_BEGIN_TRANSMIT");
    e->insert(PHY_END_TRANSMIT, "PHY_END_TRANSMIT");
    e->insert(PHY_LISTENING, "PHY_LISTENING");
    e->insert(PHY_IDLING, "PHY_IDLING");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::RESULT_PHY");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::RESULT_PHY"));
    e->insert(CHANNEL_CLEAR, "CHANNEL_CLEAR");
    e->insert(CHANNEL_BUSY, "CHANNEL_BUSY");
    e->insert(PHY_TX_OK, "PHY_TX_OK");
    e->insert(PHY_TX_ERR, "PHY_TX_ERR");
    e->insert(PHY_BUSY, "PHY_BUSY");
    e->insert(PHY_RECV_OK, "PHY_RECV_OK");
    e->insert(PHY_RECV_CORRUPTED, "PHY_RECV_CORRUPTED");
    e->insert(PHY_RECV_INCOMPLETED, "PHY_RECV_INCOMPLETED");
);

Register_Class(Command);

Command::Command(const char *name, int kind) : cPacket(name,kind)
{
    this->note_var = 0;
}

Command::Command(const Command& other) : cPacket(other)
{
    copy(other);
}

Command::~Command()
{
}

Command& Command::operator=(const Command& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Command::copy(const Command& other)
{
    this->note_var = other.note_var;
}

void Command::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->note_var);
}

void Command::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->note_var);
}

int Command::getNote() const
{
    return note_var;
}

void Command::setNote(int note)
{
    this->note_var = note;
}

class CommandDescriptor : public cClassDescriptor
{
  public:
    CommandDescriptor();
    virtual ~CommandDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(CommandDescriptor);

CommandDescriptor::CommandDescriptor() : cClassDescriptor("wsn_energy::Command", "cPacket")
{
}

CommandDescriptor::~CommandDescriptor()
{
}

bool CommandDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Command *>(obj)!=NULL;
}

const char *CommandDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int CommandDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int CommandDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *CommandDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "note",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int CommandDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "note")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *CommandDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *CommandDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int CommandDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Command *pp = (Command *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string CommandDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Command *pp = (Command *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNote());
        default: return "";
    }
}

bool CommandDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Command *pp = (Command *)object; (void)pp;
    switch (field) {
        case 0: pp->setNote(string2long(value)); return true;
        default: return false;
    }
}

const char *CommandDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *CommandDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Command *pp = (Command *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Result);

Result::Result(const char *name, int kind) : cPacket(name,kind)
{
    this->note_var = 0;
}

Result::Result(const Result& other) : cPacket(other)
{
    copy(other);
}

Result::~Result()
{
}

Result& Result::operator=(const Result& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Result::copy(const Result& other)
{
    this->note_var = other.note_var;
}

void Result::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->note_var);
}

void Result::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->note_var);
}

int Result::getNote() const
{
    return note_var;
}

void Result::setNote(int note)
{
    this->note_var = note;
}

class ResultDescriptor : public cClassDescriptor
{
  public:
    ResultDescriptor();
    virtual ~ResultDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(ResultDescriptor);

ResultDescriptor::ResultDescriptor() : cClassDescriptor("wsn_energy::Result", "cPacket")
{
}

ResultDescriptor::~ResultDescriptor()
{
}

bool ResultDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Result *>(obj)!=NULL;
}

const char *ResultDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int ResultDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int ResultDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *ResultDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "note",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int ResultDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "note")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *ResultDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *ResultDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int ResultDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Result *pp = (Result *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string ResultDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Result *pp = (Result *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNote());
        default: return "";
    }
}

bool ResultDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Result *pp = (Result *)object; (void)pp;
    switch (field) {
        case 0: pp->setNote(string2long(value)); return true;
        default: return false;
    }
}

const char *ResultDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *ResultDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Result *pp = (Result *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Raw);

Raw::Raw(const char *name, int kind) : cPacket(name,kind)
{
    this->headerLength_var = 6;
    this->maxPayloadLength_var = 127;
}

Raw::Raw(const Raw& other) : cPacket(other)
{
    copy(other);
}

Raw::~Raw()
{
}

Raw& Raw::operator=(const Raw& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Raw::copy(const Raw& other)
{
    this->headerLength_var = other.headerLength_var;
    this->maxPayloadLength_var = other.maxPayloadLength_var;
}

void Raw::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->headerLength_var);
    doPacking(b,this->maxPayloadLength_var);
}

void Raw::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->headerLength_var);
    doUnpacking(b,this->maxPayloadLength_var);
}

int Raw::getHeaderLength() const
{
    return headerLength_var;
}

void Raw::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

int Raw::getMaxPayloadLength() const
{
    return maxPayloadLength_var;
}

void Raw::setMaxPayloadLength(int maxPayloadLength)
{
    this->maxPayloadLength_var = maxPayloadLength;
}

class RawDescriptor : public cClassDescriptor
{
  public:
    RawDescriptor();
    virtual ~RawDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(RawDescriptor);

RawDescriptor::RawDescriptor() : cClassDescriptor("wsn_energy::Raw", "cPacket")
{
}

RawDescriptor::~RawDescriptor()
{
}

bool RawDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Raw *>(obj)!=NULL;
}

const char *RawDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int RawDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int RawDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *RawDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "headerLength",
        "maxPayloadLength",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int RawDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+0;
    if (fieldName[0]=='m' && strcmp(fieldName, "maxPayloadLength")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *RawDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *RawDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int RawDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Raw *pp = (Raw *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string RawDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Raw *pp = (Raw *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeaderLength());
        case 1: return long2string(pp->getMaxPayloadLength());
        default: return "";
    }
}

bool RawDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Raw *pp = (Raw *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeaderLength(string2long(value)); return true;
        case 1: pp->setMaxPayloadLength(string2long(value)); return true;
        default: return false;
    }
}

const char *RawDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *RawDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Raw *pp = (Raw *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Frame);

Frame::Frame(const char *name, int kind) : cPacket(name,kind)
{
    this->numberTransmission_var = 0;
    this->headerLength_var = 0;
    this->frameType_var = 0;
    this->securityEnabled_var = 0;
    this->framePending_var = 0;
    this->ackRequired_var = 0;
    this->panIdCompression_var = 0;
    this->reserved_var = 0;
    this->destinationAddressMode_var = 0;
    this->frameVersion_var = 0;
    this->sourceAddressMode_var = 0;
    this->frameCheckSequence_var = 0;
}

Frame::Frame(const Frame& other) : cPacket(other)
{
    copy(other);
}

Frame::~Frame()
{
}

Frame& Frame::operator=(const Frame& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Frame::copy(const Frame& other)
{
    this->numberTransmission_var = other.numberTransmission_var;
    this->headerLength_var = other.headerLength_var;
    this->frameType_var = other.frameType_var;
    this->securityEnabled_var = other.securityEnabled_var;
    this->framePending_var = other.framePending_var;
    this->ackRequired_var = other.ackRequired_var;
    this->panIdCompression_var = other.panIdCompression_var;
    this->reserved_var = other.reserved_var;
    this->destinationAddressMode_var = other.destinationAddressMode_var;
    this->frameVersion_var = other.frameVersion_var;
    this->sourceAddressMode_var = other.sourceAddressMode_var;
    this->frameCheckSequence_var = other.frameCheckSequence_var;
}

void Frame::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->numberTransmission_var);
    doPacking(b,this->headerLength_var);
    doPacking(b,this->frameType_var);
    doPacking(b,this->securityEnabled_var);
    doPacking(b,this->framePending_var);
    doPacking(b,this->ackRequired_var);
    doPacking(b,this->panIdCompression_var);
    doPacking(b,this->reserved_var);
    doPacking(b,this->destinationAddressMode_var);
    doPacking(b,this->frameVersion_var);
    doPacking(b,this->sourceAddressMode_var);
    doPacking(b,this->frameCheckSequence_var);
}

void Frame::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->numberTransmission_var);
    doUnpacking(b,this->headerLength_var);
    doUnpacking(b,this->frameType_var);
    doUnpacking(b,this->securityEnabled_var);
    doUnpacking(b,this->framePending_var);
    doUnpacking(b,this->ackRequired_var);
    doUnpacking(b,this->panIdCompression_var);
    doUnpacking(b,this->reserved_var);
    doUnpacking(b,this->destinationAddressMode_var);
    doUnpacking(b,this->frameVersion_var);
    doUnpacking(b,this->sourceAddressMode_var);
    doUnpacking(b,this->frameCheckSequence_var);
}

int Frame::getNumberTransmission() const
{
    return numberTransmission_var;
}

void Frame::setNumberTransmission(int numberTransmission)
{
    this->numberTransmission_var = numberTransmission;
}

int Frame::getHeaderLength() const
{
    return headerLength_var;
}

void Frame::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

uint8_t Frame::getFrameType() const
{
    return frameType_var;
}

void Frame::setFrameType(uint8_t frameType)
{
    this->frameType_var = frameType;
}

uint8_t Frame::getSecurityEnabled() const
{
    return securityEnabled_var;
}

void Frame::setSecurityEnabled(uint8_t securityEnabled)
{
    this->securityEnabled_var = securityEnabled;
}

uint8_t Frame::getFramePending() const
{
    return framePending_var;
}

void Frame::setFramePending(uint8_t framePending)
{
    this->framePending_var = framePending;
}

uint8_t Frame::getAckRequired() const
{
    return ackRequired_var;
}

void Frame::setAckRequired(uint8_t ackRequired)
{
    this->ackRequired_var = ackRequired;
}

uint8_t Frame::getPanIdCompression() const
{
    return panIdCompression_var;
}

void Frame::setPanIdCompression(uint8_t panIdCompression)
{
    this->panIdCompression_var = panIdCompression;
}

uint8_t Frame::getReserved() const
{
    return reserved_var;
}

void Frame::setReserved(uint8_t reserved)
{
    this->reserved_var = reserved;
}

uint8_t Frame::getDestinationAddressMode() const
{
    return destinationAddressMode_var;
}

void Frame::setDestinationAddressMode(uint8_t destinationAddressMode)
{
    this->destinationAddressMode_var = destinationAddressMode;
}

uint8_t Frame::getFrameVersion() const
{
    return frameVersion_var;
}

void Frame::setFrameVersion(uint8_t frameVersion)
{
    this->frameVersion_var = frameVersion;
}

uint8_t Frame::getSourceAddressMode() const
{
    return sourceAddressMode_var;
}

void Frame::setSourceAddressMode(uint8_t sourceAddressMode)
{
    this->sourceAddressMode_var = sourceAddressMode;
}

uint16_t Frame::getFrameCheckSequence() const
{
    return frameCheckSequence_var;
}

void Frame::setFrameCheckSequence(uint16_t frameCheckSequence)
{
    this->frameCheckSequence_var = frameCheckSequence;
}

class FrameDescriptor : public cClassDescriptor
{
  public:
    FrameDescriptor();
    virtual ~FrameDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FrameDescriptor);

FrameDescriptor::FrameDescriptor() : cClassDescriptor("wsn_energy::Frame", "cPacket")
{
}

FrameDescriptor::~FrameDescriptor()
{
}

bool FrameDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Frame *>(obj)!=NULL;
}

const char *FrameDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 12+basedesc->getFieldCount(object) : 12;
}

unsigned int FrameDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<12) ? fieldTypeFlags[field] : 0;
}

const char *FrameDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "numberTransmission",
        "headerLength",
        "frameType",
        "securityEnabled",
        "framePending",
        "ackRequired",
        "panIdCompression",
        "reserved",
        "destinationAddressMode",
        "frameVersion",
        "sourceAddressMode",
        "frameCheckSequence",
    };
    return (field>=0 && field<12) ? fieldNames[field] : NULL;
}

int FrameDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "numberTransmission")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameType")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "securityEnabled")==0) return base+3;
    if (fieldName[0]=='f' && strcmp(fieldName, "framePending")==0) return base+4;
    if (fieldName[0]=='a' && strcmp(fieldName, "ackRequired")==0) return base+5;
    if (fieldName[0]=='p' && strcmp(fieldName, "panIdCompression")==0) return base+6;
    if (fieldName[0]=='r' && strcmp(fieldName, "reserved")==0) return base+7;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationAddressMode")==0) return base+8;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameVersion")==0) return base+9;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceAddressMode")==0) return base+10;
    if (fieldName[0]=='f' && strcmp(fieldName, "frameCheckSequence")==0) return base+11;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint16_t",
    };
    return (field>=0 && field<12) ? fieldTypeStrings[field] : NULL;
}

const char *FrameDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FrameDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Frame *pp = (Frame *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FrameDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Frame *pp = (Frame *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNumberTransmission());
        case 1: return long2string(pp->getHeaderLength());
        case 2: return ulong2string(pp->getFrameType());
        case 3: return ulong2string(pp->getSecurityEnabled());
        case 4: return ulong2string(pp->getFramePending());
        case 5: return ulong2string(pp->getAckRequired());
        case 6: return ulong2string(pp->getPanIdCompression());
        case 7: return ulong2string(pp->getReserved());
        case 8: return ulong2string(pp->getDestinationAddressMode());
        case 9: return ulong2string(pp->getFrameVersion());
        case 10: return ulong2string(pp->getSourceAddressMode());
        case 11: return ulong2string(pp->getFrameCheckSequence());
        default: return "";
    }
}

bool FrameDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Frame *pp = (Frame *)object; (void)pp;
    switch (field) {
        case 0: pp->setNumberTransmission(string2long(value)); return true;
        case 1: pp->setHeaderLength(string2long(value)); return true;
        case 2: pp->setFrameType(string2ulong(value)); return true;
        case 3: pp->setSecurityEnabled(string2ulong(value)); return true;
        case 4: pp->setFramePending(string2ulong(value)); return true;
        case 5: pp->setAckRequired(string2ulong(value)); return true;
        case 6: pp->setPanIdCompression(string2ulong(value)); return true;
        case 7: pp->setReserved(string2ulong(value)); return true;
        case 8: pp->setDestinationAddressMode(string2ulong(value)); return true;
        case 9: pp->setFrameVersion(string2ulong(value)); return true;
        case 10: pp->setSourceAddressMode(string2ulong(value)); return true;
        case 11: pp->setFrameCheckSequence(string2ulong(value)); return true;
        default: return false;
    }
}

const char *FrameDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<12) ? fieldStructNames[field] : NULL;
}

void *FrameDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Frame *pp = (Frame *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FrameData);

FrameData::FrameData(const char *name, int kind) : wsn_energy::Frame(name,kind)
{
    this->headerLength_var = 0;
    this->dataSequenceNumber_var = 0;
    this->senderMacAddress_var = 0;
    this->recverMacAddress_var = 0;
    this->checkSequenceNumber_var = 0;
}

FrameData::FrameData(const FrameData& other) : wsn_energy::Frame(other)
{
    copy(other);
}

FrameData::~FrameData()
{
}

FrameData& FrameData::operator=(const FrameData& other)
{
    if (this==&other) return *this;
    wsn_energy::Frame::operator=(other);
    copy(other);
    return *this;
}

void FrameData::copy(const FrameData& other)
{
    this->headerLength_var = other.headerLength_var;
    this->dataSequenceNumber_var = other.dataSequenceNumber_var;
    this->senderMacAddress_var = other.senderMacAddress_var;
    this->recverMacAddress_var = other.recverMacAddress_var;
    this->checkSequenceNumber_var = other.checkSequenceNumber_var;
}

void FrameData::parsimPack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimPack(b);
    doPacking(b,this->headerLength_var);
    doPacking(b,this->dataSequenceNumber_var);
    doPacking(b,this->senderMacAddress_var);
    doPacking(b,this->recverMacAddress_var);
    doPacking(b,this->checkSequenceNumber_var);
}

void FrameData::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimUnpack(b);
    doUnpacking(b,this->headerLength_var);
    doUnpacking(b,this->dataSequenceNumber_var);
    doUnpacking(b,this->senderMacAddress_var);
    doUnpacking(b,this->recverMacAddress_var);
    doUnpacking(b,this->checkSequenceNumber_var);
}

int FrameData::getHeaderLength() const
{
    return headerLength_var;
}

void FrameData::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

uint8_t FrameData::getDataSequenceNumber() const
{
    return dataSequenceNumber_var;
}

void FrameData::setDataSequenceNumber(uint8_t dataSequenceNumber)
{
    this->dataSequenceNumber_var = dataSequenceNumber;
}

int FrameData::getSenderMacAddress() const
{
    return senderMacAddress_var;
}

void FrameData::setSenderMacAddress(int senderMacAddress)
{
    this->senderMacAddress_var = senderMacAddress;
}

int FrameData::getRecverMacAddress() const
{
    return recverMacAddress_var;
}

void FrameData::setRecverMacAddress(int recverMacAddress)
{
    this->recverMacAddress_var = recverMacAddress;
}

int FrameData::getCheckSequenceNumber() const
{
    return checkSequenceNumber_var;
}

void FrameData::setCheckSequenceNumber(int checkSequenceNumber)
{
    this->checkSequenceNumber_var = checkSequenceNumber;
}

class FrameDataDescriptor : public cClassDescriptor
{
  public:
    FrameDataDescriptor();
    virtual ~FrameDataDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FrameDataDescriptor);

FrameDataDescriptor::FrameDataDescriptor() : cClassDescriptor("wsn_energy::FrameData", "wsn_energy::Frame")
{
}

FrameDataDescriptor::~FrameDataDescriptor()
{
}

bool FrameDataDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FrameData *>(obj)!=NULL;
}

const char *FrameDataDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameDataDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int FrameDataDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *FrameDataDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "headerLength",
        "dataSequenceNumber",
        "senderMacAddress",
        "recverMacAddress",
        "checkSequenceNumber",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int FrameDataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSequenceNumber")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderMacAddress")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "recverMacAddress")==0) return base+3;
    if (fieldName[0]=='c' && strcmp(fieldName, "checkSequenceNumber")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameDataDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "uint8_t",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *FrameDataDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FrameDataDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FrameData *pp = (FrameData *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FrameDataDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FrameData *pp = (FrameData *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeaderLength());
        case 1: return ulong2string(pp->getDataSequenceNumber());
        case 2: return long2string(pp->getSenderMacAddress());
        case 3: return long2string(pp->getRecverMacAddress());
        case 4: return long2string(pp->getCheckSequenceNumber());
        default: return "";
    }
}

bool FrameDataDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FrameData *pp = (FrameData *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeaderLength(string2long(value)); return true;
        case 1: pp->setDataSequenceNumber(string2ulong(value)); return true;
        case 2: pp->setSenderMacAddress(string2long(value)); return true;
        case 3: pp->setRecverMacAddress(string2long(value)); return true;
        case 4: pp->setCheckSequenceNumber(string2long(value)); return true;
        default: return false;
    }
}

const char *FrameDataDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *FrameDataDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FrameData *pp = (FrameData *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FrameACK);

FrameACK::FrameACK(const char *name, int kind) : wsn_energy::Frame(name,kind)
{
    this->headerLength_var = 3;
    this->dataSequenceNumber_var = 0;
}

FrameACK::FrameACK(const FrameACK& other) : wsn_energy::Frame(other)
{
    copy(other);
}

FrameACK::~FrameACK()
{
}

FrameACK& FrameACK::operator=(const FrameACK& other)
{
    if (this==&other) return *this;
    wsn_energy::Frame::operator=(other);
    copy(other);
    return *this;
}

void FrameACK::copy(const FrameACK& other)
{
    this->headerLength_var = other.headerLength_var;
    this->dataSequenceNumber_var = other.dataSequenceNumber_var;
}

void FrameACK::parsimPack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimPack(b);
    doPacking(b,this->headerLength_var);
    doPacking(b,this->dataSequenceNumber_var);
}

void FrameACK::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimUnpack(b);
    doUnpacking(b,this->headerLength_var);
    doUnpacking(b,this->dataSequenceNumber_var);
}

int FrameACK::getHeaderLength() const
{
    return headerLength_var;
}

void FrameACK::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

uint8_t FrameACK::getDataSequenceNumber() const
{
    return dataSequenceNumber_var;
}

void FrameACK::setDataSequenceNumber(uint8_t dataSequenceNumber)
{
    this->dataSequenceNumber_var = dataSequenceNumber;
}

class FrameACKDescriptor : public cClassDescriptor
{
  public:
    FrameACKDescriptor();
    virtual ~FrameACKDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FrameACKDescriptor);

FrameACKDescriptor::FrameACKDescriptor() : cClassDescriptor("wsn_energy::FrameACK", "wsn_energy::Frame")
{
}

FrameACKDescriptor::~FrameACKDescriptor()
{
}

bool FrameACKDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FrameACK *>(obj)!=NULL;
}

const char *FrameACKDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameACKDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int FrameACKDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<2) ? fieldTypeFlags[field] : 0;
}

const char *FrameACKDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "headerLength",
        "dataSequenceNumber",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int FrameACKDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSequenceNumber")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameACKDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "uint8_t",
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *FrameACKDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FrameACKDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FrameACK *pp = (FrameACK *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FrameACKDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FrameACK *pp = (FrameACK *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeaderLength());
        case 1: return ulong2string(pp->getDataSequenceNumber());
        default: return "";
    }
}

bool FrameACKDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FrameACK *pp = (FrameACK *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeaderLength(string2long(value)); return true;
        case 1: pp->setDataSequenceNumber(string2ulong(value)); return true;
        default: return false;
    }
}

const char *FrameACKDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
    };
    return (field>=0 && field<2) ? fieldStructNames[field] : NULL;
}

void *FrameACKDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FrameACK *pp = (FrameACK *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FrameBeacon);

FrameBeacon::FrameBeacon(const char *name, int kind) : wsn_energy::Frame(name,kind)
{
    this->headerLength_var = 0;
    this->beaconSequenceNumber_var = 0;
    this->destinationPanId_var = 0;
    for (unsigned int i=0; i<8; i++)
        this->destinationAddress_var[i] = 0;
    this->sourcePanId_var = 0;
    for (unsigned int i=0; i<8; i++)
        this->sourceAddress_var[i] = 0;
    this->beaconOrder_var = 0;
    this->superFrameOrder_var = 0;
    this->finalCAPslot_var = 0;
    this->batteryLifeExtension_var = 0;
    this->reserved_var = 0;
    this->PANcoordinator_var = 0;
    this->associationPermit_var = 0;
}

FrameBeacon::FrameBeacon(const FrameBeacon& other) : wsn_energy::Frame(other)
{
    copy(other);
}

FrameBeacon::~FrameBeacon()
{
}

FrameBeacon& FrameBeacon::operator=(const FrameBeacon& other)
{
    if (this==&other) return *this;
    wsn_energy::Frame::operator=(other);
    copy(other);
    return *this;
}

void FrameBeacon::copy(const FrameBeacon& other)
{
    this->headerLength_var = other.headerLength_var;
    this->beaconSequenceNumber_var = other.beaconSequenceNumber_var;
    this->destinationPanId_var = other.destinationPanId_var;
    for (unsigned int i=0; i<8; i++)
        this->destinationAddress_var[i] = other.destinationAddress_var[i];
    this->sourcePanId_var = other.sourcePanId_var;
    for (unsigned int i=0; i<8; i++)
        this->sourceAddress_var[i] = other.sourceAddress_var[i];
    this->beaconOrder_var = other.beaconOrder_var;
    this->superFrameOrder_var = other.superFrameOrder_var;
    this->finalCAPslot_var = other.finalCAPslot_var;
    this->batteryLifeExtension_var = other.batteryLifeExtension_var;
    this->reserved_var = other.reserved_var;
    this->PANcoordinator_var = other.PANcoordinator_var;
    this->associationPermit_var = other.associationPermit_var;
}

void FrameBeacon::parsimPack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimPack(b);
    doPacking(b,this->headerLength_var);
    doPacking(b,this->beaconSequenceNumber_var);
    doPacking(b,this->destinationPanId_var);
    doPacking(b,this->destinationAddress_var,8);
    doPacking(b,this->sourcePanId_var);
    doPacking(b,this->sourceAddress_var,8);
    doPacking(b,this->beaconOrder_var);
    doPacking(b,this->superFrameOrder_var);
    doPacking(b,this->finalCAPslot_var);
    doPacking(b,this->batteryLifeExtension_var);
    doPacking(b,this->reserved_var);
    doPacking(b,this->PANcoordinator_var);
    doPacking(b,this->associationPermit_var);
}

void FrameBeacon::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimUnpack(b);
    doUnpacking(b,this->headerLength_var);
    doUnpacking(b,this->beaconSequenceNumber_var);
    doUnpacking(b,this->destinationPanId_var);
    doUnpacking(b,this->destinationAddress_var,8);
    doUnpacking(b,this->sourcePanId_var);
    doUnpacking(b,this->sourceAddress_var,8);
    doUnpacking(b,this->beaconOrder_var);
    doUnpacking(b,this->superFrameOrder_var);
    doUnpacking(b,this->finalCAPslot_var);
    doUnpacking(b,this->batteryLifeExtension_var);
    doUnpacking(b,this->reserved_var);
    doUnpacking(b,this->PANcoordinator_var);
    doUnpacking(b,this->associationPermit_var);
}

int FrameBeacon::getHeaderLength() const
{
    return headerLength_var;
}

void FrameBeacon::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

uint8_t FrameBeacon::getBeaconSequenceNumber() const
{
    return beaconSequenceNumber_var;
}

void FrameBeacon::setBeaconSequenceNumber(uint8_t beaconSequenceNumber)
{
    this->beaconSequenceNumber_var = beaconSequenceNumber;
}

uint16_t FrameBeacon::getDestinationPanId() const
{
    return destinationPanId_var;
}

void FrameBeacon::setDestinationPanId(uint16_t destinationPanId)
{
    this->destinationPanId_var = destinationPanId;
}

unsigned int FrameBeacon::getDestinationAddressArraySize() const
{
    return 8;
}

uint8_t FrameBeacon::getDestinationAddress(unsigned int k) const
{
    if (k>=8) throw cRuntimeError("Array of size 8 indexed by %lu", (unsigned long)k);
    return destinationAddress_var[k];
}

void FrameBeacon::setDestinationAddress(unsigned int k, uint8_t destinationAddress)
{
    if (k>=8) throw cRuntimeError("Array of size 8 indexed by %lu", (unsigned long)k);
    this->destinationAddress_var[k] = destinationAddress;
}

uint16_t FrameBeacon::getSourcePanId() const
{
    return sourcePanId_var;
}

void FrameBeacon::setSourcePanId(uint16_t sourcePanId)
{
    this->sourcePanId_var = sourcePanId;
}

unsigned int FrameBeacon::getSourceAddressArraySize() const
{
    return 8;
}

uint8_t FrameBeacon::getSourceAddress(unsigned int k) const
{
    if (k>=8) throw cRuntimeError("Array of size 8 indexed by %lu", (unsigned long)k);
    return sourceAddress_var[k];
}

void FrameBeacon::setSourceAddress(unsigned int k, uint8_t sourceAddress)
{
    if (k>=8) throw cRuntimeError("Array of size 8 indexed by %lu", (unsigned long)k);
    this->sourceAddress_var[k] = sourceAddress;
}

uint8_t FrameBeacon::getBeaconOrder() const
{
    return beaconOrder_var;
}

void FrameBeacon::setBeaconOrder(uint8_t beaconOrder)
{
    this->beaconOrder_var = beaconOrder;
}

uint8_t FrameBeacon::getSuperFrameOrder() const
{
    return superFrameOrder_var;
}

void FrameBeacon::setSuperFrameOrder(uint8_t superFrameOrder)
{
    this->superFrameOrder_var = superFrameOrder;
}

uint8_t FrameBeacon::getFinalCAPslot() const
{
    return finalCAPslot_var;
}

void FrameBeacon::setFinalCAPslot(uint8_t finalCAPslot)
{
    this->finalCAPslot_var = finalCAPslot;
}

uint8_t FrameBeacon::getBatteryLifeExtension() const
{
    return batteryLifeExtension_var;
}

void FrameBeacon::setBatteryLifeExtension(uint8_t batteryLifeExtension)
{
    this->batteryLifeExtension_var = batteryLifeExtension;
}

uint8_t FrameBeacon::getReserved() const
{
    return reserved_var;
}

void FrameBeacon::setReserved(uint8_t reserved)
{
    this->reserved_var = reserved;
}

uint8_t FrameBeacon::getPANcoordinator() const
{
    return PANcoordinator_var;
}

void FrameBeacon::setPANcoordinator(uint8_t PANcoordinator)
{
    this->PANcoordinator_var = PANcoordinator;
}

uint8_t FrameBeacon::getAssociationPermit() const
{
    return associationPermit_var;
}

void FrameBeacon::setAssociationPermit(uint8_t associationPermit)
{
    this->associationPermit_var = associationPermit;
}

class FrameBeaconDescriptor : public cClassDescriptor
{
  public:
    FrameBeaconDescriptor();
    virtual ~FrameBeaconDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FrameBeaconDescriptor);

FrameBeaconDescriptor::FrameBeaconDescriptor() : cClassDescriptor("wsn_energy::FrameBeacon", "wsn_energy::Frame")
{
}

FrameBeaconDescriptor::~FrameBeaconDescriptor()
{
}

bool FrameBeaconDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FrameBeacon *>(obj)!=NULL;
}

const char *FrameBeaconDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameBeaconDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 13+basedesc->getFieldCount(object) : 13;
}

unsigned int FrameBeaconDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<13) ? fieldTypeFlags[field] : 0;
}

const char *FrameBeaconDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "headerLength",
        "beaconSequenceNumber",
        "destinationPanId",
        "destinationAddress",
        "sourcePanId",
        "sourceAddress",
        "beaconOrder",
        "superFrameOrder",
        "finalCAPslot",
        "batteryLifeExtension",
        "reserved",
        "PANcoordinator",
        "associationPermit",
    };
    return (field>=0 && field<13) ? fieldNames[field] : NULL;
}

int FrameBeaconDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+0;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconSequenceNumber")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPanId")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationAddress")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePanId")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceAddress")==0) return base+5;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconOrder")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "superFrameOrder")==0) return base+7;
    if (fieldName[0]=='f' && strcmp(fieldName, "finalCAPslot")==0) return base+8;
    if (fieldName[0]=='b' && strcmp(fieldName, "batteryLifeExtension")==0) return base+9;
    if (fieldName[0]=='r' && strcmp(fieldName, "reserved")==0) return base+10;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANcoordinator")==0) return base+11;
    if (fieldName[0]=='a' && strcmp(fieldName, "associationPermit")==0) return base+12;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameBeaconDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "uint8_t",
        "uint16_t",
        "uint8_t",
        "uint16_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
        "uint8_t",
    };
    return (field>=0 && field<13) ? fieldTypeStrings[field] : NULL;
}

const char *FrameBeaconDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FrameBeaconDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FrameBeacon *pp = (FrameBeacon *)object; (void)pp;
    switch (field) {
        case 3: return 8;
        case 5: return 8;
        default: return 0;
    }
}

std::string FrameBeaconDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FrameBeacon *pp = (FrameBeacon *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeaderLength());
        case 1: return ulong2string(pp->getBeaconSequenceNumber());
        case 2: return ulong2string(pp->getDestinationPanId());
        case 3: return ulong2string(pp->getDestinationAddress(i));
        case 4: return ulong2string(pp->getSourcePanId());
        case 5: return ulong2string(pp->getSourceAddress(i));
        case 6: return ulong2string(pp->getBeaconOrder());
        case 7: return ulong2string(pp->getSuperFrameOrder());
        case 8: return ulong2string(pp->getFinalCAPslot());
        case 9: return ulong2string(pp->getBatteryLifeExtension());
        case 10: return ulong2string(pp->getReserved());
        case 11: return ulong2string(pp->getPANcoordinator());
        case 12: return ulong2string(pp->getAssociationPermit());
        default: return "";
    }
}

bool FrameBeaconDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FrameBeacon *pp = (FrameBeacon *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeaderLength(string2long(value)); return true;
        case 1: pp->setBeaconSequenceNumber(string2ulong(value)); return true;
        case 2: pp->setDestinationPanId(string2ulong(value)); return true;
        case 3: pp->setDestinationAddress(i,string2ulong(value)); return true;
        case 4: pp->setSourcePanId(string2ulong(value)); return true;
        case 5: pp->setSourceAddress(i,string2ulong(value)); return true;
        case 6: pp->setBeaconOrder(string2ulong(value)); return true;
        case 7: pp->setSuperFrameOrder(string2ulong(value)); return true;
        case 8: pp->setFinalCAPslot(string2ulong(value)); return true;
        case 9: pp->setBatteryLifeExtension(string2ulong(value)); return true;
        case 10: pp->setReserved(string2ulong(value)); return true;
        case 11: pp->setPANcoordinator(string2ulong(value)); return true;
        case 12: pp->setAssociationPermit(string2ulong(value)); return true;
        default: return false;
    }
}

const char *FrameBeaconDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<13) ? fieldStructNames[field] : NULL;
}

void *FrameBeaconDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FrameBeacon *pp = (FrameBeacon *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FrameCommand);

FrameCommand::FrameCommand(const char *name, int kind) : wsn_energy::Frame(name,kind)
{
    this->headerLength_var = 0;
    this->dataSequenceNumber_var = 0;
    this->destinationPanId_var = 0;
    for (unsigned int i=0; i<8; i++)
        this->destinationAddress_var[i] = 0;
    this->sourcePanId_var = 0;
    for (unsigned int i=0; i<8; i++)
        this->sourceAddress_var[i] = 0;
    this->commandType_var = 0;
}

FrameCommand::FrameCommand(const FrameCommand& other) : wsn_energy::Frame(other)
{
    copy(other);
}

FrameCommand::~FrameCommand()
{
}

FrameCommand& FrameCommand::operator=(const FrameCommand& other)
{
    if (this==&other) return *this;
    wsn_energy::Frame::operator=(other);
    copy(other);
    return *this;
}

void FrameCommand::copy(const FrameCommand& other)
{
    this->headerLength_var = other.headerLength_var;
    this->dataSequenceNumber_var = other.dataSequenceNumber_var;
    this->destinationPanId_var = other.destinationPanId_var;
    for (unsigned int i=0; i<8; i++)
        this->destinationAddress_var[i] = other.destinationAddress_var[i];
    this->sourcePanId_var = other.sourcePanId_var;
    for (unsigned int i=0; i<8; i++)
        this->sourceAddress_var[i] = other.sourceAddress_var[i];
    this->commandType_var = other.commandType_var;
}

void FrameCommand::parsimPack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimPack(b);
    doPacking(b,this->headerLength_var);
    doPacking(b,this->dataSequenceNumber_var);
    doPacking(b,this->destinationPanId_var);
    doPacking(b,this->destinationAddress_var,8);
    doPacking(b,this->sourcePanId_var);
    doPacking(b,this->sourceAddress_var,8);
    doPacking(b,this->commandType_var);
}

void FrameCommand::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimUnpack(b);
    doUnpacking(b,this->headerLength_var);
    doUnpacking(b,this->dataSequenceNumber_var);
    doUnpacking(b,this->destinationPanId_var);
    doUnpacking(b,this->destinationAddress_var,8);
    doUnpacking(b,this->sourcePanId_var);
    doUnpacking(b,this->sourceAddress_var,8);
    doUnpacking(b,this->commandType_var);
}

int FrameCommand::getHeaderLength() const
{
    return headerLength_var;
}

void FrameCommand::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

uint8_t FrameCommand::getDataSequenceNumber() const
{
    return dataSequenceNumber_var;
}

void FrameCommand::setDataSequenceNumber(uint8_t dataSequenceNumber)
{
    this->dataSequenceNumber_var = dataSequenceNumber;
}

uint16_t FrameCommand::getDestinationPanId() const
{
    return destinationPanId_var;
}

void FrameCommand::setDestinationPanId(uint16_t destinationPanId)
{
    this->destinationPanId_var = destinationPanId;
}

unsigned int FrameCommand::getDestinationAddressArraySize() const
{
    return 8;
}

uint8_t FrameCommand::getDestinationAddress(unsigned int k) const
{
    if (k>=8) throw cRuntimeError("Array of size 8 indexed by %lu", (unsigned long)k);
    return destinationAddress_var[k];
}

void FrameCommand::setDestinationAddress(unsigned int k, uint8_t destinationAddress)
{
    if (k>=8) throw cRuntimeError("Array of size 8 indexed by %lu", (unsigned long)k);
    this->destinationAddress_var[k] = destinationAddress;
}

uint16_t FrameCommand::getSourcePanId() const
{
    return sourcePanId_var;
}

void FrameCommand::setSourcePanId(uint16_t sourcePanId)
{
    this->sourcePanId_var = sourcePanId;
}

unsigned int FrameCommand::getSourceAddressArraySize() const
{
    return 8;
}

uint8_t FrameCommand::getSourceAddress(unsigned int k) const
{
    if (k>=8) throw cRuntimeError("Array of size 8 indexed by %lu", (unsigned long)k);
    return sourceAddress_var[k];
}

void FrameCommand::setSourceAddress(unsigned int k, uint8_t sourceAddress)
{
    if (k>=8) throw cRuntimeError("Array of size 8 indexed by %lu", (unsigned long)k);
    this->sourceAddress_var[k] = sourceAddress;
}

uint8_t FrameCommand::getCommandType() const
{
    return commandType_var;
}

void FrameCommand::setCommandType(uint8_t commandType)
{
    this->commandType_var = commandType;
}

class FrameCommandDescriptor : public cClassDescriptor
{
  public:
    FrameCommandDescriptor();
    virtual ~FrameCommandDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(FrameCommandDescriptor);

FrameCommandDescriptor::FrameCommandDescriptor() : cClassDescriptor("wsn_energy::FrameCommand", "wsn_energy::Frame")
{
}

FrameCommandDescriptor::~FrameCommandDescriptor()
{
}

bool FrameCommandDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FrameCommand *>(obj)!=NULL;
}

const char *FrameCommandDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameCommandDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 7+basedesc->getFieldCount(object) : 7;
}

unsigned int FrameCommandDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISARRAY | FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<7) ? fieldTypeFlags[field] : 0;
}

const char *FrameCommandDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "headerLength",
        "dataSequenceNumber",
        "destinationPanId",
        "destinationAddress",
        "sourcePanId",
        "sourceAddress",
        "commandType",
    };
    return (field>=0 && field<7) ? fieldNames[field] : NULL;
}

int FrameCommandDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSequenceNumber")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPanId")==0) return base+2;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationAddress")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePanId")==0) return base+4;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceAddress")==0) return base+5;
    if (fieldName[0]=='c' && strcmp(fieldName, "commandType")==0) return base+6;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameCommandDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "uint8_t",
        "uint16_t",
        "uint8_t",
        "uint16_t",
        "uint8_t",
        "uint8_t",
    };
    return (field>=0 && field<7) ? fieldTypeStrings[field] : NULL;
}

const char *FrameCommandDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int FrameCommandDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FrameCommand *pp = (FrameCommand *)object; (void)pp;
    switch (field) {
        case 3: return 8;
        case 5: return 8;
        default: return 0;
    }
}

std::string FrameCommandDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FrameCommand *pp = (FrameCommand *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeaderLength());
        case 1: return ulong2string(pp->getDataSequenceNumber());
        case 2: return ulong2string(pp->getDestinationPanId());
        case 3: return ulong2string(pp->getDestinationAddress(i));
        case 4: return ulong2string(pp->getSourcePanId());
        case 5: return ulong2string(pp->getSourceAddress(i));
        case 6: return ulong2string(pp->getCommandType());
        default: return "";
    }
}

bool FrameCommandDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FrameCommand *pp = (FrameCommand *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeaderLength(string2long(value)); return true;
        case 1: pp->setDataSequenceNumber(string2ulong(value)); return true;
        case 2: pp->setDestinationPanId(string2ulong(value)); return true;
        case 3: pp->setDestinationAddress(i,string2ulong(value)); return true;
        case 4: pp->setSourcePanId(string2ulong(value)); return true;
        case 5: pp->setSourceAddress(i,string2ulong(value)); return true;
        case 6: pp->setCommandType(string2ulong(value)); return true;
        default: return false;
    }
}

const char *FrameCommandDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<7) ? fieldStructNames[field] : NULL;
}

void *FrameCommandDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FrameCommand *pp = (FrameCommand *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(IpPacket);

IpPacket::IpPacket(const char *name, int kind) : cPacket(name,kind)
{
    this->time_var = 0;
    this->version_var = 0;
    this->trafficClass_var = 0;
    this->flowLabel_var = 0;
    this->payloadLength_var = 0;
    this->nextHeader_var = 0;
    this->hopLimit_var = 0;
    this->senderIpAddress_var = 0;
    this->recverIpAddress_var = 0;
    this->headerLength_var = 2;
}

IpPacket::IpPacket(const IpPacket& other) : cPacket(other)
{
    copy(other);
}

IpPacket::~IpPacket()
{
}

IpPacket& IpPacket::operator=(const IpPacket& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void IpPacket::copy(const IpPacket& other)
{
    this->time_var = other.time_var;
    this->version_var = other.version_var;
    this->trafficClass_var = other.trafficClass_var;
    this->flowLabel_var = other.flowLabel_var;
    this->payloadLength_var = other.payloadLength_var;
    this->nextHeader_var = other.nextHeader_var;
    this->hopLimit_var = other.hopLimit_var;
    this->senderIpAddress_var = other.senderIpAddress_var;
    this->recverIpAddress_var = other.recverIpAddress_var;
    this->headerLength_var = other.headerLength_var;
}

void IpPacket::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->time_var);
    doPacking(b,this->version_var);
    doPacking(b,this->trafficClass_var);
    doPacking(b,this->flowLabel_var);
    doPacking(b,this->payloadLength_var);
    doPacking(b,this->nextHeader_var);
    doPacking(b,this->hopLimit_var);
    doPacking(b,this->senderIpAddress_var);
    doPacking(b,this->recverIpAddress_var);
    doPacking(b,this->headerLength_var);
}

void IpPacket::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->time_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->trafficClass_var);
    doUnpacking(b,this->flowLabel_var);
    doUnpacking(b,this->payloadLength_var);
    doUnpacking(b,this->nextHeader_var);
    doUnpacking(b,this->hopLimit_var);
    doUnpacking(b,this->senderIpAddress_var);
    doUnpacking(b,this->recverIpAddress_var);
    doUnpacking(b,this->headerLength_var);
}

double IpPacket::getTime() const
{
    return time_var;
}

void IpPacket::setTime(double time)
{
    this->time_var = time;
}

int IpPacket::getVersion() const
{
    return version_var;
}

void IpPacket::setVersion(int version)
{
    this->version_var = version;
}

int IpPacket::getTrafficClass() const
{
    return trafficClass_var;
}

void IpPacket::setTrafficClass(int trafficClass)
{
    this->trafficClass_var = trafficClass;
}

int IpPacket::getFlowLabel() const
{
    return flowLabel_var;
}

void IpPacket::setFlowLabel(int flowLabel)
{
    this->flowLabel_var = flowLabel;
}

int IpPacket::getPayloadLength() const
{
    return payloadLength_var;
}

void IpPacket::setPayloadLength(int payloadLength)
{
    this->payloadLength_var = payloadLength;
}

int IpPacket::getNextHeader() const
{
    return nextHeader_var;
}

void IpPacket::setNextHeader(int nextHeader)
{
    this->nextHeader_var = nextHeader;
}

int IpPacket::getHopLimit() const
{
    return hopLimit_var;
}

void IpPacket::setHopLimit(int hopLimit)
{
    this->hopLimit_var = hopLimit;
}

int IpPacket::getSenderIpAddress() const
{
    return senderIpAddress_var;
}

void IpPacket::setSenderIpAddress(int senderIpAddress)
{
    this->senderIpAddress_var = senderIpAddress;
}

int IpPacket::getRecverIpAddress() const
{
    return recverIpAddress_var;
}

void IpPacket::setRecverIpAddress(int recverIpAddress)
{
    this->recverIpAddress_var = recverIpAddress;
}

int IpPacket::getHeaderLength() const
{
    return headerLength_var;
}

void IpPacket::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

class IpPacketDescriptor : public cClassDescriptor
{
  public:
    IpPacketDescriptor();
    virtual ~IpPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(IpPacketDescriptor);

IpPacketDescriptor::IpPacketDescriptor() : cClassDescriptor("wsn_energy::IpPacket", "cPacket")
{
}

IpPacketDescriptor::~IpPacketDescriptor()
{
}

bool IpPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<IpPacket *>(obj)!=NULL;
}

const char *IpPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int IpPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 10+basedesc->getFieldCount(object) : 10;
}

unsigned int IpPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<10) ? fieldTypeFlags[field] : 0;
}

const char *IpPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "time",
        "version",
        "trafficClass",
        "flowLabel",
        "payloadLength",
        "nextHeader",
        "hopLimit",
        "senderIpAddress",
        "recverIpAddress",
        "headerLength",
    };
    return (field>=0 && field<10) ? fieldNames[field] : NULL;
}

int IpPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "trafficClass")==0) return base+2;
    if (fieldName[0]=='f' && strcmp(fieldName, "flowLabel")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "payloadLength")==0) return base+4;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextHeader")==0) return base+5;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopLimit")==0) return base+6;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderIpAddress")==0) return base+7;
    if (fieldName[0]=='r' && strcmp(fieldName, "recverIpAddress")==0) return base+8;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+9;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *IpPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<10) ? fieldTypeStrings[field] : NULL;
}

const char *IpPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int IpPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    IpPacket *pp = (IpPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string IpPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    IpPacket *pp = (IpPacket *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getTime());
        case 1: return long2string(pp->getVersion());
        case 2: return long2string(pp->getTrafficClass());
        case 3: return long2string(pp->getFlowLabel());
        case 4: return long2string(pp->getPayloadLength());
        case 5: return long2string(pp->getNextHeader());
        case 6: return long2string(pp->getHopLimit());
        case 7: return long2string(pp->getSenderIpAddress());
        case 8: return long2string(pp->getRecverIpAddress());
        case 9: return long2string(pp->getHeaderLength());
        default: return "";
    }
}

bool IpPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    IpPacket *pp = (IpPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setTime(string2double(value)); return true;
        case 1: pp->setVersion(string2long(value)); return true;
        case 2: pp->setTrafficClass(string2long(value)); return true;
        case 3: pp->setFlowLabel(string2long(value)); return true;
        case 4: pp->setPayloadLength(string2long(value)); return true;
        case 5: pp->setNextHeader(string2long(value)); return true;
        case 6: pp->setHopLimit(string2long(value)); return true;
        case 7: pp->setSenderIpAddress(string2long(value)); return true;
        case 8: pp->setRecverIpAddress(string2long(value)); return true;
        case 9: pp->setHeaderLength(string2long(value)); return true;
        default: return false;
    }
}

const char *IpPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<10) ? fieldStructNames[field] : NULL;
}

void *IpPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    IpPacket *pp = (IpPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(IcmpPacket);

IcmpPacket::IcmpPacket(const char *name, int kind) : cPacket(name,kind)
{
    this->headerLength_var = 8;
    this->type_var = 0;
    this->code_var = 0;
    this->checksum_var = 0;
    this->others_var = 0;
}

IcmpPacket::IcmpPacket(const IcmpPacket& other) : cPacket(other)
{
    copy(other);
}

IcmpPacket::~IcmpPacket()
{
}

IcmpPacket& IcmpPacket::operator=(const IcmpPacket& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void IcmpPacket::copy(const IcmpPacket& other)
{
    this->headerLength_var = other.headerLength_var;
    this->type_var = other.type_var;
    this->code_var = other.code_var;
    this->checksum_var = other.checksum_var;
    this->others_var = other.others_var;
}

void IcmpPacket::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->headerLength_var);
    doPacking(b,this->type_var);
    doPacking(b,this->code_var);
    doPacking(b,this->checksum_var);
    doPacking(b,this->others_var);
}

void IcmpPacket::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->headerLength_var);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->code_var);
    doUnpacking(b,this->checksum_var);
    doUnpacking(b,this->others_var);
}

int IcmpPacket::getHeaderLength() const
{
    return headerLength_var;
}

void IcmpPacket::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

int IcmpPacket::getType() const
{
    return type_var;
}

void IcmpPacket::setType(int type)
{
    this->type_var = type;
}

int IcmpPacket::getCode() const
{
    return code_var;
}

void IcmpPacket::setCode(int code)
{
    this->code_var = code;
}

int IcmpPacket::getChecksum() const
{
    return checksum_var;
}

void IcmpPacket::setChecksum(int checksum)
{
    this->checksum_var = checksum;
}

int IcmpPacket::getOthers() const
{
    return others_var;
}

void IcmpPacket::setOthers(int others)
{
    this->others_var = others;
}

class IcmpPacketDescriptor : public cClassDescriptor
{
  public:
    IcmpPacketDescriptor();
    virtual ~IcmpPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(IcmpPacketDescriptor);

IcmpPacketDescriptor::IcmpPacketDescriptor() : cClassDescriptor("wsn_energy::IcmpPacket", "cPacket")
{
}

IcmpPacketDescriptor::~IcmpPacketDescriptor()
{
}

bool IcmpPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<IcmpPacket *>(obj)!=NULL;
}

const char *IcmpPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int IcmpPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int IcmpPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *IcmpPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "headerLength",
        "type",
        "code",
        "checksum",
        "others",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int IcmpPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+1;
    if (fieldName[0]=='c' && strcmp(fieldName, "code")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "checksum")==0) return base+3;
    if (fieldName[0]=='o' && strcmp(fieldName, "others")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *IcmpPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *IcmpPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int IcmpPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    IcmpPacket *pp = (IcmpPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string IcmpPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    IcmpPacket *pp = (IcmpPacket *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeaderLength());
        case 1: return long2string(pp->getType());
        case 2: return long2string(pp->getCode());
        case 3: return long2string(pp->getChecksum());
        case 4: return long2string(pp->getOthers());
        default: return "";
    }
}

bool IcmpPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    IcmpPacket *pp = (IcmpPacket *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeaderLength(string2long(value)); return true;
        case 1: pp->setType(string2long(value)); return true;
        case 2: pp->setCode(string2long(value)); return true;
        case 3: pp->setChecksum(string2long(value)); return true;
        case 4: pp->setOthers(string2long(value)); return true;
        default: return false;
    }
}

const char *IcmpPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *IcmpPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    IcmpPacket *pp = (IcmpPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(DIO);

DIO::DIO(const char *name, int kind) : cPacket(name,kind)
{
    this->dodagID_var = 0;
    this->version_var = 0;
    this->rank_var = 0;
    this->selfEnergy_var = 0;
    this->payloadLength_var = 25;
}

DIO::DIO(const DIO& other) : cPacket(other)
{
    copy(other);
}

DIO::~DIO()
{
}

DIO& DIO::operator=(const DIO& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void DIO::copy(const DIO& other)
{
    this->dodagID_var = other.dodagID_var;
    this->version_var = other.version_var;
    this->rank_var = other.rank_var;
    this->selfEnergy_var = other.selfEnergy_var;
    this->payloadLength_var = other.payloadLength_var;
}

void DIO::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->dodagID_var);
    doPacking(b,this->version_var);
    doPacking(b,this->rank_var);
    doPacking(b,this->selfEnergy_var);
    doPacking(b,this->payloadLength_var);
}

void DIO::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->dodagID_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->rank_var);
    doUnpacking(b,this->selfEnergy_var);
    doUnpacking(b,this->payloadLength_var);
}

int DIO::getDodagID() const
{
    return dodagID_var;
}

void DIO::setDodagID(int dodagID)
{
    this->dodagID_var = dodagID;
}

int DIO::getVersion() const
{
    return version_var;
}

void DIO::setVersion(int version)
{
    this->version_var = version;
}

unsigned long DIO::getRank() const
{
    return rank_var;
}

void DIO::setRank(unsigned long rank)
{
    this->rank_var = rank;
}

double DIO::getSelfEnergy() const
{
    return selfEnergy_var;
}

void DIO::setSelfEnergy(double selfEnergy)
{
    this->selfEnergy_var = selfEnergy;
}

int DIO::getPayloadLength() const
{
    return payloadLength_var;
}

void DIO::setPayloadLength(int payloadLength)
{
    this->payloadLength_var = payloadLength;
}

class DIODescriptor : public cClassDescriptor
{
  public:
    DIODescriptor();
    virtual ~DIODescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(DIODescriptor);

DIODescriptor::DIODescriptor() : cClassDescriptor("wsn_energy::DIO", "cPacket")
{
}

DIODescriptor::~DIODescriptor()
{
}

bool DIODescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DIO *>(obj)!=NULL;
}

const char *DIODescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DIODescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int DIODescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
}

const char *DIODescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "dodagID",
        "version",
        "rank",
        "selfEnergy",
        "payloadLength",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int DIODescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dodagID")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "rank")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "selfEnergy")==0) return base+3;
    if (fieldName[0]=='p' && strcmp(fieldName, "payloadLength")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DIODescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "unsigned long",
        "double",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
}

const char *DIODescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DIODescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DIO *pp = (DIO *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DIODescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DIO *pp = (DIO *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getDodagID());
        case 1: return long2string(pp->getVersion());
        case 2: return ulong2string(pp->getRank());
        case 3: return double2string(pp->getSelfEnergy());
        case 4: return long2string(pp->getPayloadLength());
        default: return "";
    }
}

bool DIODescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DIO *pp = (DIO *)object; (void)pp;
    switch (field) {
        case 0: pp->setDodagID(string2long(value)); return true;
        case 1: pp->setVersion(string2long(value)); return true;
        case 2: pp->setRank(string2ulong(value)); return true;
        case 3: pp->setSelfEnergy(string2double(value)); return true;
        case 4: pp->setPayloadLength(string2long(value)); return true;
        default: return false;
    }
}

const char *DIODescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
}

void *DIODescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DIO *pp = (DIO *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(DIS);

DIS::DIS(const char *name, int kind) : cPacket(name,kind)
{
    this->payloadLength_var = 1;
}

DIS::DIS(const DIS& other) : cPacket(other)
{
    copy(other);
}

DIS::~DIS()
{
}

DIS& DIS::operator=(const DIS& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void DIS::copy(const DIS& other)
{
    this->payloadLength_var = other.payloadLength_var;
}

void DIS::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->payloadLength_var);
}

void DIS::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->payloadLength_var);
}

int DIS::getPayloadLength() const
{
    return payloadLength_var;
}

void DIS::setPayloadLength(int payloadLength)
{
    this->payloadLength_var = payloadLength;
}

class DISDescriptor : public cClassDescriptor
{
  public:
    DISDescriptor();
    virtual ~DISDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(DISDescriptor);

DISDescriptor::DISDescriptor() : cClassDescriptor("wsn_energy::DIS", "cPacket")
{
}

DISDescriptor::~DISDescriptor()
{
}

bool DISDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<DIS *>(obj)!=NULL;
}

const char *DISDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DISDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int DISDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
}

const char *DISDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "payloadLength",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DISDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='p' && strcmp(fieldName, "payloadLength")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DISDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "int",
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
}

const char *DISDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DISDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    DIS *pp = (DIS *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DISDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    DIS *pp = (DIS *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getPayloadLength());
        default: return "";
    }
}

bool DISDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    DIS *pp = (DIS *)object; (void)pp;
    switch (field) {
        case 0: pp->setPayloadLength(string2long(value)); return true;
        default: return false;
    }
}

const char *DISDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
}

void *DISDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    DIS *pp = (DIS *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UdpPacket);

UdpPacket::UdpPacket(const char *name, int kind) : cPacket(name,kind)
{
}

UdpPacket::UdpPacket(const UdpPacket& other) : cPacket(other)
{
    copy(other);
}

UdpPacket::~UdpPacket()
{
}

UdpPacket& UdpPacket::operator=(const UdpPacket& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void UdpPacket::copy(const UdpPacket& other)
{
}

void UdpPacket::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
}

void UdpPacket::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
}

class UdpPacketDescriptor : public cClassDescriptor
{
  public:
    UdpPacketDescriptor();
    virtual ~UdpPacketDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(UdpPacketDescriptor);

UdpPacketDescriptor::UdpPacketDescriptor() : cClassDescriptor("wsn_energy::UdpPacket", "cPacket")
{
}

UdpPacketDescriptor::~UdpPacketDescriptor()
{
}

bool UdpPacketDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<UdpPacket *>(obj)!=NULL;
}

const char *UdpPacketDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UdpPacketDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 0+basedesc->getFieldCount(object) : 0;
}

unsigned int UdpPacketDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return 0;
}

const char *UdpPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

int UdpPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *UdpPacketDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

const char *UdpPacketDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int UdpPacketDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacket *pp = (UdpPacket *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string UdpPacketDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacket *pp = (UdpPacket *)object; (void)pp;
    switch (field) {
        default: return "";
    }
}

bool UdpPacketDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacket *pp = (UdpPacket *)object; (void)pp;
    switch (field) {
        default: return false;
    }
}

const char *UdpPacketDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    return NULL;
}

void *UdpPacketDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacket *pp = (UdpPacket *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Data);

Data::Data(const char *name, int kind) : cPacket(name,kind)
{
    this->time_var = 0;
    this->payloadLength_var = 0;
    this->value_var = 0;
}

Data::Data(const Data& other) : cPacket(other)
{
    copy(other);
}

Data::~Data()
{
}

Data& Data::operator=(const Data& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void Data::copy(const Data& other)
{
    this->time_var = other.time_var;
    this->payloadLength_var = other.payloadLength_var;
    this->value_var = other.value_var;
}

void Data::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->time_var);
    doPacking(b,this->payloadLength_var);
    doPacking(b,this->value_var);
}

void Data::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->time_var);
    doUnpacking(b,this->payloadLength_var);
    doUnpacking(b,this->value_var);
}

double Data::getTime() const
{
    return time_var;
}

void Data::setTime(double time)
{
    this->time_var = time;
}

int Data::getPayloadLength() const
{
    return payloadLength_var;
}

void Data::setPayloadLength(int payloadLength)
{
    this->payloadLength_var = payloadLength;
}

const char * Data::getValue() const
{
    return value_var.c_str();
}

void Data::setValue(const char * value)
{
    this->value_var = value;
}

class DataDescriptor : public cClassDescriptor
{
  public:
    DataDescriptor();
    virtual ~DataDescriptor();

    virtual bool doesSupport(cObject *obj) const;
    virtual const char *getProperty(const char *propertyname) const;
    virtual int getFieldCount(void *object) const;
    virtual const char *getFieldName(void *object, int field) const;
    virtual int findField(void *object, const char *fieldName) const;
    virtual unsigned int getFieldTypeFlags(void *object, int field) const;
    virtual const char *getFieldTypeString(void *object, int field) const;
    virtual const char *getFieldProperty(void *object, int field, const char *propertyname) const;
    virtual int getArraySize(void *object, int field) const;

    virtual std::string getFieldAsString(void *object, int field, int i) const;
    virtual bool setFieldAsString(void *object, int field, int i, const char *value) const;

    virtual const char *getFieldStructName(void *object, int field) const;
    virtual void *getFieldStructPointer(void *object, int field, int i) const;
};

Register_ClassDescriptor(DataDescriptor);

DataDescriptor::DataDescriptor() : cClassDescriptor("wsn_energy::Data", "cPacket")
{
}

DataDescriptor::~DataDescriptor()
{
}

bool DataDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<Data *>(obj)!=NULL;
}

const char *DataDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int DataDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int DataDescriptor::getFieldTypeFlags(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeFlags(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<3) ? fieldTypeFlags[field] : 0;
}

const char *DataDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "time",
        "payloadLength",
        "value",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+0;
    if (fieldName[0]=='p' && strcmp(fieldName, "payloadLength")==0) return base+1;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+2;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *DataDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "double",
        "int",
        "string",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
}

const char *DataDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldProperty(object, field, propertyname);
        field -= basedesc->getFieldCount(object);
    }
    switch (field) {
        default: return NULL;
    }
}

int DataDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    Data *pp = (Data *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string DataDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    Data *pp = (Data *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getTime());
        case 1: return long2string(pp->getPayloadLength());
        case 2: return oppstring2string(pp->getValue());
        default: return "";
    }
}

bool DataDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    Data *pp = (Data *)object; (void)pp;
    switch (field) {
        case 0: pp->setTime(string2double(value)); return true;
        case 1: pp->setPayloadLength(string2long(value)); return true;
        case 2: pp->setValue((value)); return true;
        default: return false;
    }
}

const char *DataDescriptor::getFieldStructName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
}

void *DataDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    Data *pp = (Data *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

}; // end namespace wsn_energy

