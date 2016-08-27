#ifndef FFT_COMPONENT_HPP
#define FFT_COMPONENT_HPP

#include "NodeId.hpp"
#include "ComponentBase.hpp"

class FFTComponent : public ComponentBase {
public:
    FFTComponent(const NodeId& node);

private:
    NodeId  _node;
};


#endif