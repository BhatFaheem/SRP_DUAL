//
// Generated file, do not edit! Created by opp_msgtool 6.1 from SecRoutingUpdate.msg.
//

// Disable warnings about unused variables, empty switch stmts, etc:
#ifdef _MSC_VER
#  pragma warning(disable:4101)
#  pragma warning(disable:4065)
#endif

#if defined(__clang__)
#  pragma clang diagnostic ignored "-Wshadow"
#  pragma clang diagnostic ignored "-Wconversion"
#  pragma clang diagnostic ignored "-Wunused-parameter"
#  pragma clang diagnostic ignored "-Wc++98-compat"
#  pragma clang diagnostic ignored "-Wunreachable-code-break"
#  pragma clang diagnostic ignored "-Wold-style-cast"
#elif defined(__GNUC__)
#  pragma GCC diagnostic ignored "-Wshadow"
#  pragma GCC diagnostic ignored "-Wconversion"
#  pragma GCC diagnostic ignored "-Wunused-parameter"
#  pragma GCC diagnostic ignored "-Wold-style-cast"
#  pragma GCC diagnostic ignored "-Wsuggest-attribute=noreturn"
#  pragma GCC diagnostic ignored "-Wfloat-conversion"
#endif

#include <iostream>
#include <sstream>
#include <memory>
#include <type_traits>
#include "SecRoutingUpdate_m.h"

namespace omnetpp {

// Template pack/unpack rules. They are declared *after* a1l type-specific pack functions for multiple reasons.
// They are in the omnetpp namespace, to allow them to be found by argument-dependent lookup via the cCommBuffer argument

// Packing/unpacking an std::vector
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::vector<T,A>& v)
{
    int n = v.size();
    doParsimPacking(buffer, n);
    for (int i = 0; i < n; i++)
        doParsimPacking(buffer, v[i]);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::vector<T,A>& v)
{
    int n;
    doParsimUnpacking(buffer, n);
    v.resize(n);
    for (int i = 0; i < n; i++)
        doParsimUnpacking(buffer, v[i]);
}

// Packing/unpacking an std::list
template<typename T, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::list<T,A>& l)
{
    doParsimPacking(buffer, (int)l.size());
    for (typename std::list<T,A>::const_iterator it = l.begin(); it != l.end(); ++it)
        doParsimPacking(buffer, (T&)*it);
}

template<typename T, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::list<T,A>& l)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        l.push_back(T());
        doParsimUnpacking(buffer, l.back());
    }
}

// Packing/unpacking an std::set
template<typename T, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::set<T,Tr,A>& s)
{
    doParsimPacking(buffer, (int)s.size());
    for (typename std::set<T,Tr,A>::const_iterator it = s.begin(); it != s.end(); ++it)
        doParsimPacking(buffer, *it);
}

template<typename T, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::set<T,Tr,A>& s)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        T x;
        doParsimUnpacking(buffer, x);
        s.insert(x);
    }
}

// Packing/unpacking an std::map
template<typename K, typename V, typename Tr, typename A>
void doParsimPacking(omnetpp::cCommBuffer *buffer, const std::map<K,V,Tr,A>& m)
{
    doParsimPacking(buffer, (int)m.size());
    for (typename std::map<K,V,Tr,A>::const_iterator it = m.begin(); it != m.end(); ++it) {
        doParsimPacking(buffer, it->first);
        doParsimPacking(buffer, it->second);
    }
}

template<typename K, typename V, typename Tr, typename A>
void doParsimUnpacking(omnetpp::cCommBuffer *buffer, std::map<K,V,Tr,A>& m)
{
    int n;
    doParsimUnpacking(buffer, n);
    for (int i = 0; i < n; i++) {
        K k; V v;
        doParsimUnpacking(buffer, k);
        doParsimUnpacking(buffer, v);
        m[k] = v;
    }
}

// Default pack/unpack function for arrays
template<typename T>
void doParsimArrayPacking(omnetpp::cCommBuffer *b, const T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimPacking(b, t[i]);
}

template<typename T>
void doParsimArrayUnpacking(omnetpp::cCommBuffer *b, T *t, int n)
{
    for (int i = 0; i < n; i++)
        doParsimUnpacking(b, t[i]);
}

// Default rule to prevent compiler from choosing base class' doParsimPacking() function
template<typename T>
void doParsimPacking(omnetpp::cCommBuffer *, const T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimPacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

template<typename T>
void doParsimUnpacking(omnetpp::cCommBuffer *, T& t)
{
    throw omnetpp::cRuntimeError("Parsim error: No doParsimUnpacking() function for type %s", omnetpp::opp_typename(typeid(t)));
}

}  // namespace omnetpp

Register_Class(SecRoutingUpdate)

SecRoutingUpdate::SecRoutingUpdate(const char *name, short kind) : ::omnetpp::cMessage(name, kind)
{
}

SecRoutingUpdate::SecRoutingUpdate(const SecRoutingUpdate& other) : ::omnetpp::cMessage(other)
{
    copy(other);
}

SecRoutingUpdate::~SecRoutingUpdate()
{
}

