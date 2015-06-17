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

#include <QObject>

class QIODevice;
class QXmlStreamWriter;
class QDomDocument;
class QDomNode;
class QDomNodeList;
class QDomText;
namespace ImaginativeThinking
{
    namespace Translation
    {
        class StarEnglishGenerator : public QObject
        {
            Q_OBJECT
            Q_PROPERTY(QString character READ getStarEnglishCharacter WRITE setStarEnglishCharacter NOTIFY starEnglishCharacterChanged)
            Q_PROPERTY(QString languageCode READ getStarEnglishLanguageCode WRITE setStarEnglishLanguageCode NOTIFY starEnglishLanguageCodeChanged)

        public:
            explicit StarEnglishGenerator( QObject *parent = 0);
            virtual ~StarEnglishGenerator(){}

            virtual bool generate( QIODevice* source, QIODevice* destination );

            QString getStarEnglishCharacter() const;
            void setStarEnglishCharacter( const QString& character );

            QString getStarEnglishLanguageCode() const;
            void setStarEnglishLanguageCode( const QString& code );

        signals:
            void starEnglishCharacterChanged( const QString& character );
            void starEnglishLanguageCodeChanged( const QString& languageCode );

        protected:
            QDomDocument* m_sourceDocument;
            const QString m_rootTagName;
            const QString m_messageRootTagName;
            const QString m_sourceTagName;
            const QString m_translationTagName;
            const QString m_typeAttributeName;
            const QString m_languageAttributeName;
            const QString m_pluralOrSignalarFormAttributeName;
            const QString m_pluralOrSignalarFormTagName;
            QString m_starEnglishCharacter;
            QString m_starEnglishLanguageCode;

        private:
            bool isSourceFileValid( QIODevice* source ) const;
            bool isValidTranslationXML( QIODevice* source ) const;
            bool openSourceAndDestinationFiles(QIODevice* source, QIODevice* destination);
            bool openSourceDom( QIODevice* source );
            bool processSourceFile();
            bool processRootNode();
            bool processRootNode( QDomNode& rootNode );
            bool processMessageNodes();
            bool processMessageNode( QDomNode& messageXML );
            bool supportsPluralForm( QDomNode& messageNode ) const;
            QString getSourceText( const QDomNode &messageTag ) const;
            QString getTagTextData( const QDomNode& tag ) const;
            QString convertTextToStarEnglish( const QString& sourceText ) const;
            QDomNode getOrAddATranslationTag( QDomNode& messageTag );
            void updateTagDataToStarEnglish( QDomNode& translationTag, const QString& starEnglishText );
            void updateTagDataToStarEnglish( QDomNode& translationTag, const QString& singlarFormStarEnglishText, const QString& pluralFormStarEnglishText );
            QDomNodeList getOrAddNumerusTags( QDomNode& translationTag );
            void insertStarEnglishText( QDomNode& tag, const QString& starEnglishText );
            QDomText getOrAddATextNode( QDomNode& tag );
            void removeTypeAttribute( QDomNode& translationTag );
        };
    }
}

#endif // STARENGLISHGENERATOR_H
