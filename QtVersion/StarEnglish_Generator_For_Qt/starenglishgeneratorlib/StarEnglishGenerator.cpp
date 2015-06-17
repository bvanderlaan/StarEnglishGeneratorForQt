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

#include "StarEnglishGenerator.h"
#include <QFile>
#include <QXmlStreamWriter>
#include <QDomDocument>
#include <QIODevice>
#include <QDebug>
#include <QRegularExpression>

using namespace ImaginativeThinking::Translation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
StarEnglishGenerator::StarEnglishGenerator(QObject *parent) :
    QObject(parent),
    m_sourceDocument( nullptr ),
    m_rootTagName( "TS" ),
    m_messageRootTagName( "message" ),
    m_sourceTagName( "source" ),
    m_translationTagName( "translation" ),
    m_typeAttributeName( "type" ),
    m_languageAttributeName( "language" ),
    m_pluralOrSignalarFormAttributeName( "numerus" ),
    m_pluralOrSignalarFormTagName( "numerusform" ),
    m_starEnglishCharacter( "*" ),
    m_starEnglishLanguageCode("fo_FO")
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::generate( QIODevice* source, QIODevice* destination )
{
    if ( isSourceFileValid( source ) )
    {
        if ( openSourceAndDestinationFiles( source, destination ) )
        {
            m_sourceDocument = new QDomDocument();
            if ( openSourceDom( source ) )
            {
                QTextStream writer( destination );
                if ( processSourceFile() )
                {
                    writer << m_sourceDocument->toString();
                }
            }

            delete m_sourceDocument;
            m_sourceDocument = nullptr;

            source->close();
            destination->close();
        }
    }
    return ( destination->size() > 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGenerator::getStarEnglishCharacter() const
{
    return m_starEnglishCharacter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerator::setStarEnglishCharacter(const QString& character)
{
    if ( m_starEnglishCharacter != character )
    {
        m_starEnglishCharacter = character;
        emit starEnglishCharacterChanged( m_starEnglishCharacter );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGenerator::getStarEnglishLanguageCode() const
{
    return m_starEnglishLanguageCode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerator::setStarEnglishLanguageCode(const QString& code)
{
    if ( m_starEnglishLanguageCode != code )
    {
        m_starEnglishLanguageCode = code;
        emit starEnglishLanguageCodeChanged( m_starEnglishLanguageCode );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::openSourceDom( QIODevice* source )
{
    int lineNumber(0);
    int column(0);
    QString errorMessage;

    bool openedSuccessfully = m_sourceDocument->setContent( source, &errorMessage, &lineNumber, &column );
    if ( !openedSuccessfully )
    {
        qDebug() << QString("ERROR: %1, at line %2, and column %3").arg(errorMessage).arg(lineNumber).arg(column);
    }

    return openedSuccessfully;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::isSourceFileValid( QIODevice* source ) const
{
    return ( source->size() > 0 );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::openSourceAndDestinationFiles(QIODevice* source, QIODevice* destination)
{
    bool filesOpen = source->open( QIODevice::ReadOnly | QIODevice::Text );
    filesOpen &= destination->open( QIODevice::WriteOnly | QIODevice::Text );
    return filesOpen;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::processSourceFile()
{
    bool ret( false );

    if ( processRootNode() )
    {
        ret = processMessageNodes();
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::processRootNode()
{
    bool ret( false );
    auto rootTags = m_sourceDocument->elementsByTagName( m_rootTagName );
    if ( rootTags.count() == 1 )
    {
        QDomNode rootTag = rootTags.at(0);
        ret = processRootNode( rootTag );
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::processRootNode(QDomNode& rootNode)
{
    bool ret( false );
    QDomNamedNodeMap attributes = rootNode.attributes();
    int attributeCount = attributes.count();
    for( int i=0; i < attributeCount; i++ )
    {
        QDomAttr attribute = attributes.item(i).toAttr();
        if ( attribute.name() == m_languageAttributeName )
        {
            attribute.setValue( m_starEnglishLanguageCode );
            ret = true;
            break;
        }
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::processMessageNodes()
{
    bool ret( false );
    auto messageTags = m_sourceDocument->elementsByTagName( m_messageRootTagName );
    for( int i = 0; i < messageTags.count(); i++ )
    {
        QDomNode messageTag = messageTags.at(i);
        ret = processMessageNode( messageTag );
    }

    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::processMessageNode( QDomNode& messageTag )
{
    bool ret( false );
    bool doesSupportPluralForm = supportsPluralForm( messageTag );
    QString sourceText = getSourceText( messageTag );
    QDomNode translationTag = getOrAddATranslationTag( messageTag );

    if ( !translationTag.isNull() )
    {
        if ( doesSupportPluralForm )
        {
            QRegularExpression regEx( "(\\(s\\))$");
            QString signlarFormSourceText = sourceText.replace(regEx, "");
            QString pluralFormSourceText = signlarFormSourceText + "s";

            QString starEnglishSinglarFormText = convertTextToStarEnglish( signlarFormSourceText );
            QString starEnglishPluralFormText = convertTextToStarEnglish( pluralFormSourceText );

            updateTagDataToStarEnglish( translationTag, starEnglishSinglarFormText, starEnglishPluralFormText );
        }
        else
        {
            QString starEnglishText = convertTextToStarEnglish( sourceText );
            updateTagDataToStarEnglish( translationTag, starEnglishText );
        }

        ret = true;
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGenerator::supportsPluralForm(QDomNode& messageNode) const
{
    bool supportsPluralForm( false );
    if ( messageNode.isElement() &&  messageNode.hasAttributes() )
    {
        auto attributes = messageNode.attributes();
        if ( attributes.contains( m_pluralOrSignalarFormAttributeName) )
        {
            QDomNode attribute = attributes.namedItem( m_pluralOrSignalarFormAttributeName );
            supportsPluralForm = ( attribute.nodeValue() == "yes" );
        }
    }
    return supportsPluralForm;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGenerator::getSourceText( const QDomNode &messageTag ) const
{
    QString sourceText;
    auto sourceTags = messageTag.toElement().elementsByTagName( m_sourceTagName );
    if ( sourceTags.count() > 0 )
    {
        QDomNode theSourceTag = sourceTags.at(0);
        sourceText = getTagTextData( theSourceTag );
    }
    return sourceText;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGenerator::getTagTextData( const QDomNode& tag ) const
{
    QString tagTextData;
    QDomNodeList tagChildElements = tag.childNodes();
    for( int i = 0; i < tagChildElements.count(); i++ )
    {
        QDomNode child = tagChildElements.at(i);
        if ( child.isText() )
        {
            tagTextData = child.toText().data();
            break;
        }
    }
    return tagTextData;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGenerator::convertTextToStarEnglish( const QString& sourceText ) const
{
    return QString( "%1%2%3" ).arg(m_starEnglishCharacter).arg(sourceText).arg(m_starEnglishCharacter);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QDomNode StarEnglishGenerator::getOrAddATranslationTag( QDomNode& messageTag)
{
    QDomNode translationTag;
    auto translationTags = messageTag.toElement().elementsByTagName( m_translationTagName );
    if ( translationTags.count() > 0 )
    {
        translationTag = translationTags.at(0);
    }
    else
    {
        translationTag = messageTag.appendChild( m_sourceDocument->createElement( m_translationTagName ) );
        Q_ASSERT( translationTag.isNull() != true );
    }
    return translationTag;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerator::updateTagDataToStarEnglish(QDomNode &translationTag, const QString& starEnglishText)
{
    insertStarEnglishText( translationTag, starEnglishText );
    removeTypeAttribute( translationTag );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerator::updateTagDataToStarEnglish(QDomNode& translationTag, const QString& singlarFormStarEnglishText, const QString& pluralFormStarEnglishText)
{
    auto numerusNodes = getOrAddNumerusTags( translationTag );
    QDomNode singularNode = numerusNodes.at(0);
    QDomNode pluralNode = numerusNodes.at(1);
    insertStarEnglishText( singularNode, singlarFormStarEnglishText );
    insertStarEnglishText( pluralNode, pluralFormStarEnglishText );

    removeTypeAttribute( translationTag );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QDomNodeList StarEnglishGenerator::getOrAddNumerusTags(QDomNode& translationTag)
{
    auto numerusTags = translationTag.toElement().elementsByTagName( m_pluralOrSignalarFormTagName );
    if ( numerusTags.count() == 0 )
    {
        translationTag = translationTag.appendChild( m_sourceDocument->createElement( m_pluralOrSignalarFormTagName ) );
        Q_ASSERT( translationTag.isNull() != true );

        translationTag = translationTag.appendChild( m_sourceDocument->createElement( m_pluralOrSignalarFormTagName ) );
        Q_ASSERT( translationTag.isNull() != true );
    }

    numerusTags = translationTag.toElement().elementsByTagName( m_pluralOrSignalarFormTagName );

    Q_ASSERT( numerusTags.count() == 2 );

    return numerusTags;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerator::insertStarEnglishText( QDomNode& tag, const QString& starEnglishText )
{
    QDomText textNode = getOrAddATextNode( tag );
    textNode.setNodeValue( starEnglishText );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QDomText StarEnglishGenerator::getOrAddATextNode(QDomNode &tag)
{
    QDomText textNode;
    for( int i = 0; i < tag.childNodes().count(); i++ )
    {
        QDomNode child = tag.childNodes().at(i);
        if ( child.isText() )
        {
            textNode = child.toText();
            break;
        }
    }

    if ( textNode.isNull() )
    {
        textNode = tag.appendChild( m_sourceDocument->createTextNode("") ).toText();
        Q_ASSERT( textNode.isNull() != true );
    }
    return textNode;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGenerator::removeTypeAttribute( QDomNode& translationTag )
{
    QDomNamedNodeMap attributes = translationTag.attributes();
    attributes.removeNamedItem( m_typeAttributeName );
}
