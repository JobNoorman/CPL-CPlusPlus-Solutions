#include "Data.hpp"

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

void StructValue::accept(ValueVisitor& visitor) const {
    visitor.visit(*this);
}
