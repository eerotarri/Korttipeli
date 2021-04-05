#include "agent.hh"

Agent::Agent(QPushButton* button, int x_in_scene, int y_in_scene,
             std::weak_ptr<Interface::Player> ownr, std::weak_ptr<Interface::Location> lctn,
             unsigned short pts):
    name_("card_name"), title_("card_title"),typeName_("card_type"), isCommon_(true)
{
    button_ = button;
    x_ = x_in_scene;
    y_ = y_in_scene;
    location_ = lctn;
    connections_ = pts;
    owner_ = ownr;
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
    owner_ = owner;
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
    connections_ += change;
}
