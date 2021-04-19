#ifndef SWINDLEAGENTACTION_HH
#define SWINDLEAGENTACTION_HH

#include "actioninterface.h"
#include "agent.hh"
#include "mainwindow.hh"

#include <memory>

class SwindleAgentAction: public Interface::ActionInterface
{
public:
    explicit SwindleAgentAction(std::shared_ptr<Agent> agent = nullptr, MainWindow* mw = nullptr);
    virtual ~SwindleAgentAction();

    virtual bool canPerform() const;

    virtual void perform();
private:

    std::shared_ptr<Agent> agent_ = nullptr;
    MainWindow* mainwindow_ = nullptr;
};

#endif // SWINDLEAGENTACTION_HH
