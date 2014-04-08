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
    cEnum *e = cEnum::find("wsn_energy::COMMAND_AND_RESULT");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::COMMAND_AND_RESULT"));
    e->insert(NODE_STARTUP, "NODE_STARTUP");
    e->insert(OUT_OF_ENERGY, "OUT_OF_ENERGY");
    e->insert(NODE_DESTRUCT, "NODE_DESTRUCT");
    e->insert(RPL_CONSTRUCT, "RPL_CONSTRUCT");
    e->insert(RPL_SOLICIT, "RPL_SOLICIT");
    e->insert(LAYER_RADIO_BEGIN_CCA, "LAYER_RADIO_BEGIN_CCA");
    e->insert(LAYER_RADIO_END_CCA, "LAYER_RADIO_END_CCA");
    e->insert(LAYER_RADIO_SWITCH_TRANSMIT, "LAYER_RADIO_SWITCH_TRANSMIT");
    e->insert(LAYER_RADIO_SWITCH_LISTEN, "LAYER_RADIO_SWITCH_LISTEN");
    e->insert(LAYER_RADIO_SWITCH_IDLE, "LAYER_RADIO_SWITCH_IDLE");
    e->insert(LAYER_RADIO_BEGIN_TRANSMIT, "LAYER_RADIO_BEGIN_TRANSMIT");
    e->insert(LAYER_RADIO_END_TRANSMIT, "LAYER_RADIO_END_TRANSMIT");
    e->insert(LAYER_RADIO_LISTENING, "LAYER_RADIO_LISTENING");
    e->insert(LAYER_RADIO_IDLING, "LAYER_RADIO_IDLING");
    e->insert(LAYER_RADIO_SEND_OK, "LAYER_RADIO_SEND_OK");
    e->insert(LAYER_RADIO_PACKET_OVERSIZE, "LAYER_RADIO_PACKET_OVERSIZE");
    e->insert(LAYER_RADIO_RECV_OK, "LAYER_RADIO_RECV_OK");
    e->insert(LAYER_RADIO_RECV_NOT_OK, "LAYER_RADIO_RECV_NOT_OK");
    e->insert(LAYER_RDC_SEND, "LAYER_RDC_SEND");
    e->insert(LAYER_RDC_SEND_OK, "LAYER_RDC_SEND_OK");
    e->insert(LAYER_RDC_SEND_ERR, "LAYER_RDC_SEND_ERR");
    e->insert(LAYER_RDC_LISTEN_ON, "LAYER_RDC_LISTEN_ON");
    e->insert(LAYER_RDC_LISTEN_OFF, "LAYER_RDC_LISTEN_OFF");
    e->insert(LAYER_RDC_RECV_OK, "LAYER_RDC_RECV_OK");
    e->insert(LAYER_RDC_RECV_ACK, "LAYER_RDC_RECV_ACK");
    e->insert(LAYER_MAC_DEFER, "LAYER_MAC_DEFER");
    e->insert(LAYER_MAC_SEND_OK, "LAYER_MAC_SEND_OK");
    e->insert(LAYER_MAC_SEND_ERR, "LAYER_MAC_SEND_ERR");
    e->insert(LAYER_MAC_NO_ACK, "LAYER_MAC_NO_ACK");
    e->insert(LAYER_MAC_RECV_OK, "LAYER_MAC_RECV_OK");
    e->insert(LAYER_MAC_RECV_NOT_OK, "LAYER_MAC_RECV_NOT_OK");
    e->insert(LAYER_MAC_SEND, "LAYER_MAC_SEND");
    e->insert(LAYER_NET_CHECK_BUFFER, "LAYER_NET_CHECK_BUFFER");
    e->insert(LAYER_NET_SEND_OK, "LAYER_NET_SEND_OK");
    e->insert(LAYER_NET_SEND_NOT_OK, "LAYER_NET_SEND_NOT_OK");
    e->insert(LAYER_NET_RECV_OK, "LAYER_NET_RECV_OK");
    e->insert(APP_WORKING_FLAG, "APP_WORKING_FLAG");
    e->insert(APP_SENSING_FLAG, "APP_SENSING_FLAG");
    e->insert(APP_ENVIRON_FLAG, "APP_ENVIRON_FLAG");
    e->insert(CHANNEL_CCA_REQUEST, "CHANNEL_CCA_REQUEST");
    e->insert(CHANNEL_CLEAR, "CHANNEL_CLEAR");
    e->insert(CHANNEL_BUSY, "CHANNEL_BUSY");
    e->insert(COMMAND, "COMMAND");
    e->insert(DATA, "DATA");
);

