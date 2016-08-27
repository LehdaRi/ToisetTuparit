#ifndef FFT_COMPONENT_HPP
#define FFT_COMPONENT_HPP

#include "Node.hpp"
#include "NodeId.hpp"
#include "ComponentBase.hpp"

class FFTComponent : public ComponentBase {
public:
	friend class FFTVisitor;

    FFTComponent(const NodeId& node);

private:
    NodeId  _node;
};


#endif