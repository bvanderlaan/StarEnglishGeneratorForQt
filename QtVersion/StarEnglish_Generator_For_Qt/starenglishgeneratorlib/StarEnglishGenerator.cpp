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
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QIODevice>
#include <QDebug>

using namespace ImaginativeThinking::Translation;

StarEnglishGenerator::StarEnglishGenerator(QObject *parent) :
    QObject(parent)
{

}
bool StarEnglishGenerator::generate( QIODevice* source, QIODevice* destination )
{
    //TODO: Refactor this mess
    bool ret( false );

    bool filesReady = source->open( QIODevice::ReadOnly );
    filesReady &= destination->open( QIODevice::WriteOnly );

    if ( filesReady )
    {
        if ( source->size() > 0 )
        {
            QXmlStreamReader reader( source );
            QXmlStreamWriter writer( destination );

            if ( !reader.hasError() && !writer.hasError() )
            {
                QString sourceText;
                while( !reader.atEnd() )
                {
                    reader.readNext();
                    if ( reader.tokenType() != QXmlStreamReader::Invalid )
                    {
                        if ( ( reader.name().compare("source", Qt::CaseInsensitive ) == 0 ) && reader.isStartElement() )
                        {
                            writer.writeCurrentToken( reader );
                            sourceText = reader.readElementText();
                            writer.writeCharacters( sourceText );
                            writer.writeCurrentToken( reader );
                        }
                        else if ( ( reader.name().compare( "translation", Qt::CaseInsensitive) == 0 ) && reader.isStartElement() )
                        {
                            QString attribute;
                            auto attributes = reader.attributes();
                            if ( attributes.hasAttribute( "type" ) )
                            {
                                attribute = attributes.value( "type" ).toString();
                            }

                            if ( attribute.toLower() == "unfinished" )
                            {
                                writer.writeStartElement("translation");
                                reader.readElementText();
                                writer.writeCharacters( "*" + sourceText + "*" );
                                writer.writeEndElement();
                            }
                            else
                            {
                                writer.writeCurrentToken( reader );
                            }
                        }
                        else
                        {
                            writer.writeCurrentToken( reader );
                        }
                    }
                }

                ret = ( destination->size() > 0 );
            }
        }
    }
    return ret;
}
