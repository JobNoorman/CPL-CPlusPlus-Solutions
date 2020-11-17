#include <iostream>
#include <algorithm>
#include <memory>

#include "String.hpp"
#include "Value.hpp"
#include "JsonWriter.hpp"

int main() {
    auto data = std::make_unique<StructValue>();

    auto seq = std::make_unique<SeqValue>();
    seq->push_back(std::make_unique<BoolValue>(false));
    seq->push_back(std::make_unique<StringValue>("Hello"));

    data->insert("seq", std::move(seq));
    data->insert("val", std::make_unique<IntValue>(42));

    auto visitor = JsonWriter(std::cout);
    data->accept(visitor);
}
