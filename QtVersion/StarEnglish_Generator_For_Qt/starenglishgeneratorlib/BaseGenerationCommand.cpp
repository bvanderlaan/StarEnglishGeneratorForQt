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

#include <QDebug>
#include <QFileInfo>
#include "BaseGenerationCommand.hpp"

using namespace ImaginativeThinking::Translation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
BaseGenerationCommand::BaseGenerationCommand(QObject* parent) :
    QObject( parent )
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString BaseGenerationCommand::getSourceFile() const
{
    return m_sourceFile;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseGenerationCommand::setSourceFile(const QString& file)
{
    if ( m_sourceFile != file )
    {
        m_sourceFile = file;
        emit sourceFileChanged( m_sourceFile );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString BaseGenerationCommand::getDestinationFile() const
{
    return m_destinationFile;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void BaseGenerationCommand::setDestinationFile(const QString& file)
{
    if ( m_destinationFile != file )
    {
        m_destinationFile = file;
        emit destinationFileChanged( m_destinationFile );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseGenerationCommand::areSourceAndDestinationFilesValid() const
{
    return doesSourceFileExist() && !m_destinationFile.isEmpty();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseGenerationCommand::doesSourceFileExist() const
{
    QFileInfo info( m_sourceFile );
    return doesFileExist( info );
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseGenerationCommand::doesFileExist(QFileInfo file) const
{
    return file.exists();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseGenerationCommand::isOkToOverwriteDestinationFile() const
{
    bool ret( true );
    if ( doesDestinationFileExist() )
    {
        //TODO
        qDebug() << "file already exists, ask for permission to overwrite.";
    }
    return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool BaseGenerationCommand::doesDestinationFileExist() const
{
    QFileInfo destinationFile( m_destinationFile );
    return doesFileExist( destinationFile );
}


