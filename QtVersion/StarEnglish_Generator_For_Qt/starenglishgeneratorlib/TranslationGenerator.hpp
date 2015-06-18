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

#ifndef TRANSLATIONGENERATOR_HPP
#define TRANSLATIONGENERATOR_HPP

#include <QObject>

class QIODevice;
class QDomNode;
class QDomDocument;
class QDomNodeList;
class QDomText;

namespace ImaginativeThinking
{
    namespace Translation
    {
        class TranslationGenerator : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString languageCode READ getLanguageCode WRITE setLanguageCode NOTIFY languageCodeChanged)
        public:
            explicit TranslationGenerator(QObject *parent = 0);
            virtual ~TranslationGenerator() = default;

            virtual bool generate( QIODevice* source, QIODevice* destination );

            QString getLanguageCode() const;
            void setLanguageCode( const QString& code );

        signals:
            void languageCodeChanged( const QString& languageCode );

        protected:
            QDomDocument* m_sourceDocument;
            QString m_languageCode;
            const QString m_languageAttributeName;
            const QString m_rootTagName;
            const QString m_sourceTagName;
            const QString m_translationTagName;
            const QString m_pluralOrSignalarFormAttributeName;
            const QString m_pluralOrSignalarFormTagName;
            const QString m_typeAttributeName;
            const QString m_messageRootTagName;

            bool isSourceFileValid( QIODevice* source ) const;
            bool openSourceAndDestinationFiles(QIODevice* source, QIODevice* destination);
            bool openSourceDom( QIODevice* source );
            virtual bool processSourceFile();
            virtual bool processRootNode();
            virtual bool processRootNode( QDomNode& rootNode );
            virtual bool processMessageNodes();
            virtual bool processMessageNode( QDomNode& messageTag );
            virtual QString translateText( const QString& sourceText ) const = 0;
            virtual void updateTagDataWithSinglarForm( QDomNode tag, const QString& sourceText );
            virtual void updateTagDataWithPluralForm( QDomNode tag, const QString& sourceText );
            bool supportsPluralForm( QDomNode& messageNode ) const;
            QDomNode getOrAddATranslationTag( QDomNode& messageTag );
            QString getSourceText( const QDomNode &messageTag ) const;
            QString getTagTextData( const QDomNode& tag ) const;
            QDomNodeList getOrAddNumerusTags( QDomNode& translationTag );
            QDomText getOrAddATextNode( QDomNode& tag );
            void removeTypeAttribute( QDomNode& translationTag );
            void updateTagData( QDomNode& translationTag, const QString& newText );
            void updateTagData( QDomNode& translationTag, const QString& newSinglarFormText, const QString& newPluralFormText );
            void insertText( QDomNode& tag, const QString& newText );
        };
    }
}

#endif // TRANSLATIONGENERATOR_HPP
