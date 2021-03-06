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

#include <QRegularExpression>
#include "LongEnglishGenerator.hpp"

using namespace ImaginativeThinking::Translation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
LongEnglishGenerator::LongEnglishGenerator(QObject *parent) :
    TranslationGenerator(parent),
    m_longEnglishCharacter( 'W' )
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QChar LongEnglishGenerator::getLongEnglishCharacter() const
{
    return m_longEnglishCharacter;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void LongEnglishGenerator::setLongEnglishCharacter(const QChar& character)
{
    if ( m_longEnglishCharacter != character )
    {
        m_longEnglishCharacter = character;
        emit longEnglishCharacterChanged( m_longEnglishCharacter );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString LongEnglishGenerator::translateText(const QString& sourceText) const
{
    QString longEnglishMarker = getLongEnglishMarker( sourceText );

    QString copy( sourceText );
    copy.prepend(longEnglishMarker);
    copy.append(longEnglishMarker);
    return copy;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString LongEnglishGenerator::getLongEnglishMarker(const QString& sourceText) const
{
    QString plainTextSourceText = removeHTMLTags( sourceText );

    int markerLength = plainTextSourceText.length() / 2;
    return QString( markerLength, m_longEnglishCharacter );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString LongEnglishGenerator::removeHTMLTags( const QString& sourceText ) const
{
    QString copy( sourceText );
    QRegularExpression re( "<[^>]*>" );
    return copy.remove( re );
}

