#ifndef STARENGLISHGENERATORMODELTESTSUITE_H
#define STARENGLISHGENERATORMODELTESTSUITE_H

#include <QObject>

namespace ImaginativeThinking
{
    namespace Translation
    {
        namespace UnitTest
        {
            class StarEnglishGeneratorModelTestSuite : public QObject
            {
                Q_OBJECT
            public:
                explicit StarEnglishGeneratorModelTestSuite() {}
                ~StarEnglishGeneratorModelTestSuite() {}

            private slots:
                void testSetSourceFile();
                void testSetSourceFileWithNoExtension();
                void testSetSourceFileToSameValue();
                void testSetDestinationFile();
                void testSetDestinationFileWithNoExtension();
                void testSetDestinationFileToSameValue();
                void testDestinationFileWithEmptyString();
            };
        }
    }
}

#endif // STARENGLISHGENERATORMODELTESTSUITE_H
