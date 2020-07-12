#ifndef NODE_H
#define NODE_H

#include <memory>
#include "Token.h"
#include "BaseVisitor.h"

struct Node {
    Node(const Position & pos) : pos(pos) {}
    virtual ~Node() = default;

    virtual void accept(BaseVisitor & visitor) = 0;

    Position pos;
};

#endif