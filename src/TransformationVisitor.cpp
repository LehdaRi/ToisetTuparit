#include "TransformationVisitor.hpp"
#include "Node.hpp"


using namespace Eigen;


TransformationVisitor::TransformationVisitor() :
    mode(0),
    magnitude(0.0f),
    time(0.0)
{}

void TransformationVisitor::operator()(TransformationComponent& component) {
    if (component.parent_) {
        auto& ptc = component.parent_.ref().getComponent<TransformationComponent>();
        component.mCumulative_ = ptc.mCumulative_ * component.m_;
    }
    else
        component.mCumulative_ = component.m_;
}
