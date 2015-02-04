#ifndef STARENGLISHGENERATORMODELTESTER_H
#define STARENGLISHGENERATORMODELTESTER_H

#include "StarEnglishGeneratorModel.h"

namespace ImaginativeThinking
{
    namespace Translation
    {
        class StarEnglishGeneratorModelTester : public StarEnglishGeneratorModel
        {
        public:
            explicit StarEnglishGeneratorModelTester( StarEnglishGenerator* generator, QObject* parent );
            ~StarEnglishGeneratorModelTester(){}

            bool m_doesFileExist;

        protected:
            bool doesFileExist(QFileInfo file) const override;
        };
    }
}

#endif // STARENGLISHGENERATORMODELTESTER_H
