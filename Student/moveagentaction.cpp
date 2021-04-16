#include "moveagentaction.hh"

MoveAgentAction::MoveAgentAction(std::shared_ptr<Agent> agent, MainWindow *mw)
{
    agent_ = agent;
    mainwindow_ = mw;
}

MoveAgentAction::~MoveAgentAction()
{

}

bool MoveAgentAction::canPerform() const
{
    if (agent_->getButton()->isEnabled()) {
        return true;
    } else {
        return  false;
    }
}

void MoveAgentAction::perform()
{
    mainwindow_->moveAction();
}
