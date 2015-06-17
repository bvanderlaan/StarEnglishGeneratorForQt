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

#ifndef LANGUAGESELECTOR_H
#define LANGUAGESELECTOR_H

#include <QObject>
#include <QTranslator>

namespace ImaginativeThinking
{
    namespace Translation
    {
        class LanguageSelector : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString emptyString READ getEmptyString NOTIFY selectedLanguageChanged)
            Q_PROPERTY( QString selectedLanguageCode READ getSelectedLanguageCode NOTIFY selectedLanguageChanged )
        public:
            explicit LanguageSelector(QObject *parent = 0);
            virtual ~LanguageSelector() {}

            QString getEmptyString() const;
            QString getSelectedLanguageCode() const;
            QString getTranslationFileBaseName() const;
            void setTrasnlationFileBaseName( const QString& baseName );

        public slots:
            void loadLanguage( const QString& languageCode );

        signals:
            void selectedLanguageChanged( const QString& language );
            void baseTranslationFileNameChanged( const QString& baseName );

        private:
            bool switchTranslator( const QString& lanugageCode );
            bool switchTranslator( QTranslator& translator, const QString& translationFile );
            void setSelectedLanguageCode( const QString& languageCode );
            QString m_selectedLanguage;
            QTranslator m_translator;
            QString m_baseTranslationFileName;
            QString m_translationFilePath;
        };
    }
}

#endif // LANGUAGESELECTOR_H
