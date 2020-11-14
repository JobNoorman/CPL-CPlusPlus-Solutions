#ifndef CPL_DATA_HPP
#define CPL_DATA_HPP

#include <vector>
#include <map>
#include <memory>

#include "String.hpp"

class ValueVisitor;

class Value {
public:

    virtual ~Value() = default;

    virtual void accept(ValueVisitor& visitor) const = 0;
};

class BoolValue : public Value {
public:

    bool value;

    BoolValue(bool b);

    void accept(ValueVisitor& visitor) const override;

};

class IntValue : public Value {
public:

    int value;

    IntValue(int i);

    void accept(ValueVisitor& visitor) const override;

};

class StringValue : public Value {
public:

    String value;

    StringValue(const String& str);

    void accept(ValueVisitor& visitor) const override;

};

class SeqValue : public Value {
public:

    std::vector<std::unique_ptr<Value>> values;

    void accept(ValueVisitor& visitor) const override;
};

class StructValue : public Value {
public:

    std::map<String, std::unique_ptr<Value>> values;

    void accept(ValueVisitor& visitor) const override;
};

class ValueVisitor {
public:

    virtual void visit(const BoolValue& b) = 0;
    virtual void visit(const IntValue& i) = 0;
    virtual void visit(const StringValue& s) = 0;
    virtual void visit(const SeqValue& s) = 0;
    virtual void visit(const StructValue& s) = 0;
};

#endif
