#ifndef CPL_JSONWRITER_HPP
#define CPL_JSONWRITER_HPP

// <<<
#include "ValueVisitor.hpp"
#include "Value.hpp"

#include <iosfwd>

class JsonWriter : public ValueVisitor {
public:

    JsonWriter(std::ostream& stream);

    void visit(const BoolValue& b) override;
    void visit(const IntValue& i) override;
    void visit(const StringValue& s) override;
    void visit(const SeqValue& s) override;
    void visit(const StructValue& s) override;

private:

    std::ostream& stream_;
};

// >>>
#endif
