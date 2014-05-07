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
    cEnum *e = cEnum::find("wsn_energy::MANUAL_EVENT");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::MANUAL_EVENT"));
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
    e->insert(RPL_SET_UP_DELAY, "RPL_SET_UP_DELAY");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::COMMAND_NET");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::COMMAND_NET"));
    e->insert(NET_TIMER_DIO, "NET_TIMER_DIO");
    e->insert(NET_TIMER_DIS, "NET_TIMER_DIS");
    e->insert(NET_CHECK_BUFFER, "NET_CHECK_BUFFER");
    e->insert(RPL_CONSTRUCT, "RPL_CONSTRUCT");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::RESULT_NET");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::RESULT_NET"));
    e->insert(NET_DIO_SENT, "NET_DIO_SENT");
    e->insert(NET_DIS_SENT, "NET_DIS_SENT");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::IP_PACKET_NEXT_HEADER");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::IP_PACKET_NEXT_HEADER"));
    e->insert(NEXT_HEADER_UDP, "NEXT_HEADER_UDP");
    e->insert(NEXT_HEADER_TCP, "NEXT_HEADER_TCP");
    e->insert(NEXT_HEADER_ICMP, "NEXT_HEADER_ICMP");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::ICMP_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::ICMP_TYPE"));
    e->insert(ICMP_RPL, "ICMP_RPL");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::ICMP_CODE");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::ICMP_CODE"));
    e->insert(RPL_DIO_CODE, "RPL_DIO_CODE");
    e->insert(RPL_DIS_CODE, "RPL_DIS_CODE");
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
    cEnum *e = cEnum::find("wsn_energy::FRAME_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::FRAME_TYPE"));
    e->insert(FRAME_BEACON, "FRAME_BEACON");
    e->insert(FRAME_COMMAND, "FRAME_COMMAND");
    e->insert(FRAME_DATA, "FRAME_DATA");
    e->insert(FRAME_ACK, "FRAME_ACK");
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
    e->insert(RDC_CHANNEL_CHECK, "RDC_CHANNEL_CHECK");
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

int Frame::getFrameType() const
{
    return frameType_var;
}

void Frame::setFrameType(int frameType)
{
    this->frameType_var = frameType;
}

int Frame::getSecurityEnabled() const
{
    return securityEnabled_var;
}

void Frame::setSecurityEnabled(int securityEnabled)
{
    this->securityEnabled_var = securityEnabled;
}

int Frame::getFramePending() const
{
    return framePending_var;
}

void Frame::setFramePending(int framePending)
{
    this->framePending_var = framePending;
}

bool Frame::getAckRequired() const
{
    return ackRequired_var;
}

void Frame::setAckRequired(bool ackRequired)
{
    this->ackRequired_var = ackRequired;
}

bool Frame::getPanIdCompression() const
{
    return panIdCompression_var;
}

void Frame::setPanIdCompression(bool panIdCompression)
{
    this->panIdCompression_var = panIdCompression;
}

int Frame::getReserved() const
{
    return reserved_var;
}

void Frame::setReserved(int reserved)
{
    this->reserved_var = reserved;
}

int Frame::getDestinationAddressMode() const
{
    return destinationAddressMode_var;
}

void Frame::setDestinationAddressMode(int destinationAddressMode)
{
    this->destinationAddressMode_var = destinationAddressMode;
}

int Frame::getFrameVersion() const
{
    return frameVersion_var;
}

void Frame::setFrameVersion(int frameVersion)
{
    this->frameVersion_var = frameVersion;
}

int Frame::getSourceAddressMode() const
{
    return sourceAddressMode_var;
}

void Frame::setSourceAddressMode(int sourceAddressMode)
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
        "int",
        "int",
        "int",
        "bool",
        "bool",
        "int",
        "int",
        "int",
        "int",
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
        case 2: return long2string(pp->getFrameType());
        case 3: return long2string(pp->getSecurityEnabled());
        case 4: return long2string(pp->getFramePending());
        case 5: return bool2string(pp->getAckRequired());
        case 6: return bool2string(pp->getPanIdCompression());
        case 7: return long2string(pp->getReserved());
        case 8: return long2string(pp->getDestinationAddressMode());
        case 9: return long2string(pp->getFrameVersion());
        case 10: return long2string(pp->getSourceAddressMode());
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
        case 2: pp->setFrameType(string2long(value)); return true;
        case 3: pp->setSecurityEnabled(string2long(value)); return true;
        case 4: pp->setFramePending(string2long(value)); return true;
        case 5: pp->setAckRequired(string2bool(value)); return true;
        case 6: pp->setPanIdCompression(string2bool(value)); return true;
        case 7: pp->setReserved(string2long(value)); return true;
        case 8: pp->setDestinationAddressMode(string2long(value)); return true;
        case 9: pp->setFrameVersion(string2long(value)); return true;
        case 10: pp->setSourceAddressMode(string2long(value)); return true;
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

Register_Class(FrameDataStandard);

FrameDataStandard::FrameDataStandard(const char *name, int kind) : wsn_energy::Frame(name,kind)
{
    this->setHeaderLength(25);

    this->dataSequenceNumber_var = 0;
    this->sourcePanID_var = 0;
    this->destinationPanID_var = 0;
    this->sourceMacAddress_var = 0;
    this->destinationMacAddress_var = 0;
}

FrameDataStandard::FrameDataStandard(const FrameDataStandard& other) : wsn_energy::Frame(other)
{
    copy(other);
}

FrameDataStandard::~FrameDataStandard()
{
}

FrameDataStandard& FrameDataStandard::operator=(const FrameDataStandard& other)
{
    if (this==&other) return *this;
    wsn_energy::Frame::operator=(other);
    copy(other);
    return *this;
}

void FrameDataStandard::copy(const FrameDataStandard& other)
{
    this->dataSequenceNumber_var = other.dataSequenceNumber_var;
    this->sourcePanID_var = other.sourcePanID_var;
    this->destinationPanID_var = other.destinationPanID_var;
    this->sourceMacAddress_var = other.sourceMacAddress_var;
    this->destinationMacAddress_var = other.destinationMacAddress_var;
}

void FrameDataStandard::parsimPack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimPack(b);
    doPacking(b,this->dataSequenceNumber_var);
    doPacking(b,this->sourcePanID_var);
    doPacking(b,this->destinationPanID_var);
    doPacking(b,this->sourceMacAddress_var);
    doPacking(b,this->destinationMacAddress_var);
}

void FrameDataStandard::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimUnpack(b);
    doUnpacking(b,this->dataSequenceNumber_var);
    doUnpacking(b,this->sourcePanID_var);
    doUnpacking(b,this->destinationPanID_var);
    doUnpacking(b,this->sourceMacAddress_var);
    doUnpacking(b,this->destinationMacAddress_var);
}

int FrameDataStandard::getDataSequenceNumber() const
{
    return dataSequenceNumber_var;
}

void FrameDataStandard::setDataSequenceNumber(int dataSequenceNumber)
{
    this->dataSequenceNumber_var = dataSequenceNumber;
}

