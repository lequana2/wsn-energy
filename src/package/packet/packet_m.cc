//
// Generated file, do not edit! Created by opp_msgc 4.4 from package/packet/packet.msg.
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

}; // end namespace wsn_energy