EXECUTE_ON_STARTUP(
    cEnum *e = cEnum::find("wsn_energy::IP_PACKET_TYPE");
    if (!e) enums.getInstance()->add(e = new cEnum("wsn_energy::IP_PACKET_TYPE"));
    e->insert(NET_ICMP_DIO, "NET_ICMP_DIO");
    e->insert(NET_ICMP_DIS, "NET_ICMP_DIS");
    e->insert(NET_ICMP_ACK, "NET_ICMP_ACK");
    e->insert(NET_DATA, "NET_DATA");
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

Register_Class(Raw);

Raw::Raw(const char *name, int kind) : cPacket(name,kind)
{
    this->error_var = 0;
    this->note_var = 0;
    this->radioSendId_var = 0;
    this->radioRecvId_var = 0;
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
    this->error_var = other.error_var;
    this->note_var = other.note_var;
    this->radioSendId_var = other.radioSendId_var;
    this->radioRecvId_var = other.radioRecvId_var;
}

void Raw::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->error_var);
    doPacking(b,this->note_var);
    doPacking(b,this->radioSendId_var);
    doPacking(b,this->radioRecvId_var);
}

void Raw::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->error_var);
    doUnpacking(b,this->note_var);
    doUnpacking(b,this->radioSendId_var);
    doUnpacking(b,this->radioRecvId_var);
}

bool Raw::getError() const
{
    return error_var;
}

void Raw::setError(bool error)
{
    this->error_var = error;
}

int Raw::getNote() const
{
    return note_var;
}

void Raw::setNote(int note)
{
    this->note_var = note;
}

int Raw::getRadioSendId() const
{
    return radioSendId_var;
}

void Raw::setRadioSendId(int radioSendId)
{
    this->radioSendId_var = radioSendId;
}

int Raw::getRadioRecvId() const
{
    return radioRecvId_var;
}

void Raw::setRadioRecvId(int radioRecvId)
{
    this->radioRecvId_var = radioRecvId;
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
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
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
        FD_ISEDITABLE,
        FD_ISEDITABLE,
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
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
        "error",
        "note",
        "radioSendId",
        "radioRecvId",
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int RawDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='e' && strcmp(fieldName, "error")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "note")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "radioSendId")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "radioRecvId")==0) return base+3;
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
        "bool",
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
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
        case 0: return bool2string(pp->getError());
        case 1: return long2string(pp->getNote());
        case 2: return long2string(pp->getRadioSendId());
        case 3: return long2string(pp->getRadioRecvId());
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
        case 0: pp->setError(string2bool(value)); return true;
        case 1: pp->setNote(string2long(value)); return true;
        case 2: pp->setRadioSendId(string2long(value)); return true;
        case 3: pp->setRadioRecvId(string2long(value)); return true;
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
        NULL,
        NULL,
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
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

Register_Class(FrameRDC);

FrameRDC::FrameRDC(const char *name, int kind) : cPacket(name,kind)
{
    this->note_var = 0;
}

FrameRDC::FrameRDC(const FrameRDC& other) : cPacket(other)
{
    copy(other);
}

FrameRDC::~FrameRDC()
{
}

FrameRDC& FrameRDC::operator=(const FrameRDC& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void FrameRDC::copy(const FrameRDC& other)
{
    this->note_var = other.note_var;
}

void FrameRDC::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->note_var);
}

void FrameRDC::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->note_var);
}

int FrameRDC::getNote() const
{
    return note_var;
}

void FrameRDC::setNote(int note)
{
    this->note_var = note;
}

class FrameRDCDescriptor : public cClassDescriptor
{
  public:
    FrameRDCDescriptor();
    virtual ~FrameRDCDescriptor();

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

Register_ClassDescriptor(FrameRDCDescriptor);

FrameRDCDescriptor::FrameRDCDescriptor() : cClassDescriptor("wsn_energy::FrameRDC", "cPacket")
{
}

FrameRDCDescriptor::~FrameRDCDescriptor()
{
}

bool FrameRDCDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FrameRDC *>(obj)!=NULL;
}

const char *FrameRDCDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameRDCDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 1+basedesc->getFieldCount(object) : 1;
}

unsigned int FrameRDCDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *FrameRDCDescriptor::getFieldName(void *object, int field) const
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

int FrameRDCDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "note")==0) return base+0;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameRDCDescriptor::getFieldTypeString(void *object, int field) const
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

