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

#include <QFile>
#include <QFileInfo>
#include "LongEnglishGenerationCommand.hpp"
#include "LongEnglishGenerator.hpp"

using namespace ImaginativeThinking::Translation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
LongEnglishGenerationCommand::LongEnglishGenerationCommand(QObject *parent) :
    BaseGenerationCommand(parent)
{
    m_generator = new LongEnglishGenerator(this);

    Q_ASSERT( m_generator != nullptr );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
LongEnglishGenerationCommand::LongEnglishGenerationCommand(TranslationGenerator* generator, QObject* parent) :
    BaseGenerationCommand( parent ),
    m_generator( generator )
{
    Q_ASSERT( m_generator != nullptr );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool LongEnglishGenerationCommand::generate()
{
    bool ret( false );

    if ( areSourceAndDestinationFilesValid() )
    {
        if ( isOkToOverwriteDestinationFile() )
        {
            QFileInfo sourceFile( m_sourceFile );
            QFileInfo destinationFile( m_destinationFile );
            QFile source( sourceFile.absoluteFilePath() );
            QFile destination( destinationFile.absoluteFilePath() );

            ret = m_generator->generate( &source, &destination );
        }
    }

    emit generationCompleted( ret );
    return ret;
}

