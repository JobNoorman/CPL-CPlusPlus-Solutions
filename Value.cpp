#include "Value.hpp"

// <<<
#include "ValueVisitor.hpp"

BoolValue::BoolValue(bool b) : value(b) {}

void BoolValue::accept(ValueVisitor& visitor) const {
    visitor.visit(*this);
}

IntValue::IntValue(int i) : value(i) {}

void IntValue::accept(ValueVisitor& visitor) const {
    visitor.visit(*this);
}


StringValue::StringValue(const String& str) : value(str) {}

void StringValue::accept(ValueVisitor& visitor) const {
    visitor.visit(*this);
}

void SeqValue::accept(ValueVisitor& visitor) const {
    visitor.visit(*this);
}

void SeqValue::push_back(std::unique_ptr<Value> v) {
    values.push_back(std::move(v));
}

SeqValue::Iterator SeqValue::begin() const {
    return values.begin();
}

SeqValue::Iterator SeqValue::end() const {
    return values.end();
}

void StructValue::accept(ValueVisitor& visitor) const {
    visitor.visit(*this);
}

void StructValue::insert(String key, std::unique_ptr<Value> v) {
    values.insert({std::move(key), std::move(v)});
}

StructValue::Iterator StructValue::begin() const {
    return values.begin();
}

StructValue::Iterator StructValue::end() const {
    return values.end();
}

// >>>