const char *FrameRDCDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int FrameRDCDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FrameRDC *pp = (FrameRDC *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FrameRDCDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FrameRDC *pp = (FrameRDC *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNote());
        default: return "";
    }
}

bool FrameRDCDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FrameRDC *pp = (FrameRDC *)object; (void)pp;
    switch (field) {
        case 0: pp->setNote(string2long(value)); return true;
        default: return false;
    }
}

const char *FrameRDCDescriptor::getFieldStructName(void *object, int field) const
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

void *FrameRDCDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FrameRDC *pp = (FrameRDC *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(FrameMAC);

FrameMAC::FrameMAC(const char *name, int kind) : cPacket(name,kind)
{
    this->numberTransmission_var = 0;
    this->note_var = 0;
    this->senderMacAddress_var = 0;
    this->recverMacAddress_var = 0;
    this->sequenceNumber_var = 0;
}

FrameMAC::FrameMAC(const FrameMAC& other) : cPacket(other)
{
    copy(other);
}

FrameMAC::~FrameMAC()
{
}

FrameMAC& FrameMAC::operator=(const FrameMAC& other)
{
    if (this==&other) return *this;
    cPacket::operator=(other);
    copy(other);
    return *this;
}

void FrameMAC::copy(const FrameMAC& other)
{
    this->numberTransmission_var = other.numberTransmission_var;
    this->note_var = other.note_var;
    this->senderMacAddress_var = other.senderMacAddress_var;
    this->recverMacAddress_var = other.recverMacAddress_var;
    this->sequenceNumber_var = other.sequenceNumber_var;
}

void FrameMAC::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->numberTransmission_var);
    doPacking(b,this->note_var);
    doPacking(b,this->senderMacAddress_var);
    doPacking(b,this->recverMacAddress_var);
    doPacking(b,this->sequenceNumber_var);
}

void FrameMAC::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->numberTransmission_var);
    doUnpacking(b,this->note_var);
    doUnpacking(b,this->senderMacAddress_var);
    doUnpacking(b,this->recverMacAddress_var);
    doUnpacking(b,this->sequenceNumber_var);
}

int FrameMAC::getNumberTransmission() const
{
    return numberTransmission_var;
}

void FrameMAC::setNumberTransmission(int numberTransmission)
{
    this->numberTransmission_var = numberTransmission;
}

int FrameMAC::getNote() const
{
    return note_var;
}

void FrameMAC::setNote(int note)
{
    this->note_var = note;
}

int FrameMAC::getSenderMacAddress() const
{
    return senderMacAddress_var;
}

void FrameMAC::setSenderMacAddress(int senderMacAddress)
{
    this->senderMacAddress_var = senderMacAddress;
}

int FrameMAC::getRecverMacAddress() const
{
    return recverMacAddress_var;
}

void FrameMAC::setRecverMacAddress(int recverMacAddress)
{
    this->recverMacAddress_var = recverMacAddress;
}

int FrameMAC::getSequenceNumber() const
{
    return sequenceNumber_var;
}

void FrameMAC::setSequenceNumber(int sequenceNumber)
{
    this->sequenceNumber_var = sequenceNumber;
}

class FrameMACDescriptor : public cClassDescriptor
{
  public:
    FrameMACDescriptor();
    virtual ~FrameMACDescriptor();

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

Register_ClassDescriptor(FrameMACDescriptor);

FrameMACDescriptor::FrameMACDescriptor() : cClassDescriptor("wsn_energy::FrameMAC", "cPacket")
{
}

FrameMACDescriptor::~FrameMACDescriptor()
{
}

bool FrameMACDescriptor::doesSupport(cObject *obj) const
{
    return dynamic_cast<FrameMAC *>(obj)!=NULL;
}

const char *FrameMACDescriptor::getProperty(const char *propertyname) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? basedesc->getProperty(propertyname) : NULL;
}

int FrameMACDescriptor::getFieldCount(void *object) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
}

unsigned int FrameMACDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *FrameMACDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "numberTransmission",
        "note",
        "senderMacAddress",
        "recverMacAddress",
        "sequenceNumber",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int FrameMACDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "numberTransmission")==0) return base+0;
    if (fieldName[0]=='n' && strcmp(fieldName, "note")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderMacAddress")==0) return base+2;
    if (fieldName[0]=='r' && strcmp(fieldName, "recverMacAddress")==0) return base+3;
    if (fieldName[0]=='s' && strcmp(fieldName, "sequenceNumber")==0) return base+4;
    return basedesc ? basedesc->findField(object, fieldName) : -1;
}

