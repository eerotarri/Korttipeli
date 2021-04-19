#ifndef AGENT_HH
#define AGENT_HH

#include "agentinterface.h"
#include "QPushButton"
#include "location.h"
#include "QGraphicsScene"


class Agent: public Interface::AgentInterface
{
public:
    explicit Agent(QPushButton* button = nullptr,
                   std::weak_ptr<Interface::Player> ownr = {}, std::weak_ptr<Interface::Location> lctn = {},
                   unsigned short pts = 0, QString name = "", QString typeName = "", QString title = "", QGraphicsScene* scene = nullptr);
    virtual ~Agent();

    // Pure virtual method impletemtations from parent classes AgentInterface and CardInterface
    virtual QString name() const;
    virtual QString typeName() const;
    virtual QString title() const;
    virtual std::weak_ptr<Interface::Location> location() const;
    virtual std::weak_ptr<Interface::Player> owner() const;
    virtual void setOwner(std::weak_ptr<Interface::Player> owner);
    virtual bool isCommon() const;
    virtual std::weak_ptr<Interface::Location> placement() const;
    virtual void setButton(QPushButton* button);
    virtual QPushButton* getButton();
    virtual void setPlacement(std::weak_ptr<Interface::Location> placement);
    virtual unsigned short connections() const;
    virtual void setConnections(unsigned short connections);
    virtual void modifyConnections(short change);

    QGraphicsScene *scene();
    virtual void setScene(QGraphicsScene* scene);


private:

    QString name_;

    QString title_;

    QString typeName_;

    std::weak_ptr<Interface::Location> location_;

    std::weak_ptr<Interface::Player> owner_;

    unsigned short connections_;

    bool isCommon_ = true;

    QPushButton* button_;

    QGraphicsScene* scene_;
};

#endif // AGENT_HH
