#include <iostream>
#include <algorithm>
#include <memory>

#include "String.hpp"
#include "Data.hpp"
#include "JsonWriter.hpp"

int main() {
    auto data = std::make_unique<StructValue>();

    auto seq = std::make_unique<SeqValue>();
    seq->values.push_back(std::make_unique<BoolValue>(false));
    seq->values.push_back(std::make_unique<StringValue>("Hello"));

    data->values["seq"] = std::move(seq);
    data->values["val"] = std::make_unique<IntValue>(42);

    auto visitor = JsonWriter(std::cout);
    data->accept(visitor);
}
