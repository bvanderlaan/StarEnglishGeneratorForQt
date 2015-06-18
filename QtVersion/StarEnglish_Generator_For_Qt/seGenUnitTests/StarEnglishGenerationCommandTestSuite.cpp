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

#include <QTest>
#include <QSignalSpy>
#include "StarEnglishGenerationCommandTestSuite.hpp"
#include "StarEnglishGenerationCommand.hpp"
#include "StarEnglishGenerationCommandSkipIOCheck.hpp"
#include "StarEnglishGeneratorFake.h"

using namespace ImaginativeThinking::Translation::UnitTest;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerationCommandTestSuite::testGeneratingStarEnglishFileWithInvalidSourceFile()
{
    StarEnglishGenerationCommand command;
    QCOMPARE( command.getSourceFile().isEmpty(), true );
    command.setDestinationFile( "starEnglish.ts" );
    QSignalSpy generationCompletedSpy( &command, SIGNAL(generationCompleted(bool)));

    bool expected = false;
    bool actual = command.generate();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = generationCompletedSpy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );

    expected = false;
    actual = generationCompletedSpy.takeFirst().at(0).toBool();
    QCOMPARE ( actual, expected );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerationCommandTestSuite::testGeneratingStarEnglishFileWithInvalidDestinationFile()
{
    StarEnglishGenerationCommand command;
    QCOMPARE( command.getDestinationFile().isEmpty(), true );
    command.setSourceFile( "English.ts" );
    QSignalSpy generationCompletedSpy( &command, SIGNAL(generationCompleted(bool)));

    bool expected = false;
    bool actual = command.generate();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = generationCompletedSpy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );

    expected = false;
    actual = generationCompletedSpy.takeFirst().at(0).toBool();
    QCOMPARE ( actual, expected );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerationCommandTestSuite::testGeneratingStarEnglishFile()
{
    auto fakeGenerator = new StarEnglishGeneratorFake();
    fakeGenerator->m_generateReturnValue = true;

    StarEnglishGenerationCommandSkipIOCheck command( fakeGenerator, this );
    command.setSourceFile( "English.ts" );
    command.setDestinationFile( "starEnglish.ts" );
    QSignalSpy generationCompletedSpy( &command, SIGNAL(generationCompleted(bool)));

    bool expected = true;
    bool actual = command.generate();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = generationCompletedSpy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );

    expected = true;
    actual = generationCompletedSpy.takeFirst().at(0).toBool();
    QCOMPARE ( actual, expected );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerationCommandTestSuite::testGeneratingStarEnglishFileWithGeneratorError()
{
    auto fakeGenerator = new StarEnglishGeneratorFake();
    fakeGenerator->m_generateReturnValue = false;

    StarEnglishGenerationCommand command( fakeGenerator, this );
    command.setSourceFile( "English.ts" );
    command.setDestinationFile( "starEnglish.ts" );
    QSignalSpy generationCompletedSpy( &command, SIGNAL(generationCompleted(bool)));

    bool expected = false;
    bool actual = command.generate();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = generationCompletedSpy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );

    expected = false;
    actual = generationCompletedSpy.takeFirst().at(0).toBool();
    QCOMPARE ( actual, expected );
}
