#ifndef CPL_VALUEVISITOR_HPP
#define CPL_VALUEVISITOR_HPP

#include "Value.hpp"

class ValueVisitor {
public:

    virtual ~ValueVisitor() = default;

    virtual void visit(const BoolValue& b) = 0;
    virtual void visit(const IntValue& i) = 0;
    virtual void visit(const StringValue& s) = 0;
    virtual void visit(const SeqValue& s) = 0;
    virtual void visit(const StructValue& s) = 0;
};

#endif
