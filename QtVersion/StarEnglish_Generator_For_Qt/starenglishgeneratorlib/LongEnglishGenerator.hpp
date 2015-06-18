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

#ifndef LONGENGLISHGENERATOR_HPP
#define LONGENGLISHGENERATOR_HPP

#include "TranslationGenerator.hpp"

namespace ImaginativeThinking
{
    namespace Translation
    {
        class LongEnglishGenerator : public TranslationGenerator
        {
            Q_OBJECT
            Q_PROPERTY(QChar character READ getLongEnglishCharacter WRITE setLongEnglishCharacter NOTIFY longEnglishCharacterChanged)
        public:
            explicit LongEnglishGenerator(QObject *parent = 0);
            virtual ~LongEnglishGenerator() = default;

            QChar getLongEnglishCharacter() const;
            void setLongEnglishCharacter( const QChar& character );

        signals:
            void longEnglishCharacterChanged( const QChar& character );

        protected:
            QChar m_longEnglishCharacter;
            QString translateText(const QString& sourceText) const override;
            QString getLongEnglishMarker(const QString& sourceText ) const;
            QString removeHTMLTags( const QString& sourceText ) const;
        };
    }
}

#endif // LONGENGLISHGENERATOR_HPP
