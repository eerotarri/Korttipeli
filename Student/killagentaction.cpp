#include "killagentaction.hh"

#include <QDebug>

KillAgentAction::KillAgentAction(std::shared_ptr<Agent> agent, MainWindow *mw)
{
    agent_ = agent;
    mainwindow_ = mw;
}

KillAgentAction::~KillAgentAction()
{
}

bool KillAgentAction::canPerform() const
{
    // Katsoo, ettei agentti ole yksin sijainnissaan
    auto agents = agent_->location().lock()->agents();

    // Katsoo, että agentin seurassa on vastustajan agentti
    bool has_enemies = false;
    for (auto agent : agents) {
        if (agent->owner().lock() != agent_->owner().lock()) {
            has_enemies = true;
        }
    }

    if (agents.size() >= 2 && has_enemies) {
        return true;
    } else {
        return  false;
    }
}

void KillAgentAction::perform()
{
    mainwindow_->killAction();
}
