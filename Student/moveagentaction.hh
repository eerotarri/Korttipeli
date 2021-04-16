#ifndef MOVEAGENTACTION_HH
#define MOVEAGENTACTION_HH

#include "actioninterface.h"
#include "agent.hh"
#include "mainwindow.hh"

#include <memory>

class MoveAgentAction: public Interface::ActionInterface
{
public:
    explicit MoveAgentAction(std::shared_ptr<Agent> agent = nullptr, MainWindow* mw = nullptr);
    virtual ~MoveAgentAction();

    virtual bool canPerform() const;

    virtual void perform();

private:

    std::shared_ptr<Agent> agent_ = nullptr;
    MainWindow* mainwindow_ = nullptr;

};

#endif // MOVEAGENTACTION_HH
