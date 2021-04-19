#include "swindleagentaction.hh"

SwindleAgentAction::SwindleAgentAction(std::shared_ptr<Agent> agent, MainWindow *mw)
{
    agent_ = agent;
    mainwindow_ = mw;
}

SwindleAgentAction::~SwindleAgentAction()
{

}

bool SwindleAgentAction::canPerform() const
{
    if (agent_->getButton()->isEnabled()) {
        return true;
    } else {
        return  false;
    }
}

void SwindleAgentAction::perform()
{
    mainwindow_->swindleAction();
}
