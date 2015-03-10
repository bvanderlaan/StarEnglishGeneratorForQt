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
class QDomText;
namespace ImaginativeThinking
{
    namespace Translation
    {
        class StarEnglishGenerator : public QObject
        {
            Q_OBJECT

        public:
            explicit StarEnglishGenerator( QObject *parent = 0);
            virtual ~StarEnglishGenerator(){}

            virtual bool generate( QIODevice* source, QIODevice* destination );
        private:
            bool isSourceFileValid( QIODevice* source ) const;
            bool isValidTranslationXML( QIODevice* source ) const;
            bool openSourceAndDestinationFiles(QIODevice* source, QIODevice* destination);
            bool openSourceDom( QIODevice* source );
            void processSourceFile();
            void processMessageNode( QDomNode& messageXML );
            QString getSourceText( const QDomNode &messageTag ) const;
            QString getTagTextData( const QDomNode& tag ) const;
            QString convertTextToStarEnglish( const QString& sourceText ) const;
            QDomNode getOrAddATranslationTag( QDomNode& messageTag );
            void updateTagDataToStarEnglish( QDomNode& translationTag, const QString& starEnglishText );
            void insertStarEnglishText( QDomNode& tag, const QString& starEnglishText );
            QDomText getOrAddATextNode( QDomNode& tag );
            void removeTypeAttribute( QDomNode& translationTag );
            QDomDocument* m_sourceDocument;
            const QString m_messageRootTagName;
            const QString m_sourceTagName;
            const QString m_translationTagName;
            const QString m_typeAttributeName;
            QString m_starEnglishCharacter;
        };
    }
}

#endif // STARENGLISHGENERATOR_H