SecRoutingUpdate& SecRoutingUpdate::operator=(const SecRoutingUpdate& other)
{
    if (this == &other) return *this;
    ::omnetpp::cMessage::operator=(other);
    copy(other);
    return *this;
}

void SecRoutingUpdate::copy(const SecRoutingUpdate& other)
{
    this->origin = other.origin;
    this->dest = other.dest;
    this->metric = other.metric;
    this->hash = other.hash;
}

void SecRoutingUpdate::parsimPack(omnetpp::cCommBuffer *b) const
{
    ::omnetpp::cMessage::parsimPack(b);
    doParsimPacking(b,this->origin);
    doParsimPacking(b,this->dest);
    doParsimPacking(b,this->metric);
    doParsimPacking(b,this->hash);
}

void SecRoutingUpdate::parsimUnpack(omnetpp::cCommBuffer *b)
{
    ::omnetpp::cMessage::parsimUnpack(b);
    doParsimUnpacking(b,this->origin);
    doParsimUnpacking(b,this->dest);
    doParsimUnpacking(b,this->metric);
    doParsimUnpacking(b,this->hash);
}

int SecRoutingUpdate::getOrigin() const
{
    return this->origin;
}

void SecRoutingUpdate::setOrigin(int origin)
{
    this->origin = origin;
}

int SecRoutingUpdate::getDest() const
{
    return this->dest;
}

void SecRoutingUpdate::setDest(int dest)
{
    this->dest = dest;
}

double SecRoutingUpdate::getMetric() const
{
    return this->metric;
}

void SecRoutingUpdate::setMetric(double metric)
{
    this->metric = metric;
}

const char * SecRoutingUpdate::getHash() const
{
    return this->hash.c_str();
}

void SecRoutingUpdate::setHash(const char * hash)
{
    this->hash = hash;
}

class SecRoutingUpdateDescriptor : public omnetpp::cClassDescriptor
{
  private:
    mutable const char **propertyNames;
    enum FieldConstants {
        FIELD_origin,
        FIELD_dest,
        FIELD_metric,
        FIELD_hash,
    };
  public:
    SecRoutingUpdateDescriptor();
    virtual ~SecRoutingUpdateDescriptor();

    virtual bool doesSupport(omnetpp::cObject *obj) const override;
    virtual const char **getPropertyNames() const override;
    virtual const char *getProperty(const char *propertyName) const override;
    virtual int getFieldCount() const override;
    virtual const char *getFieldName(int field) const override;
    virtual int findField(const char *fieldName) const override;
    virtual unsigned int getFieldTypeFlags(int field) const override;
    virtual const char *getFieldTypeString(int field) const override;
    virtual const char **getFieldPropertyNames(int field) const override;
    virtual const char *getFieldProperty(int field, const char *propertyName) const override;
    virtual int getFieldArraySize(omnetpp::any_ptr object, int field) const override;
    virtual void setFieldArraySize(omnetpp::any_ptr object, int field, int size) const override;

    virtual const char *getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const override;
    virtual std::string getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const override;
    virtual omnetpp::cValue getFieldValue(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const override;

    virtual const char *getFieldStructName(int field) const override;
    virtual omnetpp::any_ptr getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const override;
    virtual void setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const override;
};

Register_ClassDescriptor(SecRoutingUpdateDescriptor)

SecRoutingUpdateDescriptor::SecRoutingUpdateDescriptor() : omnetpp::cClassDescriptor(omnetpp::opp_typename(typeid(SecRoutingUpdate)), "omnetpp::cMessage")
{
    propertyNames = nullptr;
}

SecRoutingUpdateDescriptor::~SecRoutingUpdateDescriptor()
{
    delete[] propertyNames;
}

bool SecRoutingUpdateDescriptor::doesSupport(omnetpp::cObject *obj) const
{
    return dynamic_cast<SecRoutingUpdate *>(obj)!=nullptr;
}

const char **SecRoutingUpdateDescriptor::getPropertyNames() const
{
    if (!propertyNames) {
        static const char *names[] = {  nullptr };
        omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
        const char **baseNames = base ? base->getPropertyNames() : nullptr;
        propertyNames = mergeLists(baseNames, names);
    }
    return propertyNames;
}

const char *SecRoutingUpdateDescriptor::getProperty(const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? base->getProperty(propertyName) : nullptr;
}

int SecRoutingUpdateDescriptor::getFieldCount() const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    return base ? 4+base->getFieldCount() : 4;
}

unsigned int SecRoutingUpdateDescriptor::getFieldTypeFlags(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeFlags(field);
        field -= base->getFieldCount();
    }
    static unsigned int fieldTypeFlags[] = {
        FD_ISEDITABLE,    // FIELD_origin
        FD_ISEDITABLE,    // FIELD_dest
        FD_ISEDITABLE,    // FIELD_metric
        FD_ISEDITABLE,    // FIELD_hash
    };
    return (field >= 0 && field < 4) ? fieldTypeFlags[field] : 0;
}

