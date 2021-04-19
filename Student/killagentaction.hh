#ifndef KILLAGENTACTION_HH
#define KILLAGENTACTION_HH

#include "actioninterface.h"
#include "agent.hh"
#include "mainwindow.hh"

#include <memory>

class KillAgentAction: public Interface::ActionInterface
{
public:
    explicit KillAgentAction(std::shared_ptr<Agent> agent = nullptr, MainWindow* mw = nullptr);
    virtual ~KillAgentAction();

    virtual bool canPerform() const;

    virtual void perform();
private:
    std::shared_ptr<Agent> agent_ = nullptr;
    MainWindow* mainwindow_ = nullptr;
};

#endif // KILLAGENTACTION_HH
