#ifndef AGENT_HH
#define AGENT_HH

#include "agentinterface.h"
#include "QPushButton"
#include "location.h"

struct ButtonInfo{
    int x_;
    int y_;
    QPushButton* button_;
};

class Agent: public Interface::AgentInterface
{
public:
    explicit Agent(QPushButton* button = nullptr);
    virtual ~Agent();

    virtual QString name() const;
    virtual QString typeName() const;
    virtual QString title() const;
    virtual std::weak_ptr<Interface::Location> location() const;
    virtual std::weak_ptr<Interface::Player> owner() const;
    virtual void setOwner(std::weak_ptr<Interface::Player> owner);
    virtual bool isCommon() const;
    virtual std::weak_ptr<Interface::Location> placement() const;
    virtual void setPlacement(std::weak_ptr<Interface::Location> placement);
    virtual unsigned short connections() const;
    virtual void setConnections(unsigned short connections);
    virtual void modifyConnections(short change);

private:
    const QColor color_ = Qt::red;

    ButtonInfo agent_selected_;

    QString name_;

    QString title_;

    QString typeName_;

    std::weak_ptr<Interface::Location> location_;

    std::weak_ptr<Interface::Player> owner_;

    unsigned short connections_;

    bool isCommon_;
};

#endif // AGENT_HH
