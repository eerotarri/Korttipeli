#include "agent.hh"

Agent::Agent(QPushButton* button):
    name_("vittu")
{
    agent_selected_.button_ = button;
}

Agent::~Agent()
{

}

QString Agent::name() const
{
    return name_;
}

QString Agent::typeName() const
{
    return typeName_;
}

QString Agent::title() const
{
    return title_;
}

std::weak_ptr<Interface::Location> Agent::location() const
{
    return location_;
}

std::weak_ptr<Interface::Player> Agent::owner() const
{
    return owner_;
}

void Agent::setOwner(std::weak_ptr<Interface::Player> owner)
{
    // Stub
}

bool Agent::isCommon() const
{
    return isCommon_;
}

std::weak_ptr<Interface::Location> Agent::placement() const
{
    return location_;
}

void Agent::setPlacement(std::weak_ptr<Interface::Location> placement)
{
    location_ = placement;
}

unsigned short Agent::connections() const
{
    return  connections_;
}

void Agent::setConnections(unsigned short connections)
{
    connections_ = connections;
}

void Agent::modifyConnections(short change)
{
    // Stub
}