const char *FrameMACDescriptor::getFieldTypeString(void *object, int field) const
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

const char *FrameMACDescriptor::getFieldProperty(void *object, int field, const char *propertyname) const
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

int FrameMACDescriptor::getArraySize(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getArraySize(object, field);
        field -= basedesc->getFieldCount(object);
    }
    FrameMAC *pp = (FrameMAC *)object; (void)pp;
    switch (field) {
        default: return 0;
    }
}

std::string FrameMACDescriptor::getFieldAsString(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldAsString(object,field,i);
        field -= basedesc->getFieldCount(object);
    }
    FrameMAC *pp = (FrameMAC *)object; (void)pp;
    switch (field) {
        case 0: return long2string(pp->getNumberTransmission());
        case 1: return long2string(pp->getNote());
        case 2: return long2string(pp->getSenderMacAddress());
        case 3: return long2string(pp->getRecverMacAddress());
        case 4: return long2string(pp->getSequenceNumber());
        default: return "";
    }
}

bool FrameMACDescriptor::setFieldAsString(void *object, int field, int i, const char *value) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->setFieldAsString(object,field,i,value);
        field -= basedesc->getFieldCount(object);
    }
    FrameMAC *pp = (FrameMAC *)object; (void)pp;
    switch (field) {
        case 0: pp->setNumberTransmission(string2long(value)); return true;
        case 1: pp->setNote(string2long(value)); return true;
        case 2: pp->setSenderMacAddress(string2long(value)); return true;
        case 3: pp->setRecverMacAddress(string2long(value)); return true;
        case 4: pp->setSequenceNumber(string2long(value)); return true;
        default: return false;
    }
}

const char *FrameMACDescriptor::getFieldStructName(void *object, int field) const
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

void *FrameMACDescriptor::getFieldStructPointer(void *object, int field, int i) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldStructPointer(object, field, i);
        field -= basedesc->getFieldCount(object);
    }
    FrameMAC *pp = (FrameMAC *)object; (void)pp;
    switch (field) {
        default: return NULL;
    }
}

Register_Class(IpPacket);

IpPacket::IpPacket(const char *name, int kind) : cPacket(name,kind)
{
    this->note_var = 0;
    this->type_var = 0;
    this->isBroadcast_var = 0;
    this->senderIpAddress_var = 0;
    this->recverIpAddress_var = 0;
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
    this->note_var = other.note_var;
    this->type_var = other.type_var;
    this->isBroadcast_var = other.isBroadcast_var;
    this->senderIpAddress_var = other.senderIpAddress_var;
    this->recverIpAddress_var = other.recverIpAddress_var;
}

void IpPacket::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->note_var);
    doPacking(b,this->type_var);
    doPacking(b,this->isBroadcast_var);
    doPacking(b,this->senderIpAddress_var);
    doPacking(b,this->recverIpAddress_var);
}

void IpPacket::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->note_var);
    doUnpacking(b,this->type_var);
    doUnpacking(b,this->isBroadcast_var);
    doUnpacking(b,this->senderIpAddress_var);
    doUnpacking(b,this->recverIpAddress_var);
}

int IpPacket::getNote() const
{
    return note_var;
}

void IpPacket::setNote(int note)
{
    this->note_var = note;
}

int IpPacket::getType() const
{
    return type_var;
}

void IpPacket::setType(int type)
{
    this->type_var = type;
}

bool IpPacket::getIsBroadcast() const
{
    return isBroadcast_var;
}

void IpPacket::setIsBroadcast(bool isBroadcast)
{
    this->isBroadcast_var = isBroadcast;
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
    return basedesc ? 5+basedesc->getFieldCount(object) : 5;
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
    };
    return (field>=0 && field<5) ? fieldTypeFlags[field] : 0;
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
        "note",
        "type",
        "isBroadcast",
        "senderIpAddress",
        "recverIpAddress",
    };
    return (field>=0 && field<5) ? fieldNames[field] : NULL;
}

int IpPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "note")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "type")==0) return base+1;
    if (fieldName[0]=='i' && strcmp(fieldName, "isBroadcast")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "senderIpAddress")==0) return base+3;
    if (fieldName[0]=='r' && strcmp(fieldName, "recverIpAddress")==0) return base+4;
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
        "int",
        "int",
        "bool",
        "int",
        "int",
    };
    return (field>=0 && field<5) ? fieldTypeStrings[field] : NULL;
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
        case 0: return long2string(pp->getNote());
        case 1: return long2string(pp->getType());
        case 2: return bool2string(pp->getIsBroadcast());
        case 3: return long2string(pp->getSenderIpAddress());
        case 4: return long2string(pp->getRecverIpAddress());
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
        case 0: pp->setNote(string2long(value)); return true;
        case 1: pp->setType(string2long(value)); return true;
        case 2: pp->setIsBroadcast(string2bool(value)); return true;
        case 3: pp->setSenderIpAddress(string2long(value)); return true;
        case 4: pp->setRecverIpAddress(string2long(value)); return true;
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
    };
    return (field>=0 && field<5) ? fieldStructNames[field] : NULL;
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

Register_Class(DIO);

DIO::DIO(const char *name, int kind) : wsn_energy::IpPacket(name,kind)
{
    this->dodagID_var = 0;
    this->version_var = 0;
    this->rank_var = 0;
    this->selfEnergy_var = 0;
}

DIO::DIO(const DIO& other) : wsn_energy::IpPacket(other)
{
    copy(other);
}

DIO::~DIO()
{
}

DIO& DIO::operator=(const DIO& other)
{
    if (this==&other) return *this;
    wsn_energy::IpPacket::operator=(other);
    copy(other);
    return *this;
}

void DIO::copy(const DIO& other)
{
    this->dodagID_var = other.dodagID_var;
    this->version_var = other.version_var;
    this->rank_var = other.rank_var;
    this->selfEnergy_var = other.selfEnergy_var;
}

void DIO::parsimPack(cCommBuffer *b)
{
    wsn_energy::IpPacket::parsimPack(b);
    doPacking(b,this->dodagID_var);
    doPacking(b,this->version_var);
    doPacking(b,this->rank_var);
    doPacking(b,this->selfEnergy_var);
}

void DIO::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::IpPacket::parsimUnpack(b);
    doUnpacking(b,this->dodagID_var);
    doUnpacking(b,this->version_var);
    doUnpacking(b,this->rank_var);
    doUnpacking(b,this->selfEnergy_var);
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

DIODescriptor::DIODescriptor() : cClassDescriptor("wsn_energy::DIO", "wsn_energy::IpPacket")
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
    return basedesc ? 4+basedesc->getFieldCount(object) : 4;
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
    };
    return (field>=0 && field<4) ? fieldTypeFlags[field] : 0;
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
    };
    return (field>=0 && field<4) ? fieldNames[field] : NULL;
}

int DIODescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='d' && strcmp(fieldName, "dodagID")==0) return base+0;
    if (fieldName[0]=='v' && strcmp(fieldName, "version")==0) return base+1;
    if (fieldName[0]=='r' && strcmp(fieldName, "rank")==0) return base+2;
    if (fieldName[0]=='s' && strcmp(fieldName, "selfEnergy")==0) return base+3;
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
    };
    return (field>=0 && field<4) ? fieldTypeStrings[field] : NULL;
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
    };
    return (field>=0 && field<4) ? fieldStructNames[field] : NULL;
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

DIS::DIS(const char *name, int kind) : wsn_energy::IpPacket(name,kind)
{
    this->convergence_var = 0;
}

DIS::DIS(const DIS& other) : wsn_energy::IpPacket(other)
{
    copy(other);
}

DIS::~DIS()
{
}

DIS& DIS::operator=(const DIS& other)
{
    if (this==&other) return *this;
    wsn_energy::IpPacket::operator=(other);
    copy(other);
    return *this;
}

void DIS::copy(const DIS& other)
{
    this->convergence_var = other.convergence_var;
}

void DIS::parsimPack(cCommBuffer *b)
{
    wsn_energy::IpPacket::parsimPack(b);
    doPacking(b,this->convergence_var);
}

void DIS::parsimUnpack(cCommBuffer *b)
{
    wsn_energy::IpPacket::parsimUnpack(b);
    doUnpacking(b,this->convergence_var);
}

int DIS::getConvergence() const
{
    return convergence_var;
}

void DIS::setConvergence(int convergence)
{
    this->convergence_var = convergence;
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

DISDescriptor::DISDescriptor() : cClassDescriptor("wsn_energy::DIS", "wsn_energy::IpPacket")
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
        "convergence",
    };
    return (field>=0 && field<1) ? fieldNames[field] : NULL;
}

int DISDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='c' && strcmp(fieldName, "convergence")==0) return base+0;
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
        case 0: return long2string(pp->getConvergence());
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
        case 0: pp->setConvergence(string2long(value)); return true;
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
    this->note_var = 0;
    this->sourceIpAddress_var = 0;
    this->sinkIpAddress_var = 0;
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
    this->note_var = other.note_var;
    this->sourceIpAddress_var = other.sourceIpAddress_var;
    this->sinkIpAddress_var = other.sinkIpAddress_var;
}

void UdpPacket::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->note_var);
    doPacking(b,this->sourceIpAddress_var);
    doPacking(b,this->sinkIpAddress_var);
}

void UdpPacket::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->note_var);
    doUnpacking(b,this->sourceIpAddress_var);
    doUnpacking(b,this->sinkIpAddress_var);
}

int UdpPacket::getNote() const
{
    return note_var;
}

void UdpPacket::setNote(int note)
{
    this->note_var = note;
}

int UdpPacket::getSourceIpAddress() const
{
    return sourceIpAddress_var;
}

void UdpPacket::setSourceIpAddress(int sourceIpAddress)
{
    this->sourceIpAddress_var = sourceIpAddress;
}

int UdpPacket::getSinkIpAddress() const
{
    return sinkIpAddress_var;
}

void UdpPacket::setSinkIpAddress(int sinkIpAddress)
{
    this->sinkIpAddress_var = sinkIpAddress;
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
    return basedesc ? 3+basedesc->getFieldCount(object) : 3;
}

unsigned int UdpPacketDescriptor::getFieldTypeFlags(void *object, int field) const
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

const char *UdpPacketDescriptor::getFieldName(void *object, int field) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    if (basedesc) {
        if (field < basedesc->getFieldCount(object))
            return basedesc->getFieldName(object, field);
        field -= basedesc->getFieldCount(object);
    }
    static const char *fieldNames[] = {
        "note",
        "sourceIpAddress",
        "sinkIpAddress",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int UdpPacketDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "note")==0) return base+0;
    if (fieldName[0]=='s' && strcmp(fieldName, "sourceIpAddress")==0) return base+1;
    if (fieldName[0]=='s' && strcmp(fieldName, "sinkIpAddress")==0) return base+2;
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
    static const char *fieldTypeStrings[] = {
        "int",
        "int",
        "int",
    };
    return (field>=0 && field<3) ? fieldTypeStrings[field] : NULL;
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
        case 0: return long2string(pp->getNote());
        case 1: return long2string(pp->getSourceIpAddress());
        case 2: return long2string(pp->getSinkIpAddress());
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
        case 0: pp->setNote(string2long(value)); return true;
        case 1: pp->setSourceIpAddress(string2long(value)); return true;
        case 2: pp->setSinkIpAddress(string2long(value)); return true;
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
    static const char *fieldStructNames[] = {
        NULL,
        NULL,
        NULL,
    };
    return (field>=0 && field<3) ? fieldStructNames[field] : NULL;
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
    this->note_var = 0;
    this->time_var = 0;
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
    this->note_var = other.note_var;
    this->time_var = other.time_var;
    this->value_var = other.value_var;
}

void Data::parsimPack(cCommBuffer *b)
{
    cPacket::parsimPack(b);
    doPacking(b,this->note_var);
    doPacking(b,this->time_var);
    doPacking(b,this->value_var);
}

void Data::parsimUnpack(cCommBuffer *b)
{
    cPacket::parsimUnpack(b);
    doUnpacking(b,this->note_var);
    doUnpacking(b,this->time_var);
    doUnpacking(b,this->value_var);
}

int Data::getNote() const
{
    return note_var;
}

void Data::setNote(int note)
{
    this->note_var = note;
}

double Data::getTime() const
{
    return time_var;
}

void Data::setTime(double time)
{
    this->time_var = time;
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
        "note",
        "time",
        "value",
    };
    return (field>=0 && field<3) ? fieldNames[field] : NULL;
}

int DataDescriptor::findField(void *object, const char *fieldName) const
{
    cClassDescriptor *basedesc = getBaseClassDescriptor();
    int base = basedesc ? basedesc->getFieldCount(object) : 0;
    if (fieldName[0]=='n' && strcmp(fieldName, "note")==0) return base+0;
    if (fieldName[0]=='t' && strcmp(fieldName, "time")==0) return base+1;
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
        "int",
        "double",
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
        case 0: return long2string(pp->getNote());
        case 1: return double2string(pp->getTime());
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
        case 0: pp->setNote(string2long(value)); return true;
        case 1: pp->setTime(string2double(value)); return true;
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

