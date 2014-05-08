//
// Generated file, do not edit! Created by opp_msgc 4.4 from package/segment/segment.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#include <iostream>
#include <sstream>
#include "segment_m.h"

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

}; // end namespace wsn_energy

