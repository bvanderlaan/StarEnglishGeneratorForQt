#include <QString>
#include <QtTest>

class SeGenUnitTestsTest : public QObject
{
    Q_OBJECT

public:
    SeGenUnitTestsTest();

private Q_SLOTS:
    void testCase1();
};

SeGenUnitTestsTest::SeGenUnitTestsTest()
{
}

void SeGenUnitTestsTest::testCase1()
{
    QVERIFY2(true, "Failure");
}

QTEST_APPLESS_MAIN(SeGenUnitTestsTest)

#include "tst_SeGenUnitTestsTest.moc"
