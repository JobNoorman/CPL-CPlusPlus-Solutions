#include "JsonWriter.hpp"

#include <ostream>

JsonWriter::JsonWriter(std::ostream& stream) : stream_(stream) {}

void JsonWriter::visit(const BoolValue& b) {
    stream_ << (b.value ? "true" : "false");
}

void JsonWriter::visit(const IntValue& i) {
    stream_ << i.value;
}

void JsonWriter::visit(const StringValue& s) {
    stream_ << '"' << s.value << '"';
}

void JsonWriter::visit(const SeqValue& s) {
    stream_ << '[';
    bool first = true;

    for (const auto& v : s) {
        if (!first) {
            stream_ << ", ";
        }

        first = false;
        v->accept(*this);
    }

    stream_ << ']';
}

void JsonWriter::visit(const StructValue& s) {
    stream_ << '{';
    bool first = true;

    for (const auto& [key, value] : s) {
        if (!first) {
            stream_ << ", ";
        }

        first = false;

        stream_ << '"' << key << "\": ";
        value->accept(*this);
    }

    stream_ << '}';
}
