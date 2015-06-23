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

#ifndef STARENGLISHGENERATORTESTSUITE_H
#define STARENGLISHGENERATORTESTSUITE_H

#include <QObject>

namespace ImaginativeThinking
{
    namespace Translation
    {
        namespace UnitTest
        {
            class StarEnglishGeneratorTestSuite : public QObject
            {
                Q_OBJECT
            public:
                explicit StarEnglishGeneratorTestSuite() {}

            private slots:
                void testGeneratingStarEnglishFileWithEmptySourceFile();
                void testGeneratingStarEnglishFileWithExistingDestinationFile();
                void testGeneratingStarEnglishFileWithNonExistingDestinationFile();
                void testGeneratingStarEnglishWhenEntryIsAlreadyTranslated();
                void testGeneratingStarEnglishWhenTranslationAttributeNotUnfinished();
                void testGeneratingStarEnglishMultipleContextMultipleMessages();
                void testGeneratingStarEnglishWithMissOrderedTags();
                void testGeneratingStarEnglishWithMalFormedXML();
                void testGeneratingStarEnglishWithIncorrectXML();
                void testToMakeSureThatTheGeneratorSwitchedTheLanguageTypeAttribute();
                void testToMakeSureThatTheGeneratorHandelsHTMLStrings();
                void testToMakeSureThatTheGeneratorHandelsTheLocationTagUsedByQML();
                void testToMakeSureThatTheGeneratorHandlesContextComments();
                void testToMakeSureThatTheGeneratorHandelsExtraComments();
                void testGeneratingStarEnglishWithNumerusFormSourceString();
                void testGeneratingStarEnglishWithArgumentPlaceHolders();
                void testGeneratingStarEnglishWithAltShortCutMarkers();
            };
        }
    }
}

#endif // STARENGLISHGENERATORTESTSUITE_H
