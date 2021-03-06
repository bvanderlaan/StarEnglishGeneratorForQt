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

#include "StarEnglishGeneratorModelTestSuite.h"
#include "StarEnglishGeneratorModel.h"
#include <QtTest/QTest>
#include <QSignalSpy>

using namespace ImaginativeThinking::Translation::UnitTest;
using namespace ImaginativeThinking::Translation;

void StarEnglishGeneratorModelTestSuite::testSetSourceFile()
{
    StarEnglishGeneratorModel model;
    QSignalSpy spy( &model, SIGNAL(sourceFileChanged(QString)));
    QCOMPARE( model.getSourceFile().isEmpty(), true );

    QString expected = "file.ts";
    model.setSourceFile( expected );

    QString actual = model.getSourceFile();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = spy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );
}
void StarEnglishGeneratorModelTestSuite::testSetSourceFileWithNoExtension()
{
    StarEnglishGeneratorModel model;
    QSignalSpy spy( &model, SIGNAL(sourceFileChanged(QString)));
    QCOMPARE( model.getSourceFile().isEmpty(), true );

    model.setSourceFile( "file" );

    QString expected = "file";
    QString actual = model.getSourceFile();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = spy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );
}
void StarEnglishGeneratorModelTestSuite::testSetSourceFileToSameValue()
{
    QString expected = "file.ts";
    StarEnglishGeneratorModel model;
    model.setSourceFile( expected );
    QSignalSpy spy( &model, SIGNAL(sourceFileChanged(QString)));
    QCOMPARE( model.getSourceFile(), expected );

    model.setSourceFile( expected );

    QString actual = model.getSourceFile();
    QCOMPARE ( actual, expected );

    int expectedCount = 0;
    int actualCount = spy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );
}
void StarEnglishGeneratorModelTestSuite::testSetDestinationFile()
{
    StarEnglishGeneratorModel model;
    QSignalSpy spy( &model, SIGNAL(destinationFileChanged(QString)));
    QCOMPARE( model.getDestinationFile().isEmpty(), true );

    QString expected = "file.ts";
    model.setDestinationFile( expected );

    QString actual = model.getDestinationFile();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = spy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );
}
void StarEnglishGeneratorModelTestSuite::testSetDestinationFileWithNoExtension()
{
    StarEnglishGeneratorModel model;
    QSignalSpy spy( &model, SIGNAL(destinationFileChanged(QString)));
    QCOMPARE( model.getDestinationFile().isEmpty(), true );

    model.setDestinationFile( "file" );

    QString expected = "file.ts";
    QString actual = model.getDestinationFile();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = spy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );
}
void StarEnglishGeneratorModelTestSuite::testSetDestinationFileToSameValue()
{
    QString expected = "file.ts";
    StarEnglishGeneratorModel model;
    model.setDestinationFile( expected );
    QSignalSpy spy( &model, SIGNAL(destinationFileChanged(QString)));
    QCOMPARE( model.getDestinationFile(), expected );

    model.setDestinationFile( expected );

    QString actual = model.getDestinationFile();
    QCOMPARE ( actual, expected );

    int expectedCount = 0;
    int actualCount = spy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );
}
void StarEnglishGeneratorModelTestSuite::testDestinationFileWithEmptyString()
{
    StarEnglishGeneratorModel model;
    model.setDestinationFile( "test.ts" );
    QCOMPARE( model.getDestinationFile(), QString("test.ts") );

    QSignalSpy spy( &model, SIGNAL(destinationFileChanged(QString)));
    model.setDestinationFile( "" );

    QString expected = "";
    QString actual = model.getDestinationFile();
    QCOMPARE ( actual, expected );

    int expectedCount = 1;
    int actualCount = spy.count();
    QVERIFY2( actualCount == expectedCount, QString("Expected [%1], Actual [%2]").arg(expectedCount).arg(actualCount).toStdString().c_str() );
}
