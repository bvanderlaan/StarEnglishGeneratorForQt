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

#ifndef LONGENGLISHGENERATIONCOMMAND_HPP
#define LONGENGLISHGENERATIONCOMMAND_HPP

#include <QObject>
#include "BaseGenerationCommand.hpp"

namespace ImaginativeThinking
{
    namespace Translation
    {
        class TranslationGenerator;
        class LongEnglishGenerationCommand : public BaseGenerationCommand
        {
            Q_OBJECT
        public:
            explicit LongEnglishGenerationCommand(QObject *parent = 0);
            explicit LongEnglishGenerationCommand(TranslationGenerator* generator, QObject *parent = 0);
            virtual ~LongEnglishGenerationCommand() {}

        public slots:
            bool generate() override;

        private:
            TranslationGenerator* m_generator;
        };
    }
}

#endif // LONGENGLISHGENERATIONCOMMAND_HPP