int FrameDataStandard::getSourcePanID() const
{
    return sourcePanID_var;
}

void FrameDataStandard::setSourcePanID(int sourcePanID)
{
    this->sourcePanID_var = sourcePanID;
}

int FrameDataStandard::getDestinationPanID() const
{
    return destinationPanID_var;
}

void FrameDataStandard::setDestinationPanID(int destinationPanID)
{
    this->destinationPanID_var = destinationPanID;
}

int FrameDataStandard::getSourceMacAddress() const
{
    return sourceMacAddress_var;
}

void FrameDataStandard::setSourceMacAddress(int sourceMacAddress)
{
    this->sourceMacAddress_var = sourceMacAddress;
}

int FrameDataStandard::getDestinationMacAddress() const
{
    return destinationMacAddress_var;
}

void FrameDataStandard::setDestinationMacAddress(int destinationMacAddress)
{
    this->destinationMacAddress_var = destinationMacAddress;
}

class FrameDataStandardDescriptor : public cClassDescriptor
{
  public:
    FrameDataStandardDescriptor();
    virtual ~FrameDataStandardDescriptor();

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

Register_ClassDescriptor(FrameDataStandardDescriptor);

FrameDataStandardDescriptor::FrameDataStandardDescriptor() : cClassDescriptor("wsn_energy::FrameDataStandard", "wsn_energy::Frame")
{
}

FrameDataStandardDescriptor::~FrameDataStandardDescriptor()
{
}

bool FrameDataStandardDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FrameDataStandard *>(obj)!=NULL;
}

const char *FrameDataStandardDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameDataStandardDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int FrameDataStandardDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *FrameDataStandardDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "dataSequenceNumber",
        "sourcePanID",
        "destinationPanID",
        "sourceMacAddress",
        "destinationMacAddress",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int FrameDataStandardDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSequenceNumber")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePanID")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPanID")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceMacAddress")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationMacAddress")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameDataStandardDescriptor::getFieldTypeString(void *object, int field) const
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

const char *FrameDataStandardDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int FrameDataStandardDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FrameDataStandard *pp = (FrameDataStandard *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FrameDataStandardDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FrameDataStandard *pp = (FrameDataStandard *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getDataSequenceNumber());
        case 1: return long2string(pp->getSourcePanID());
        case 2: return long2string(pp->getDestinationPanID());
        case 3: return long2string(pp->getSourceMacAddress());
        case 4: return long2string(pp->getDestinationMacAddress());
        default: return "";
    }
}

bool FrameDataStandardDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FrameDataStandard *pp = (FrameDataStandard *)object; (void)pp;
    switch (field) {
        case 0: pp->setDataSequenceNumber(string2long(value)); return true;
        case 1: pp->setSourcePanID(string2long(value)); return true;
        case 2: pp->setDestinationPanID(string2long(value)); return true;
        case 3: pp->setSourceMacAddress(string2long(value)); return true;
        case 4: pp->setDestinationMacAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *FrameDataStandardDescriptor::getFieldStructName(void *object, int field) const
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

void *FrameDataStandardDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FrameDataStandard *pp = (FrameDataStandard *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FrameDataCompressed);

FrameDataCompressed::FrameDataCompressed(const char *name, int kind) : wsn_energy::Frame(name,kind)
{
    this->headerLength_var = 32;
}

FrameDataCompressed::FrameDataCompressed(const FrameDataCompressed& other) : wsn_energy::Frame(other)
{
    copy(other);
}

FrameDataCompressed::~FrameDataCompressed()
{
}

FrameDataCompressed& FrameDataCompressed::operator=(const FrameDataCompressed& other)
{
    if (this==&other) return *this;
    wsn_energy::Frame::operator=(other);
    copy(other);
    return *this;
}

void FrameDataCompressed::copy(const FrameDataCompressed& other)
{
    this->headerLength_var = other.headerLength_var;
}

void FrameDataCompressed::parsimPack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimPack(b);
    doPacking(b,this->headerLength_var);
}

void FrameDataCompressed::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimUnpack(b);
    doUnpacking(b,this->headerLength_var);
}

int FrameDataCompressed::getHeaderLength() const
{
    return headerLength_var;
}

void FrameDataCompressed::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

class FrameDataCompressedDescriptor : public cClassDescriptor
{
  public:
    FrameDataCompressedDescriptor();
    virtual ~FrameDataCompressedDescriptor();

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

Register_ClassDescriptor(FrameDataCompressedDescriptor);

FrameDataCompressedDescriptor::FrameDataCompressedDescriptor() : cClassDescriptor("wsn_energy::FrameDataCompressed", "wsn_energy::Frame")
{
}

FrameDataCompressedDescriptor::~FrameDataCompressedDescriptor()
{
}

bool FrameDataCompressedDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FrameDataCompressed *>(obj)!=NULL;
}

const char *FrameDataCompressedDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameDataCompressedDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int FrameDataCompressedDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *FrameDataCompressedDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "headerLength",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int FrameDataCompressedDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameDataCompressedDescriptor::getFieldTypeString(void *object, int field) const
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

const char *FrameDataCompressedDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int FrameDataCompressedDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FrameDataCompressed *pp = (FrameDataCompressed *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FrameDataCompressedDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FrameDataCompressed *pp = (FrameDataCompressed *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeaderLength());
        default: return "";
    }
}

bool FrameDataCompressedDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FrameDataCompressed *pp = (FrameDataCompressed *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeaderLength(string2long(value)); return true;
        default: return false;
    }
}

const char *FrameDataCompressedDescriptor::getFieldStructName(void *object, int field) const
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

void *FrameDataCompressedDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FrameDataCompressed *pp = (FrameDataCompressed *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FrameACK);

FrameACK::FrameACK(const char *name, int kind) : wsn_energy::Frame(name,kind)
{
    this->setHeaderLength(3);

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
    this->dataSequenceNumber_var = other.dataSequenceNumber_var;
}

void FrameACK::parsimPack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimPack(b);
    doPacking(b,this->dataSequenceNumber_var);
}

void FrameACK::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimUnpack(b);
    doUnpacking(b,this->dataSequenceNumber_var);
}

int FrameACK::getDataSequenceNumber() const
{
    return dataSequenceNumber_var;
}

