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

#ifndef STARENGLISHGENERATOR_H
#define STARENGLISHGENERATOR_H

#include "TranslationGenerator.hpp"

namespace ImaginativeThinking
{
    namespace Translation
    {
        class StarEnglishGenerator : public TranslationGenerator
        {
            Q_OBJECT
            Q_PROPERTY(QString character READ getStarEnglishCharacter WRITE setStarEnglishCharacter NOTIFY starEnglishCharacterChanged)

        public:
            explicit StarEnglishGenerator( QObject *parent = 0);
            virtual ~StarEnglishGenerator() = default;

            QString getStarEnglishCharacter() const;
            void setStarEnglishCharacter( const QString& character );

        signals:
            void starEnglishCharacterChanged( const QString& character );

        protected:
            QString m_starEnglishCharacter;
            QString translateText( const QString& sourceText ) const override;
        };
    }
}

#endif // STARENGLISHGENERATOR_H
