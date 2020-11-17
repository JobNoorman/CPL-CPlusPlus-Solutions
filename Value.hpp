#ifndef CPL_VALUE_HPP
#define CPL_VALUE_HPP

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

#endif