void FrameACK::setDataSequenceNumber(int dataSequenceNumber)
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
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
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
    };
    return (field>=0 && field<1) ? fieldTypeFlags[field] : 0;
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
        "dataSequenceNumber",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int FrameACKDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSequenceNumber")==0) return base+0;
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
    };
    return (field>=0 && field<1) ? fieldTypeStrings[field] : NULL;
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
        case 0: return long2string(pp->getDataSequenceNumber());
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
        case 0: pp->setDataSequenceNumber(string2long(value)); return true;
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
    };
    return (field>=0 && field<1) ? fieldStructNames[field] : NULL;
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
    this->setHeaderLength(26);

    this->beaconSequenceNumber_var = 0;
    this->sourcePanID_var = 0;
    this->destinationPanID_var = 0;
    this->sourceMacAddress_var = 0;
    this->destinationMacAddress_var = 0;
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
    this->beaconSequenceNumber_var = other.beaconSequenceNumber_var;
    this->sourcePanID_var = other.sourcePanID_var;
    this->destinationPanID_var = other.destinationPanID_var;
    this->sourceMacAddress_var = other.sourceMacAddress_var;
    this->destinationMacAddress_var = other.destinationMacAddress_var;
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
    doPacking(b,this->beaconSequenceNumber_var);
    doPacking(b,this->sourcePanID_var);
    doPacking(b,this->destinationPanID_var);
    doPacking(b,this->sourceMacAddress_var);
    doPacking(b,this->destinationMacAddress_var);
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
    doUnpacking(b,this->beaconSequenceNumber_var);
    doUnpacking(b,this->sourcePanID_var);
    doUnpacking(b,this->destinationPanID_var);
    doUnpacking(b,this->sourceMacAddress_var);
    doUnpacking(b,this->destinationMacAddress_var);
    doUnpacking(b,this->beaconOrder_var);
    doUnpacking(b,this->superFrameOrder_var);
    doUnpacking(b,this->finalCAPslot_var);
    doUnpacking(b,this->batteryLifeExtension_var);
    doUnpacking(b,this->reserved_var);
    doUnpacking(b,this->PANcoordinator_var);
    doUnpacking(b,this->associationPermit_var);
}

int FrameBeacon::getBeaconSequenceNumber() const
{
    return beaconSequenceNumber_var;
}

void FrameBeacon::setBeaconSequenceNumber(int beaconSequenceNumber)
{
    this->beaconSequenceNumber_var = beaconSequenceNumber;
}

int FrameBeacon::getSourcePanID() const
{
    return sourcePanID_var;
}

void FrameBeacon::setSourcePanID(int sourcePanID)
{
    this->sourcePanID_var = sourcePanID;
}

int FrameBeacon::getDestinationPanID() const
{
    return destinationPanID_var;
}

void FrameBeacon::setDestinationPanID(int destinationPanID)
{
    this->destinationPanID_var = destinationPanID;
}

int FrameBeacon::getSourceMacAddress() const
{
    return sourceMacAddress_var;
}

void FrameBeacon::setSourceMacAddress(int sourceMacAddress)
{
    this->sourceMacAddress_var = sourceMacAddress;
}

int FrameBeacon::getDestinationMacAddress() const
{
    return destinationMacAddress_var;
}

void FrameBeacon::setDestinationMacAddress(int destinationMacAddress)
{
    this->destinationMacAddress_var = destinationMacAddress;
}

int FrameBeacon::getBeaconOrder() const
{
    return beaconOrder_var;
}

void FrameBeacon::setBeaconOrder(int beaconOrder)
{
    this->beaconOrder_var = beaconOrder;
}

int FrameBeacon::getSuperFrameOrder() const
{
    return superFrameOrder_var;
}

void FrameBeacon::setSuperFrameOrder(int superFrameOrder)
{
    this->superFrameOrder_var = superFrameOrder;
}

int FrameBeacon::getFinalCAPslot() const
{
    return finalCAPslot_var;
}

void FrameBeacon::setFinalCAPslot(int finalCAPslot)
{
    this->finalCAPslot_var = finalCAPslot;
}

int FrameBeacon::getBatteryLifeExtension() const
{
    return batteryLifeExtension_var;
}

void FrameBeacon::setBatteryLifeExtension(int batteryLifeExtension)
{
    this->batteryLifeExtension_var = batteryLifeExtension;
}

int FrameBeacon::getReserved() const
{
    return reserved_var;
}

void FrameBeacon::setReserved(int reserved)
{
    this->reserved_var = reserved;
}

int FrameBeacon::getPANcoordinator() const
{
    return PANcoordinator_var;
}

void FrameBeacon::setPANcoordinator(int PANcoordinator)
{
    this->PANcoordinator_var = PANcoordinator;
}

int FrameBeacon::getAssociationPermit() const
{
    return associationPermit_var;
}

void FrameBeacon::setAssociationPermit(int associationPermit)
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
    return basedesc ? 12+basedesc->getFieldCount(object) : 12;
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

const char *FrameBeaconDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "beaconSequenceNumber",
        "sourcePanID",
        "destinationPanID",
        "sourceMacAddress",
        "destinationMacAddress",
        "beaconOrder",
        "superFrameOrder",
        "finalCAPslot",
        "batteryLifeExtension",
        "reserved",
        "PANcoordinator",
        "associationPermit",
    };
    return (field>=0 && field<12) ? fieldNames[field] : NULL;
}

int FrameBeaconDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconSequenceNumber")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePanID")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPanID")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceMacAddress")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationMacAddress")==0) return base+4;
    if (fieldName[0]=='b' && strcmp(fieldName, "beaconOrder")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "superFrameOrder")==0) return base+6;
    if (fieldName[0]=='f' && strcmp(fieldName, "finalCAPslot")==0) return base+7;
    if (fieldName[0]=='b' && strcmp(fieldName, "batteryLifeExtension")==0) return base+8;
    if (fieldName[0]=='r' && strcmp(fieldName, "reserved")==0) return base+9;
    if (fieldName[0]=='P' && strcmp(fieldName, "PANcoordinator")==0) return base+10;
    if (fieldName[0]=='a' && strcmp(fieldName, "associationPermit")==0) return base+11;
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
        "int",
        "int",
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
    return (field>=0 && field<12) ? fieldTypeStrings[field] : NULL;
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
        case 0: return long2string(pp->getBeaconSequenceNumber());
        case 1: return long2string(pp->getSourcePanID());
        case 2: return long2string(pp->getDestinationPanID());
        case 3: return long2string(pp->getSourceMacAddress());
        case 4: return long2string(pp->getDestinationMacAddress());
        case 5: return long2string(pp->getBeaconOrder());
        case 6: return long2string(pp->getSuperFrameOrder());
        case 7: return long2string(pp->getFinalCAPslot());
        case 8: return long2string(pp->getBatteryLifeExtension());
        case 9: return long2string(pp->getReserved());
        case 10: return long2string(pp->getPANcoordinator());
        case 11: return long2string(pp->getAssociationPermit());
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
        case 0: pp->setBeaconSequenceNumber(string2long(value)); return true;
        case 1: pp->setSourcePanID(string2long(value)); return true;
        case 2: pp->setDestinationPanID(string2long(value)); return true;
        case 3: pp->setSourceMacAddress(string2long(value)); return true;
        case 4: pp->setDestinationMacAddress(string2long(value)); return true;
        case 5: pp->setBeaconOrder(string2long(value)); return true;
        case 6: pp->setSuperFrameOrder(string2long(value)); return true;
        case 7: pp->setFinalCAPslot(string2long(value)); return true;
        case 8: pp->setBatteryLifeExtension(string2long(value)); return true;
        case 9: pp->setReserved(string2long(value)); return true;
        case 10: pp->setPANcoordinator(string2long(value)); return true;
        case 11: pp->setAssociationPermit(string2long(value)); return true;
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
    };
    return (field>=0 && field<12) ? fieldStructNames[field] : NULL;
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
    this->setHeaderLength(25);

    this->dataSequenceNumber_var = 0;
    this->sourcePanID_var = 0;
    this->destinationPanID_var = 0;
    this->sourceMacAddress_var = 0;
    this->destinationMacAddress_var = 0;
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
    this->dataSequenceNumber_var = other.dataSequenceNumber_var;
    this->sourcePanID_var = other.sourcePanID_var;
    this->destinationPanID_var = other.destinationPanID_var;
    this->sourceMacAddress_var = other.sourceMacAddress_var;
    this->destinationMacAddress_var = other.destinationMacAddress_var;
    this->commandType_var = other.commandType_var;
}

