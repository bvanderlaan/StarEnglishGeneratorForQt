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

#ifndef LONGENGLISHGENERATORTESTSUITE_HPP
#define LONGENGLISHGENERATORTESTSUITE_HPP

#include <QObject>

namespace ImaginativeThinking
{
    namespace Translation
    {
        namespace UnitTest
        {
            class LongEnglishGeneratorTestSuite : public QObject
            {
                Q_OBJECT
            public:
                explicit LongEnglishGeneratorTestSuite(QObject *parent = 0) : QObject( parent ) {}

            private slots:
                void testGeneratingLongEnglishFileWithEmptySourceFile();
                void testGeneratingLongEnglishFileWithExistingDestinationFile();
                void testGeneratingLongEnglishFileWithNonExistingDestinationFile();
                void testGeneratingLongEnglishWhenEntryIsAlreadyTranslated();
                void testGeneratingLongEnglishWhenTranslationAttributeNotUnfinished();
                void testGeneratingLongEnglishMultipleContextMultipleMessages();
                void testGeneratingLongEnglishWithMissOrderedTags();
                void testGeneratingLongEnglishWithMalFormedXML();
                void testGeneratingLongEnglishWithIncorrectXML();
                void testToMakeSureThatTheGeneratorSwitchedTheLanguageTypeAttribute();
                void testToMakeSureThatTheGeneratorHandelsHTMLStrings();
                void testToMakeSureThatTheGeneratorHandelsTheLocationTagUsedByQML();
                void testToMakeSureThatTheGeneratorHandlesContextComments();
                void testToMakeSureThatTheGeneratorHandelsExtraComments();
                void testGeneratingLongEnglishWithNumerusFormSourceString();
            };
        }
    }
}

#endif // LONGENGLISHGENERATORTESTSUITE_HPP
