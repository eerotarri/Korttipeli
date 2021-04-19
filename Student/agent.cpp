#include "agent.hh"

Agent::Agent(QPushButton* button,
             std::weak_ptr<Interface::Player> ownr, std::weak_ptr<Interface::Location> lctn,
             unsigned short pts, QString name, QString typeName, QString title, QGraphicsScene* scene)
{
    button_ = button;
    name_ = name;
    title_ = title;
    typeName_ = typeName;
    location_ = lctn;
    connections_ = pts;
    owner_ = ownr;
    scene_ = scene;
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

void Agent::setButton(QPushButton *button)
{
    button_ = button;
}

QPushButton *Agent::getButton()
{
    return button_;
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

QGraphicsScene *Agent::scene()
{
    return scene_;
}

void Agent::setScene(QGraphicsScene *scene)
{
    scene_ = scene;
}
