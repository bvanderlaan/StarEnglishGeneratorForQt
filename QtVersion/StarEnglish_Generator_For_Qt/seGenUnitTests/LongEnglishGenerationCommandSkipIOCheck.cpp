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

#include <QFileInfo>
#include "LongEnglishGenerationCommandSkipIOCheck.hpp"

using namespace ImaginativeThinking::Translation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
LongEnglishGenerationCommandSkipIOCheck::LongEnglishGenerationCommandSkipIOCheck( QObject* parent ) :
    LongEnglishGenerationCommand( parent ),
    m_doesfileExist( true )
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
LongEnglishGenerationCommandSkipIOCheck::LongEnglishGenerationCommandSkipIOCheck(TranslationGenerator* generator, QObject* parent) :
    LongEnglishGenerationCommand( generator, parent ),
    m_doesfileExist( true )
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LongEnglishGenerationCommandSkipIOCheck::doesFileExist(QFileInfo file) const
{
    Q_UNUSED( file );
    return m_doesfileExist;
}

