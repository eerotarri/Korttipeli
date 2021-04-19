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
    // Tähän tarkastelut milloin voi suorittaa tapon
    unsigned int size = 0;
    switch (agent_->location().lock()->id()) {
        case 1: {
            // Agent is in Castle
            size = mainwindow_->getSceneItemSize(1);
            break;
        }
        case 2: {
            // Agent is in Market
            size = mainwindow_->getSceneItemSize(2);
            break;
        }
        case 3: {
            // Agent is in Forest
            size = mainwindow_->getSceneItemSize(3);
            break;
        }
        case 4: {
            // Agent is in Slums
            size = mainwindow_->getSceneItemSize(4);
            break;
        }
    }

    qDebug() << size;

    if (size > 10) {
        return true;
    } else {
        qDebug() << "ei tappo natsaa";
        return  false;
    }
}

void KillAgentAction::perform()
{
    mainwindow_->killAction();
}