void FrameCommand::parsimPack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimPack(b);
    doPacking(b,this->dataSequenceNumber_var);
    doPacking(b,this->sourcePanID_var);
    doPacking(b,this->destinationPanID_var);
    doPacking(b,this->sourceMacAddress_var);
    doPacking(b,this->destinationMacAddress_var);
    doPacking(b,this->commandType_var);
}

void FrameCommand::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::Frame::parsimUnpack(b);
    doUnpacking(b,this->dataSequenceNumber_var);
    doUnpacking(b,this->sourcePanID_var);
    doUnpacking(b,this->destinationPanID_var);
    doUnpacking(b,this->sourceMacAddress_var);
    doUnpacking(b,this->destinationMacAddress_var);
    doUnpacking(b,this->commandType_var);
}

int FrameCommand::getDataSequenceNumber() const
{
    return dataSequenceNumber_var;
}

void FrameCommand::setDataSequenceNumber(int dataSequenceNumber)
{
    this->dataSequenceNumber_var = dataSequenceNumber;
}

int FrameCommand::getSourcePanID() const
{
    return sourcePanID_var;
}

void FrameCommand::setSourcePanID(int sourcePanID)
{
    this->sourcePanID_var = sourcePanID;
}

int FrameCommand::getDestinationPanID() const
{
    return destinationPanID_var;
}

void FrameCommand::setDestinationPanID(int destinationPanID)
{
    this->destinationPanID_var = destinationPanID;
}

int FrameCommand::getSourceMacAddress() const
{
    return sourceMacAddress_var;
}

void FrameCommand::setSourceMacAddress(int sourceMacAddress)
{
    this->sourceMacAddress_var = sourceMacAddress;
}

int FrameCommand::getDestinationMacAddress() const
{
    return destinationMacAddress_var;
}

void FrameCommand::setDestinationMacAddress(int destinationMacAddress)
{
    this->destinationMacAddress_var = destinationMacAddress;
}

int FrameCommand::getCommandType() const
{
    return commandType_var;
}

void FrameCommand::setCommandType(int commandType)
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
    return basedesc ? 6+basedesc->getFieldCount(object) : 6;
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<6) ? fieldTypeFlags[field] : 0;
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
        "dataSequenceNumber",
        "sourcePanID",
        "destinationPanID",
        "sourceMacAddress",
        "destinationMacAddress",
        "commandType",
    };
    return (field>=0 && field<6) ? fieldNames[field] : NULL;
}

int FrameCommandDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dataSequenceNumber")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePanID")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPanID")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceMacAddress")==0) return base+3;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationMacAddress")==0) return base+4;
    if (fieldName[0]=='c' && strcmp(fieldName, "commandType")==0) return base+5;
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
        "int",
        "int",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<6) ? fieldTypeStrings[field] : NULL;
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
        case 0: return long2string(pp->getDataSequenceNumber());
        case 1: return long2string(pp->getSourcePanID());
        case 2: return long2string(pp->getDestinationPanID());
        case 3: return long2string(pp->getSourceMacAddress());
        case 4: return long2string(pp->getDestinationMacAddress());
        case 5: return long2string(pp->getCommandType());
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
        case 0: pp->setDataSequenceNumber(string2long(value)); return true;
        case 1: pp->setSourcePanID(string2long(value)); return true;
        case 2: pp->setDestinationPanID(string2long(value)); return true;
        case 3: pp->setSourceMacAddress(string2long(value)); return true;
        case 4: pp->setDestinationMacAddress(string2long(value)); return true;
        case 5: pp->setCommandType(string2long(value)); return true;
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
    };
    return (field>=0 && field<6) ? fieldStructNames[field] : NULL;
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

Register_Class(IpPacketInterface);

IpPacketInterface::IpPacketInterface(const char *name, int kind) : cPacket(name,kind)
{
    this->time_var = 0;
    this->headerLength_var = 0;
}

IpPacketInterface::IpPacketInterface(const IpPacketInterface& other) : cPacket(other)
{
    copy(other);
}

IpPacketInterface::~IpPacketInterface()
{
}

IpPacketInterface& IpPacketInterface::operator=(const IpPacketInterface& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void IpPacketInterface::copy(const IpPacketInterface& other)
{
    this->time_var = other.time_var;
    this->headerLength_var = other.headerLength_var;
}

void IpPacketInterface::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->time_var);
    doPacking(b,this->headerLength_var);
}

void IpPacketInterface::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->time_var);
    doUnpacking(b,this->headerLength_var);
}

double IpPacketInterface::getTime() const
{
    return time_var;
}

void IpPacketInterface::setTime(double time)
{
    this->time_var = time;
}

int IpPacketInterface::getHeaderLength() const
{
    return headerLength_var;
}

void IpPacketInterface::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

class IpPacketInterfaceDescriptor : public cClassDescriptor
{
  public:
    IpPacketInterfaceDescriptor();
    virtual ~IpPacketInterfaceDescriptor();

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

Register_ClassDescriptor(IpPacketInterfaceDescriptor);

IpPacketInterfaceDescriptor::IpPacketInterfaceDescriptor() : cClassDescriptor("wsn_energy::IpPacketInterface", "cPacket")
{
}

IpPacketInterfaceDescriptor::~IpPacketInterfaceDescriptor()
{
}

bool IpPacketInterfaceDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<IpPacketInterface *>(obj)!=NULL;
}

const char *IpPacketInterfaceDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int IpPacketInterfaceDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 2+basedesc->getFieldCount(object) : 2;
}

unsigned int IpPacketInterfaceDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *IpPacketInterfaceDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "time",
        "headerLength",
    };
    return (field>=0 && field<2) ? fieldNames[field] : NULL;
}

int IpPacketInterfaceDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+1;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *IpPacketInterfaceDescriptor::getFieldTypeString(void *object, int field) const
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
    };
    return (field>=0 && field<2) ? fieldTypeStrings[field] : NULL;
}

const char *IpPacketInterfaceDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int IpPacketInterfaceDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketInterface *pp = (IpPacketInterface *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string IpPacketInterfaceDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketInterface *pp = (IpPacketInterface *)object; (void)pp;
    switch (field) {
        case 0: return double2string(pp->getTime());
        case 1: return long2string(pp->getHeaderLength());
        default: return "";
    }
}

