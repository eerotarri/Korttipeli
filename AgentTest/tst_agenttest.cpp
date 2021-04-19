#include <QtTest>
#include <QCoreApplication>

#include "agent.hh"

class AgentTest : public QObject
{
    Q_OBJECT

public:
    AgentTest();
    ~AgentTest();

private slots:
    void initTestCase();
    void cleanupTestCase();
    void test_case1();

};

AgentTest::AgentTest()
{

}

AgentTest::~AgentTest()
{

}

void AgentTest::initTestCase()
{

}

void AgentTest::cleanupTestCase()
{

}

void AgentTest::test_case1()
{

}

QTEST_MAIN(AgentTest)

#include "tst_agenttest.moc"
