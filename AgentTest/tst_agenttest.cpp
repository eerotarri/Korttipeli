#include <QtTest>
#include <QCoreApplication>

#include "agent.hh"
#include "game.h"
#include "location.h"
#include "player.h"

class AgentTest : public QObject
{
    Q_OBJECT

public:
    AgentTest();
    ~AgentTest();

private slots:
    void createAgentCase();

};

AgentTest::AgentTest()
{

}

AgentTest::~AgentTest()
{

}

void AgentTest::createAgentCase()
{
    auto g = std::make_shared<Interface::Game>();
    g->addPlayer("TestName");
    auto l = std::make_shared<Interface::Location>(0, "TestLocation");
    g->addLocation(l);
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setFont(QFont());

    QPushButton* b =  new QPushButton("TestButton");

    std::shared_ptr<Agent> agent = std::make_shared<Agent>(b, g->players().at(0), l, 0, "TestName", "TestTypeName", "TestTitle", scene);
    QCOMPARE(agent->getButton()->text(), "TestButton");
    QCOMPARE(agent->name(), "TestName");
    QCOMPARE(agent->title(), "TestTitle");
    QCOMPARE(agent->typeName(), "TestTypeName");
    QCOMPARE(agent->scene()->font(), QFont());
    QCOMPARE(agent->location().lock()->id(), 0);
    QCOMPARE(agent->location().lock()->name(), "TestLocation");
    QCOMPARE(agent->owner().lock(), g->players().at(0));



}

QTEST_MAIN(AgentTest)

#include "tst_agenttest.moc"
