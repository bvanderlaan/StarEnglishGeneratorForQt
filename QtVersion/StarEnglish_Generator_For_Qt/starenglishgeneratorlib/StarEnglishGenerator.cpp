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

using namespace ImaginativeThinking::Translation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
StarEnglishGenerator::StarEnglishGenerator(QObject *parent) :
    TranslationGenerator(parent),
    m_starEnglishCharacter( "*" )
{
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
QString StarEnglishGenerator::translateText( const QString& sourceText ) const
{
    QString copy( sourceText );
    copy.prepend(m_starEnglishCharacter);
    copy.append(m_starEnglishCharacter);
    return copy;
}

