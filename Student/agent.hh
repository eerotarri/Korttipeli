#ifndef AGENT_HH
#define AGENT_HH

#include "agentinterface.h"
#include "QPushButton"

class Agent: public Interface::AgentInterface
{
public:
    Agent();
    ~Agent();

private:
    const QColor color_ = Qt::red;

    struct agent_selected_{
        int x_ = 0;
        int y_ = 0;
        QPushButton* button_ = nullptr;

    };
};

#endif // AGENT_HH