const char *SecRoutingUpdateDescriptor::getFieldName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldName(field);
        field -= base->getFieldCount();
    }
    static const char *fieldNames[] = {
        "origin",
        "dest",
        "metric",
        "hash",
    };
    return (field >= 0 && field < 4) ? fieldNames[field] : nullptr;
}

int SecRoutingUpdateDescriptor::findField(const char *fieldName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    int baseIndex = base ? base->getFieldCount() : 0;
    if (strcmp(fieldName, "origin") == 0) return baseIndex + 0;
    if (strcmp(fieldName, "dest") == 0) return baseIndex + 1;
    if (strcmp(fieldName, "metric") == 0) return baseIndex + 2;
    if (strcmp(fieldName, "hash") == 0) return baseIndex + 3;
    return base ? base->findField(fieldName) : -1;
}

const char *SecRoutingUpdateDescriptor::getFieldTypeString(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldTypeString(field);
        field -= base->getFieldCount();
    }
    static const char *fieldTypeStrings[] = {
        "int",    // FIELD_origin
        "int",    // FIELD_dest
        "double",    // FIELD_metric
        "string",    // FIELD_hash
    };
    return (field >= 0 && field < 4) ? fieldTypeStrings[field] : nullptr;
}

const char **SecRoutingUpdateDescriptor::getFieldPropertyNames(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldPropertyNames(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

const char *SecRoutingUpdateDescriptor::getFieldProperty(int field, const char *propertyName) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldProperty(field, propertyName);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    }
}

int SecRoutingUpdateDescriptor::getFieldArraySize(omnetpp::any_ptr object, int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldArraySize(object, field);
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        default: return 0;
    }
}

void SecRoutingUpdateDescriptor::setFieldArraySize(omnetpp::any_ptr object, int field, int size) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldArraySize(object, field, size);
            return;
        }
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set array size of field %d of class 'SecRoutingUpdate'", field);
    }
}

const char *SecRoutingUpdateDescriptor::getFieldDynamicTypeString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldDynamicTypeString(object,field,i);
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        default: return nullptr;
    }
}

std::string SecRoutingUpdateDescriptor::getFieldValueAsString(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValueAsString(object,field,i);
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_origin: return long2string(pp->getOrigin());
        case FIELD_dest: return long2string(pp->getDest());
        case FIELD_metric: return double2string(pp->getMetric());
        case FIELD_hash: return oppstring2string(pp->getHash());
        default: return "";
    }
}

void SecRoutingUpdateDescriptor::setFieldValueAsString(omnetpp::any_ptr object, int field, int i, const char *value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValueAsString(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_origin: pp->setOrigin(string2long(value)); break;
        case FIELD_dest: pp->setDest(string2long(value)); break;
        case FIELD_metric: pp->setMetric(string2double(value)); break;
        case FIELD_hash: pp->setHash((value)); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SecRoutingUpdate'", field);
    }
}

omnetpp::cValue SecRoutingUpdateDescriptor::getFieldValue(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldValue(object,field,i);
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_origin: return pp->getOrigin();
        case FIELD_dest: return pp->getDest();
        case FIELD_metric: return pp->getMetric();
        case FIELD_hash: return pp->getHash();
        default: throw omnetpp::cRuntimeError("Cannot return field %d of class 'SecRoutingUpdate' as cValue -- field index out of range?", field);
    }
}

void SecRoutingUpdateDescriptor::setFieldValue(omnetpp::any_ptr object, int field, int i, const omnetpp::cValue& value) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldValue(object, field, i, value);
            return;
        }
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        case FIELD_origin: pp->setOrigin(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_dest: pp->setDest(omnetpp::checked_int_cast<int>(value.intValue())); break;
        case FIELD_metric: pp->setMetric(value.doubleValue()); break;
        case FIELD_hash: pp->setHash(value.stringValue()); break;
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SecRoutingUpdate'", field);
    }
}

const char *SecRoutingUpdateDescriptor::getFieldStructName(int field) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructName(field);
        field -= base->getFieldCount();
    }
    switch (field) {
        default: return nullptr;
    };
}

omnetpp::any_ptr SecRoutingUpdateDescriptor::getFieldStructValuePointer(omnetpp::any_ptr object, int field, int i) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount())
            return base->getFieldStructValuePointer(object, field, i);
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        default: return omnetpp::any_ptr(nullptr);
    }
}

void SecRoutingUpdateDescriptor::setFieldStructValuePointer(omnetpp::any_ptr object, int field, int i, omnetpp::any_ptr ptr) const
{
    omnetpp::cClassDescriptor *base = getBaseClassDescriptor();
    if (base) {
        if (field < base->getFieldCount()){
            base->setFieldStructValuePointer(object, field, i, ptr);
            return;
        }
        field -= base->getFieldCount();
    }
    SecRoutingUpdate *pp = omnetpp::fromAnyPtr<SecRoutingUpdate>(object); (void)pp;
    switch (field) {
        default: throw omnetpp::cRuntimeError("Cannot set field %d of class 'SecRoutingUpdate'", field);
    }
}

namespace omnetpp {

}  // namespace omnetpp

