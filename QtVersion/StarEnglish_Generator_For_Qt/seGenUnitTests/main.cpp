/*
 * Copyright 2015 ImaginativeThinking
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QtTest/QTest>
#include <QDebug>
#include <QMetaMethod>
#include "StarEnglishGeneratorTestSuite.h"
#include "StarEnglishGeneratorModelTestSuite.h"
#include "LongEnglishGeneratorTestSuite.hpp"
#include "StarEnglishGenerationCommandTestSuite.hpp"
#include "LongEnglishGenerationCommandTestSuite.hpp"

void displayMessage( int numOfTests, int numOfFailedTests )
{
    qDebug() << "********* Summary of testing *********";
    qDebug() << QString( "Totals: %1 passed, %2 failed, %3 total tests" ).arg( numOfTests - numOfFailedTests ).arg( numOfFailedTests ).arg( numOfTests ).toStdString().c_str();
    if ( numOfFailedTests == 0 )
    {
        qDebug( QString("\r\nYOU HAVE NO (0) FAILED TESTS, YOU ARE AWESOME!\r\n").toStdString().c_str() );
    }
    else
    {
        qDebug( QString("\r\n!!!!!!!!!! You have %1 failed tests (scroll up), please fix them before commiting !!!!!!!!!!\r\n").arg( numOfFailedTests ).toStdString().c_str() );
    }
    qDebug() << "********* Finished Summary of testing *********";
}
int getNumberOfTests( QObject* testSuite )
{
    int numberOfTests(0);

    if ( testSuite != nullptr )
    {
        int methodCount = testSuite->metaObject()->methodCount();
        for( int i = 0; i < methodCount; ++i )
        {
            QMetaMethod method = testSuite->metaObject()->method( i );
            if( method.access() == QMetaMethod::Access::Private && method.methodType() == QMetaMethod::MethodType::Slot )
            {
                ++numberOfTests;
            }
        }
        --numberOfTests; // do not count "_q_reregisterTimers" inherited private slot from QObject
    }

    return numberOfTests;
}
int main( int argc, char** argv )
{
    // This is the same as QTEST_APPLIST_MAIN() but for mutliple test classes.
   int numOfTests( 0 );
   int numOfFailedTests( 0 );
   auto ASSERT_TEST = [&numOfFailedTests, &numOfTests, argc, argv](QObject* testSuite) {
#ifdef QT_DEBUG
       numOfFailedTests += QTest::qExec( testSuite );
#else
       numOfFailedTests += QTest::qExec( testSuite, argc, argv );
#endif
       numOfTests += getNumberOfTests( testSuite );
       delete testSuite;
   };

   ASSERT_TEST( new ImaginativeThinking::Translation::UnitTest::StarEnglishGeneratorTestSuite() );
   ASSERT_TEST( new ImaginativeThinking::Translation::UnitTest::StarEnglishGeneratorModelTestSuite() );
   ASSERT_TEST( new ImaginativeThinking::Translation::UnitTest::LongEnglishGeneratorTestSuite() );
   ASSERT_TEST( new ImaginativeThinking::Translation::UnitTest::StarEnglishGenerationCommandTestSuite() );
   ASSERT_TEST( new ImaginativeThinking::Translation::UnitTest::LongEnglishGenerationCommandTestSuite() );

   displayMessage( numOfTests, numOfFailedTests );
   return numOfFailedTests;
}