bool IpPacketInterfaceDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketInterface *pp = (IpPacketInterface *)object; (void)pp;
    switch (field) {
        case 0: pp->setTime(string2double(value)); return true;
        case 1: pp->setHeaderLength(string2long(value)); return true;
        default: return false;
    }
}

const char *IpPacketInterfaceDescriptor::getFieldStructName(void *object, int field) const
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

void *IpPacketInterfaceDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketInterface *pp = (IpPacketInterface *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(IpPacketStandard);

IpPacketStandard::IpPacketStandard(const char *name, int kind) : wsn_energy::IpPacketInterface(name,kind)
{
    this->setHeaderLength(40);

    this->version_var = 0;
    this->trafficClass_var = 0;
    this->flowLabel_var = 0;
    this->payloadLength_var = 0;
    this->nextHeader_var = 0;
    this->hopLimit_var = 0;
    this->sourceIpAddress_var = 0;
    this->destinationIpAddress_var = 0;
}

IpPacketStandard::IpPacketStandard(const IpPacketStandard& other) : wsn_energy::IpPacketInterface(other)
{
    copy(other);
}

IpPacketStandard::~IpPacketStandard()
{
}

IpPacketStandard& IpPacketStandard::operator=(const IpPacketStandard& other)
{
    if (this==&other) return *this;
    wsn_energy::IpPacketInterface::operator=(other);
    copy(other);
    return *this;
}

void IpPacketStandard::copy(const IpPacketStandard& other)
{
    this->version_var = other.version_var;
    this->trafficClass_var = other.trafficClass_var;
    this->flowLabel_var = other.flowLabel_var;
    this->payloadLength_var = other.payloadLength_var;
    this->nextHeader_var = other.nextHeader_var;
    this->hopLimit_var = other.hopLimit_var;
    this->sourceIpAddress_var = other.sourceIpAddress_var;
    this->destinationIpAddress_var = other.destinationIpAddress_var;
}

void IpPacketStandard::parsimPack(cCommBuffer *b)
{
    wsn_energy::IpPacketInterface::parsimPack(b);
    doPacking(b,this->version_var);
    doPacking(b,this->trafficClass_var);
    doPacking(b,this->flowLabel_var);
    doPacking(b,this->payloadLength_var);
    doPacking(b,this->nextHeader_var);
    doPacking(b,this->hopLimit_var);
    doPacking(b,this->sourceIpAddress_var);
    doPacking(b,this->destinationIpAddress_var);
}

void IpPacketStandard::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::IpPacketInterface::parsimUnpack(b);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->trafficClass_var);
    doUnpacking(b,this->flowLabel_var);
    doUnpacking(b,this->payloadLength_var);
    doUnpacking(b,this->nextHeader_var);
    doUnpacking(b,this->hopLimit_var);
    doUnpacking(b,this->sourceIpAddress_var);
    doUnpacking(b,this->destinationIpAddress_var);
}

int IpPacketStandard::getVersion() const
{
    return version_var;
}

void IpPacketStandard::setVersion(int version)
{
    this->version_var = version;
}

int IpPacketStandard::getTrafficClass() const
{
    return trafficClass_var;
}

void IpPacketStandard::setTrafficClass(int trafficClass)
{
    this->trafficClass_var = trafficClass;
}

int IpPacketStandard::getFlowLabel() const
{
    return flowLabel_var;
}

void IpPacketStandard::setFlowLabel(int flowLabel)
{
    this->flowLabel_var = flowLabel;
}

int IpPacketStandard::getPayloadLength() const
{
    return payloadLength_var;
}

void IpPacketStandard::setPayloadLength(int payloadLength)
{
    this->payloadLength_var = payloadLength;
}

int IpPacketStandard::getNextHeader() const
{
    return nextHeader_var;
}

void IpPacketStandard::setNextHeader(int nextHeader)
{
    this->nextHeader_var = nextHeader;
}

int IpPacketStandard::getHopLimit() const
{
    return hopLimit_var;
}

void IpPacketStandard::setHopLimit(int hopLimit)
{
    this->hopLimit_var = hopLimit;
}

int IpPacketStandard::getSourceIpAddress() const
{
    return sourceIpAddress_var;
}

void IpPacketStandard::setSourceIpAddress(int sourceIpAddress)
{
    this->sourceIpAddress_var = sourceIpAddress;
}

int IpPacketStandard::getDestinationIpAddress() const
{
    return destinationIpAddress_var;
}

void IpPacketStandard::setDestinationIpAddress(int destinationIpAddress)
{
    this->destinationIpAddress_var = destinationIpAddress;
}

class IpPacketStandardDescriptor : public cClassDescriptor
{
  public:
    IpPacketStandardDescriptor();
    virtual ~IpPacketStandardDescriptor();

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

Register_ClassDescriptor(IpPacketStandardDescriptor);

IpPacketStandardDescriptor::IpPacketStandardDescriptor() : cClassDescriptor("wsn_energy::IpPacketStandard", "wsn_energy::IpPacketInterface")
{
}

IpPacketStandardDescriptor::~IpPacketStandardDescriptor()
{
}

bool IpPacketStandardDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<IpPacketStandard *>(obj)!=NULL;
}

const char *IpPacketStandardDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int IpPacketStandardDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 8+basedesc->getFieldCount(object) : 8;
}

unsigned int IpPacketStandardDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<8) ? fieldTypeFlags[field] : 0;
}

const char *IpPacketStandardDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "version",
        "trafficClass",
        "flowLabel",
        "payloadLength",
        "nextHeader",
        "hopLimit",
        "sourceIpAddress",
        "destinationIpAddress",
    };
    return (field>=0 && field<8) ? fieldNames[field] : NULL;
}

int IpPacketStandardDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "trafficClass")==0) return base+1;
    if (fieldName[0]=='f' && strcmp(fieldName, "flowLabel")==0) return base+2;
    if (fieldName[0]=='p' && strcmp(fieldName, "payloadLength")==0) return base+3;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextHeader")==0) return base+4;
    if (fieldName[0]=='h' && strcmp(fieldName, "hopLimit")==0) return base+5;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceIpAddress")==0) return base+6;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationIpAddress")==0) return base+7;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *IpPacketStandardDescriptor::getFieldTypeString(void *object, int field) const
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
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<8) ? fieldTypeStrings[field] : NULL;
}

const char *IpPacketStandardDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int IpPacketStandardDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketStandard *pp = (IpPacketStandard *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string IpPacketStandardDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketStandard *pp = (IpPacketStandard *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getVersion());
        case 1: return long2string(pp->getTrafficClass());
        case 2: return long2string(pp->getFlowLabel());
        case 3: return long2string(pp->getPayloadLength());
        case 4: return long2string(pp->getNextHeader());
        case 5: return long2string(pp->getHopLimit());
        case 6: return long2string(pp->getSourceIpAddress());
        case 7: return long2string(pp->getDestinationIpAddress());
        default: return "";
    }
}

