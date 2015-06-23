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

#include "StarEnglishGeneratorTestSuite.h"
#include "StarEnglishGenerator.h"
#include <QBuffer>
#include <QtTest/QTest>

using namespace ImaginativeThinking::Translation::UnitTest;
using namespace ImaginativeThinking::Translation;

void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishFileWithEmptySourceFile()
{
   StarEnglishGenerator generator;

   QByteArray source;
   QByteArray destination;
   QBuffer sourceIODevice( &source );
   QBuffer destinationIODevice( &destination );

   bool expected = false;
   bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
   QCOMPARE ( actual, expected );

   int expectedSize = 0;
   int actualSize = destination.size();
   QVERIFY2( expectedSize == actualSize, QString("Expected [%1], Actual [%2]").arg(expectedSize).arg(actualSize).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishFileWithExistingDestinationFile()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>HELLO WORLD</source>"
                  "<translation type=\"unfinished\" />"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    destination.append("FUBAR");
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>HELLO WORLD</source>"
                           " <translation>*HELLO WORLD*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";

    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishFileWithNonExistingDestinationFile()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>HELLO WORLD</source>"
                  "<translation type=\"unfinished\" someOtherAttribute=\"true\">"
                  "</translation>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>HELLO WORLD</source>"
                           " <translation someOtherAttribute=\"true\">*HELLO WORLD*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishWhenEntryIsAlreadyTranslated()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>HELLO WORLD</source>"
                  "<translation>Bonjour Le Monde</translation>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    // Notice that we kill the translation and replace it with Star English
    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>HELLO WORLD</source>"
                           " <translation>*HELLO WORLD*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishWhenTranslationAttributeNotUnfinished()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>HELLO WORLD</source>"
                  "<translation type=\"finished\" someOtherAttribute=\"true\">Hello World</translation>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    // Notice that we kill the translation and replace it with Star English
    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>HELLO WORLD</source>"
                           " <translation someOtherAttribute=\"true\">*HELLO WORLD*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishMultipleContextMultipleMessages()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>HELLO WORLD</source>"
                  "<translation type=\"unfinished\" />"
                  "</message>"
                  "<message>"
                  "<source>FU BAR</source>"
                  "<translation type=\"unfinished\" />"
                  "</message>"
                  "</context>"
                  "<context>"
                  "<message>"
                  "<source>Test Message</source>"
                  "<translation type=\"unfinished\" />"
                  "</message>"
                  "<message>"
                  "<source>One Two Three</source>"
                  "<translation type=\"unfinished\" />"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>HELLO WORLD</source>"
                           " <translation>*HELLO WORLD*</translation>"
                           " </message>"
                           " <message>"
                           " <source>FU BAR</source>"
                           " <translation>*FU BAR*</translation>"
                           " </message>"
                           " </context>"
                           " <context>"
                           " <message>"
                           " <source>Test Message</source>"
                           " <translation>*Test Message*</translation>"
                           " </message>"
                           " <message>"
                           " <source>One Two Three</source>"
                           " <translation>*One Two Three*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";

    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishWithMissOrderedTags()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<translation type=\"unfinished\">Hello World</translation>"
                  "<source>HELLO WORLD</source>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    // Notice that it works and that the order did not change
    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <translation>*HELLO WORLD*</translation>"
                           " <source>HELLO WORLD</source>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishWithMalFormedXML()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("Hello World");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = false;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishWithIncorrectXML()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<?xml version=\"1.0\" encoding=\"utf-8\"?>"
                  "<root>"
                  "<message>Not what you were expecting eh?</message>"
                  "</root>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = false;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE( actual, expected );

    QString expectedData = "";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testToMakeSureThatTheGeneratorSwitchedTheLanguageTypeAttribute()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fr_FR\">"
                  "<context>"
                  "<message>"
                  "<source>HELLO WORLD</source>"
                  "<translation type=\"unfinished\">Hello World</translation>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>HELLO WORLD</source>"
                           " <translation>*HELLO WORLD*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testToMakeSureThatTheGeneratorHandelsHTMLStrings()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>HELLO &lt;b&gt;WORLD&lt;b&gt;</source>"
                  "<translation type=\"unfinished\">Hello World</translation>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>HELLO &lt;b>WORLD&lt;b></source>"
                           " <translation>*HELLO &lt;b>WORLD&lt;b>*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testToMakeSureThatTheGeneratorHandelsTheLocationTagUsedByQML()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<location filename=\"starenglishgeneratorapp/main.qml\" line=\"34\"/>"
                  "<source>Hello World</source>"
                  "<translation type=\"unfinished\"></translation>"
                  "</message>"
                  "</context>"
                  "</TS>");

    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <location line=\"34\" filename=\"starenglishgeneratorapp/main.qml\"/>"
                           " <source>Hello World</source>"
                           " <translation>*Hello World*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";

    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testToMakeSureThatTheGeneratorHandlesContextComments()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>&amp;File</source>"
                  "<comment>This is just showing how a context comment looks in the TS file.</comment>"
                  "<translation type=\"unfinished\"></translation>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>&amp;File</source>"
                           " <comment>This is just showing how a context comment looks in the TS file.</comment>"
                           " <translation>*&amp;File*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testToMakeSureThatTheGeneratorHandelsExtraComments()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>Hello World</source>"
                  "<extracomment>This is an example of an extra comment ment for the translator.</extracomment>"
                  "<translation type=\"unfinished\"></translation>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>Hello World</source>"
                           " <extracomment>This is an example of an extra comment ment for the translator.</extracomment>"
                           " <translation>*Hello World*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishWithNumerusFormSourceString()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message numerus=\"yes\">"
                  "<source>Month(s)</source>"
                  "<translation type=\"unfinished\">"
                  "<numerusform></numerusform>"
                  "<numerusform></numerusform>"
                  "</translation>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message numerus=\"yes\">"
                           " <source>Month(s)</source>"
                           " <translation>"
                           " <numerusform>*Month*</numerusform>"
                           " <numerusform>*Months*</numerusform>"
                           " </translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishWithArgumentPlaceHolders()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>Copyright %1 ImaginativeThinking</source>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>Copyright %1 ImaginativeThinking</source>"
                           " <translation>*Copyright %1 ImaginativeThinking*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
void StarEnglishGeneratorTestSuite::testGeneratingStarEnglishWithAltShortCutMarkers()
{
    StarEnglishGenerator generator;

    QByteArray source;
    source.append("<TS language=\"fo_FO\">"
                  "<context>"
                  "<message>"
                  "<source>&amp;File</source>"
                  "</message>"
                  "</context>"
                  "</TS>");
    QByteArray destination;
    QBuffer sourceIODevice( &source );
    QBuffer destinationIODevice( &destination );

    bool expected = true;
    bool actual = generator.generate( &sourceIODevice, &destinationIODevice );
    QCOMPARE ( actual, expected );

    QString expectedData = "<TS language=\"fo_FO\">"
                           " <context>"
                           " <message>"
                           " <source>&amp;File</source>"
                           " <translation>*&amp;File*</translation>"
                           " </message>"
                           " </context>"
                           " </TS>";
    QString actualData = QString(destination).simplified();
    QVERIFY2( expectedData.compare(actualData, Qt::CaseInsensitive) == 0, QString("\nExpected [%1], \nActual [%2]").arg(expectedData).arg(actualData).toStdString().c_str() );
}
