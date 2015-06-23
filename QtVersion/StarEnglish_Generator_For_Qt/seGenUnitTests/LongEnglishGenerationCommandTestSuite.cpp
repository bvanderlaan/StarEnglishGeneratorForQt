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
#include "LongEnglishGenerationCommandTestSuite.hpp"
#include "LongEnglishGenerationCommand.hpp"
#include "LongEnglishGenerationCommandSkipIOCheck.hpp"
#include "LongEnglishGeneratorFake.hpp"

using namespace ImaginativeThinking::Translation::UnitTest;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void LongEnglishGenerationCommandTestSuite::testGeneratingLongEnglishFileWithInvalidSourceFile()
{
    LongEnglishGenerationCommand command;
    QCOMPARE( command.getSourceFile().isEmpty(), true );
    command.setDestinationFile( "LongEnglish.ts" );
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
void LongEnglishGenerationCommandTestSuite::testGeneratingLongEnglishFileWithInvalidDestinationFile()
{
    LongEnglishGenerationCommand command;
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
void LongEnglishGenerationCommandTestSuite::testGeneratingLongEnglishFile()
{
    auto fakeGenerator = new LongEnglishGeneratorFake();
    fakeGenerator->m_generateReturnValue = true;

    LongEnglishGenerationCommandSkipIOCheck command( fakeGenerator, this );
    command.setSourceFile( "English.ts" );
    command.setDestinationFile( "LongEnglish.ts" );
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
void LongEnglishGenerationCommandTestSuite::testGeneratingLongEnglishFileWithGeneratorError()
{
    auto fakeGenerator = new LongEnglishGeneratorFake();
    fakeGenerator->m_generateReturnValue = false;

    LongEnglishGenerationCommand command( fakeGenerator, this );
    command.setSourceFile( "English.ts" );
    command.setDestinationFile( "LongEnglish.ts" );
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
void LongEnglishGenerationCommandTestSuite::testGeneratingLongEnglishFileWhenSourceAndDestinationFilesAreTheSame()
{
    auto fakeGenerator = new LongEnglishGeneratorFake();
    fakeGenerator->m_generateReturnValue = true;

    LongEnglishGenerationCommandSkipIOCheck command( fakeGenerator, this );
    command.setSourceFile( "English.ts" );
    command.setDestinationFile( "ENGLISH.ts" );
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