bool IpPacketStandardDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketStandard *pp = (IpPacketStandard *)object; (void)pp;
    switch (field) {
        case 0: pp->setVersion(string2long(value)); return true;
        case 1: pp->setTrafficClass(string2long(value)); return true;
        case 2: pp->setFlowLabel(string2long(value)); return true;
        case 3: pp->setPayloadLength(string2long(value)); return true;
        case 4: pp->setNextHeader(string2long(value)); return true;
        case 5: pp->setHopLimit(string2long(value)); return true;
        case 6: pp->setSourceIpAddress(string2long(value)); return true;
        case 7: pp->setDestinationIpAddress(string2long(value)); return true;
        default: return false;
    }
}

const char *IpPacketStandardDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<8) ? fieldStructNames[field] : NULL;
}

void *IpPacketStandardDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketStandard *pp = (IpPacketStandard *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(IpPacketCompressed);

IpPacketCompressed::IpPacketCompressed(const char *name, int kind) : wsn_energy::IpPacketInterface(name,kind)
{
    this->setHeaderLength(2);

    this->sourceIPAddress_var = 0;
    this->destinationIPAddress_var = 0;
    this->trafficClassAndFlowLabel_var = 0;
    this->nextHeader_var = 0;
    this->hc2encoding_var = 0;
}

IpPacketCompressed::IpPacketCompressed(const IpPacketCompressed& other) : wsn_energy::IpPacketInterface(other)
{
    copy(other);
}

IpPacketCompressed::~IpPacketCompressed()
{
}

IpPacketCompressed& IpPacketCompressed::operator=(const IpPacketCompressed& other)
{
    if (this==&other) return *this;
    wsn_energy::IpPacketInterface::operator=(other);
    copy(other);
    return *this;
}

void IpPacketCompressed::copy(const IpPacketCompressed& other)
{
    this->sourceIPAddress_var = other.sourceIPAddress_var;
    this->destinationIPAddress_var = other.destinationIPAddress_var;
    this->trafficClassAndFlowLabel_var = other.trafficClassAndFlowLabel_var;
    this->nextHeader_var = other.nextHeader_var;
    this->hc2encoding_var = other.hc2encoding_var;
}

void IpPacketCompressed::parsimPack(cCommBuffer *b)
{
    wsn_energy::IpPacketInterface::parsimPack(b);
    doPacking(b,this->sourceIPAddress_var);
    doPacking(b,this->destinationIPAddress_var);
    doPacking(b,this->trafficClassAndFlowLabel_var);
    doPacking(b,this->nextHeader_var);
    doPacking(b,this->hc2encoding_var);
}

void IpPacketCompressed::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::IpPacketInterface::parsimUnpack(b);
    doUnpacking(b,this->sourceIPAddress_var);
    doUnpacking(b,this->destinationIPAddress_var);
    doUnpacking(b,this->trafficClassAndFlowLabel_var);
    doUnpacking(b,this->nextHeader_var);
    doUnpacking(b,this->hc2encoding_var);
}

int IpPacketCompressed::getSourceIPAddress() const
{
    return sourceIPAddress_var;
}

void IpPacketCompressed::setSourceIPAddress(int sourceIPAddress)
{
    this->sourceIPAddress_var = sourceIPAddress;
}

int IpPacketCompressed::getDestinationIPAddress() const
{
    return destinationIPAddress_var;
}

void IpPacketCompressed::setDestinationIPAddress(int destinationIPAddress)
{
    this->destinationIPAddress_var = destinationIPAddress;
}

int IpPacketCompressed::getTrafficClassAndFlowLabel() const
{
    return trafficClassAndFlowLabel_var;
}

void IpPacketCompressed::setTrafficClassAndFlowLabel(int trafficClassAndFlowLabel)
{
    this->trafficClassAndFlowLabel_var = trafficClassAndFlowLabel;
}

int IpPacketCompressed::getNextHeader() const
{
    return nextHeader_var;
}

void IpPacketCompressed::setNextHeader(int nextHeader)
{
    this->nextHeader_var = nextHeader;
}

int IpPacketCompressed::getHc2encoding() const
{
    return hc2encoding_var;
}

void IpPacketCompressed::setHc2encoding(int hc2encoding)
{
    this->hc2encoding_var = hc2encoding;
}

class IpPacketCompressedDescriptor : public cClassDescriptor
{
  public:
    IpPacketCompressedDescriptor();
    virtual ~IpPacketCompressedDescriptor();

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

Register_ClassDescriptor(IpPacketCompressedDescriptor);

IpPacketCompressedDescriptor::IpPacketCompressedDescriptor() : cClassDescriptor("wsn_energy::IpPacketCompressed", "wsn_energy::IpPacketInterface")
{
}

IpPacketCompressedDescriptor::~IpPacketCompressedDescriptor()
{
}

bool IpPacketCompressedDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<IpPacketCompressed *>(obj)!=NULL;
}

const char *IpPacketCompressedDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int IpPacketCompressedDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int IpPacketCompressedDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *IpPacketCompressedDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "sourceIPAddress",
        "destinationIPAddress",
        "trafficClassAndFlowLabel",
        "nextHeader",
        "hc2encoding",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int IpPacketCompressedDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceIPAddress")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationIPAddress")==0) return base+1;
    if (fieldName[0]=='t' && strcmp(fieldName, "trafficClassAndFlowLabel")==0) return base+2;
    if (fieldName[0]=='n' && strcmp(fieldName, "nextHeader")==0) return base+3;
    if (fieldName[0]=='h' && strcmp(fieldName, "hc2encoding")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *IpPacketCompressedDescriptor::getFieldTypeString(void *object, int field) const
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

const char *IpPacketCompressedDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int IpPacketCompressedDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketCompressed *pp = (IpPacketCompressed *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string IpPacketCompressedDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketCompressed *pp = (IpPacketCompressed *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSourceIPAddress());
        case 1: return long2string(pp->getDestinationIPAddress());
        case 2: return long2string(pp->getTrafficClassAndFlowLabel());
        case 3: return long2string(pp->getNextHeader());
        case 4: return long2string(pp->getHc2encoding());
        default: return "";
    }
}

bool IpPacketCompressedDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketCompressed *pp = (IpPacketCompressed *)object; (void)pp;
    switch (field) {
        case 0: pp->setSourceIPAddress(string2long(value)); return true;
        case 1: pp->setDestinationIPAddress(string2long(value)); return true;
        case 2: pp->setTrafficClassAndFlowLabel(string2long(value)); return true;
        case 3: pp->setNextHeader(string2long(value)); return true;
        case 4: pp->setHc2encoding(string2long(value)); return true;
        default: return false;
    }
}

const char *IpPacketCompressedDescriptor::getFieldStructName(void *object, int field) const
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

void *IpPacketCompressedDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    IpPacketCompressed *pp = (IpPacketCompressed *)object; (void)pp;
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

Register_Class(UdpPacketInterface);

UdpPacketInterface::UdpPacketInterface(const char *name, int kind) : cPacket(name,kind)
{
    this->headerLength_var = 0;
}

UdpPacketInterface::UdpPacketInterface(const UdpPacketInterface& other) : cPacket(other)
{
    copy(other);
}

UdpPacketInterface::~UdpPacketInterface()
{
}

UdpPacketInterface& UdpPacketInterface::operator=(const UdpPacketInterface& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void UdpPacketInterface::copy(const UdpPacketInterface& other)
{
    this->headerLength_var = other.headerLength_var;
}

void UdpPacketInterface::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->headerLength_var);
}

void UdpPacketInterface::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->headerLength_var);
}

int UdpPacketInterface::getHeaderLength() const
{
    return headerLength_var;
}

void UdpPacketInterface::setHeaderLength(int headerLength)
{
    this->headerLength_var = headerLength;
}

class UdpPacketInterfaceDescriptor : public cClassDescriptor
{
  public:
    UdpPacketInterfaceDescriptor();
    virtual ~UdpPacketInterfaceDescriptor();

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

Register_ClassDescriptor(UdpPacketInterfaceDescriptor);

UdpPacketInterfaceDescriptor::UdpPacketInterfaceDescriptor() : cClassDescriptor("wsn_energy::UdpPacketInterface", "cPacket")
{
}

UdpPacketInterfaceDescriptor::~UdpPacketInterfaceDescriptor()
{
}

bool UdpPacketInterfaceDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<UdpPacketInterface *>(obj)!=NULL;
}

const char *UdpPacketInterfaceDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UdpPacketInterfaceDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int UdpPacketInterfaceDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *UdpPacketInterfaceDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "headerLength",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int UdpPacketInterfaceDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='h' && strcmp(fieldName, "headerLength")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *UdpPacketInterfaceDescriptor::getFieldTypeString(void *object, int field) const
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

const char *UdpPacketInterfaceDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int UdpPacketInterfaceDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketInterface *pp = (UdpPacketInterface *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string UdpPacketInterfaceDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketInterface *pp = (UdpPacketInterface *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getHeaderLength());
        default: return "";
    }
}

bool UdpPacketInterfaceDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketInterface *pp = (UdpPacketInterface *)object; (void)pp;
    switch (field) {
        case 0: pp->setHeaderLength(string2long(value)); return true;
        default: return false;
    }
}

const char *UdpPacketInterfaceDescriptor::getFieldStructName(void *object, int field) const
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

void *UdpPacketInterfaceDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketInterface *pp = (UdpPacketInterface *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UdpPacketStandard);

UdpPacketStandard::UdpPacketStandard(const char *name, int kind) : wsn_energy::UdpPacketInterface(name,kind)
{
    this->setHeaderLength(8);

    this->sourcePort_var = 0;
    this->destinationPort_var = 0;
    this->length_var = 0;
    this->checksum_var = 0;
}

UdpPacketStandard::UdpPacketStandard(const UdpPacketStandard& other) : wsn_energy::UdpPacketInterface(other)
{
    copy(other);
}

UdpPacketStandard::~UdpPacketStandard()
{
}

UdpPacketStandard& UdpPacketStandard::operator=(const UdpPacketStandard& other)
{
    if (this==&other) return *this;
    wsn_energy::UdpPacketInterface::operator=(other);
    copy(other);
    return *this;
}

void UdpPacketStandard::copy(const UdpPacketStandard& other)
{
    this->sourcePort_var = other.sourcePort_var;
    this->destinationPort_var = other.destinationPort_var;
    this->length_var = other.length_var;
    this->checksum_var = other.checksum_var;
}

void UdpPacketStandard::parsimPack(cCommBuffer *b)
{
    wsn_energy::UdpPacketInterface::parsimPack(b);
    doPacking(b,this->sourcePort_var);
    doPacking(b,this->destinationPort_var);
    doPacking(b,this->length_var);
    doPacking(b,this->checksum_var);
}

void UdpPacketStandard::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::UdpPacketInterface::parsimUnpack(b);
    doUnpacking(b,this->sourcePort_var);
    doUnpacking(b,this->destinationPort_var);
    doUnpacking(b,this->length_var);
    doUnpacking(b,this->checksum_var);
}

short UdpPacketStandard::getSourcePort() const
{
    return sourcePort_var;
}

void UdpPacketStandard::setSourcePort(short sourcePort)
{
    this->sourcePort_var = sourcePort;
}

short UdpPacketStandard::getDestinationPort() const
{
    return destinationPort_var;
}

void UdpPacketStandard::setDestinationPort(short destinationPort)
{
    this->destinationPort_var = destinationPort;
}

short UdpPacketStandard::getLength() const
{
    return length_var;
}

void UdpPacketStandard::setLength(short length)
{
    this->length_var = length;
}

short UdpPacketStandard::getChecksum() const
{
    return checksum_var;
}

void UdpPacketStandard::setChecksum(short checksum)
{
    this->checksum_var = checksum;
}

class UdpPacketStandardDescriptor : public cClassDescriptor
{
  public:
    UdpPacketStandardDescriptor();
    virtual ~UdpPacketStandardDescriptor();

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

Register_ClassDescriptor(UdpPacketStandardDescriptor);

UdpPacketStandardDescriptor::UdpPacketStandardDescriptor() : cClassDescriptor("wsn_energy::UdpPacketStandard", "wsn_energy::UdpPacketInterface")
{
}

UdpPacketStandardDescriptor::~UdpPacketStandardDescriptor()
{
}

bool UdpPacketStandardDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<UdpPacketStandard *>(obj)!=NULL;
}

const char *UdpPacketStandardDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UdpPacketStandardDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int UdpPacketStandardDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *UdpPacketStandardDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "sourcePort",
        "destinationPort",
        "length",
        "checksum",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int UdpPacketStandardDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourcePort")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPort")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "length")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "checksum")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *UdpPacketStandardDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "short",
        "short",
        "short",
        "short",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *UdpPacketStandardDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int UdpPacketStandardDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketStandard *pp = (UdpPacketStandard *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string UdpPacketStandardDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketStandard *pp = (UdpPacketStandard *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getSourcePort());
        case 1: return long2string(pp->getDestinationPort());
        case 2: return long2string(pp->getLength());
        case 3: return long2string(pp->getChecksum());
        default: return "";
    }
}

bool UdpPacketStandardDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketStandard *pp = (UdpPacketStandard *)object; (void)pp;
    switch (field) {
        case 0: pp->setSourcePort(string2long(value)); return true;
        case 1: pp->setDestinationPort(string2long(value)); return true;
        case 2: pp->setLength(string2long(value)); return true;
        case 3: pp->setChecksum(string2long(value)); return true;
        default: return false;
    }
}

const char *UdpPacketStandardDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *UdpPacketStandardDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketStandard *pp = (UdpPacketStandard *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(UdpPacketCompressed);

UdpPacketCompressed::UdpPacketCompressed(const char *name, int kind) : wsn_energy::UdpPacketInterface(name,kind)
{
    this->setHeaderLength(3);

    this->udpSourcePort_var = 0;
    this->udpDestinationPort_var = 0;
    this->length_var = 0;
    this->checksum_var = 0;
}

UdpPacketCompressed::UdpPacketCompressed(const UdpPacketCompressed& other) : wsn_energy::UdpPacketInterface(other)
{
    copy(other);
}

UdpPacketCompressed::~UdpPacketCompressed()
{
}

UdpPacketCompressed& UdpPacketCompressed::operator=(const UdpPacketCompressed& other)
{
    if (this==&other) return *this;
    wsn_energy::UdpPacketInterface::operator=(other);
    copy(other);
    return *this;
}

void UdpPacketCompressed::copy(const UdpPacketCompressed& other)
{
    this->udpSourcePort_var = other.udpSourcePort_var;
    this->udpDestinationPort_var = other.udpDestinationPort_var;
    this->length_var = other.length_var;
    this->checksum_var = other.checksum_var;
}

void UdpPacketCompressed::parsimPack(cCommBuffer *b)
{
    wsn_energy::UdpPacketInterface::parsimPack(b);
    doPacking(b,this->udpSourcePort_var);
    doPacking(b,this->udpDestinationPort_var);
    doPacking(b,this->length_var);
    doPacking(b,this->checksum_var);
}

void UdpPacketCompressed::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::UdpPacketInterface::parsimUnpack(b);
    doUnpacking(b,this->udpSourcePort_var);
    doUnpacking(b,this->udpDestinationPort_var);
    doUnpacking(b,this->length_var);
    doUnpacking(b,this->checksum_var);
}

bool UdpPacketCompressed::getUdpSourcePort() const
{
    return udpSourcePort_var;
}

void UdpPacketCompressed::setUdpSourcePort(bool udpSourcePort)
{
    this->udpSourcePort_var = udpSourcePort;
}

bool UdpPacketCompressed::getUdpDestinationPort() const
{
    return udpDestinationPort_var;
}

void UdpPacketCompressed::setUdpDestinationPort(bool udpDestinationPort)
{
    this->udpDestinationPort_var = udpDestinationPort;
}

short UdpPacketCompressed::getLength() const
{
    return length_var;
}

void UdpPacketCompressed::setLength(short length)
{
    this->length_var = length;
}

short UdpPacketCompressed::getChecksum() const
{
    return checksum_var;
}

void UdpPacketCompressed::setChecksum(short checksum)
{
    this->checksum_var = checksum;
}

class UdpPacketCompressedDescriptor : public cClassDescriptor
{
  public:
    UdpPacketCompressedDescriptor();
    virtual ~UdpPacketCompressedDescriptor();

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

Register_ClassDescriptor(UdpPacketCompressedDescriptor);

UdpPacketCompressedDescriptor::UdpPacketCompressedDescriptor() : cClassDescriptor("wsn_energy::UdpPacketCompressed", "wsn_energy::UdpPacketInterface")
{
}

UdpPacketCompressedDescriptor::~UdpPacketCompressedDescriptor()
{
}

bool UdpPacketCompressedDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<UdpPacketCompressed *>(obj)!=NULL;
}

const char *UdpPacketCompressedDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int UdpPacketCompressedDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
}

unsigned int UdpPacketCompressedDescriptor::getFieldTypeFlags(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
}

const char *UdpPacketCompressedDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "udpSourcePort",
        "udpDestinationPort",
        "length",
        "checksum",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int UdpPacketCompressedDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='u' && strcmp(fieldName, "udpSourcePort")==0) return base+0;
    if (fieldName[0]=='u' && strcmp(fieldName, "udpDestinationPort")==0) return base+1;
    if (fieldName[0]=='l' && strcmp(fieldName, "length")==0) return base+2;
    if (fieldName[0]=='c' && strcmp(fieldName, "checksum")==0) return base+3;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *UdpPacketCompressedDescriptor::getFieldTypeString(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldTypeString(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldTypeStrings[] = {
        "bool",
        "bool",
        "short",
        "short",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
}

const char *UdpPacketCompressedDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int UdpPacketCompressedDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketCompressed *pp = (UdpPacketCompressed *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string UdpPacketCompressedDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketCompressed *pp = (UdpPacketCompressed *)object; (void)pp;
    switch (field) {
        case 0: return bool2string(pp->getUdpSourcePort());
        case 1: return bool2string(pp->getUdpDestinationPort());
        case 2: return long2string(pp->getLength());
        case 3: return long2string(pp->getChecksum());
        default: return "";
    }
}

bool UdpPacketCompressedDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketCompressed *pp = (UdpPacketCompressed *)object; (void)pp;
    switch (field) {
        case 0: pp->setUdpSourcePort(string2bool(value)); return true;
        case 1: pp->setUdpDestinationPort(string2bool(value)); return true;
        case 2: pp->setLength(string2long(value)); return true;
        case 3: pp->setChecksum(string2long(value)); return true;
        default: return false;
    }
}

const char *UdpPacketCompressedDescriptor::getFieldStructName(void *object, int field) const
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
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
}

void *UdpPacketCompressedDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    UdpPacketCompressed *pp = (UdpPacketCompressed *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(Data);

Data::Data(const char *name, int kind) : cPacket(name,kind)
{
    this->time_var = 0;
    this->destinationPort_var = 0;
    this->destinationIPAddress_var = 0;
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
    this->destinationPort_var = other.destinationPort_var;
    this->destinationIPAddress_var = other.destinationIPAddress_var;
    this->value_var = other.value_var;
}

void Data::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->time_var);
    doPacking(b,this->destinationPort_var);
    doPacking(b,this->destinationIPAddress_var);
    doPacking(b,this->value_var);
}

void Data::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->time_var);
    doUnpacking(b,this->destinationPort_var);
    doUnpacking(b,this->destinationIPAddress_var);
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

int Data::getDestinationPort() const
{
    return destinationPort_var;
}

void Data::setDestinationPort(int destinationPort)
{
    this->destinationPort_var = destinationPort;
}

int Data::getDestinationIPAddress() const
{
    return destinationIPAddress_var;
}

void Data::setDestinationIPAddress(int destinationIPAddress)
{
    this->destinationIPAddress_var = destinationIPAddress;
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
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
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
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
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
        "destinationPort",
        "destinationIPAddress",
        "value",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int DataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+0;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationPort")==0) return base+1;
    if (fieldName[0]=='d' && strcmp(fieldName, "destinationIPAddress")==0) return base+2;
    if (fieldName[0]=='v' && strcmp(fieldName, "value")==0) return base+3;
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
        "int",
        "string",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
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
        case 1: return long2string(pp->getDestinationPort());
        case 2: return long2string(pp->getDestinationIPAddress());
        case 3: return oppstring2string(pp->getValue());
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
        case 1: pp->setDestinationPort(string2long(value)); return true;
        case 2: pp->setDestinationIPAddress(string2long(value)); return true;
        case 3: pp->setValue((value)); return true;
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
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
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

