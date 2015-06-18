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

#include <QDir>
#include "StarEnglishGeneratorModel.h"

using namespace ImaginativeThinking::Translation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
StarEnglishGeneratorModel::StarEnglishGeneratorModel(QObject *parent) :
    QObject(parent)
{
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGeneratorModel::getSourceFileWithAbsolutePath() const
{
    return m_sourceFile.absoluteFilePath();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGeneratorModel::getSourceFile() const
{
    return m_sourceFile.fileName();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGeneratorModel::setSourceFile(const QString &sourceFile)
{
    if ( m_sourceFile.fileName() != sourceFile )
    {
       m_sourceFile.setFile( sourceFile );
       emit sourceFileChanged( sourceFile );

       setDestinationPath( m_sourceFile.absolutePath() );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGeneratorModel::getDestinationFileWithAbsolutePath() const
{
    QFileInfo info( QDir(m_destinationFilePath), m_destinationFilename );
    return info.absoluteFilePath();
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGeneratorModel::getDestinationFile() const
{
    return m_destinationFilename;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGeneratorModel::setDestinationFile( QString destinationFile)
{
    if ( !destinationFile.isEmpty() )
    {
        destinationFile = addFileExtensionIfNeeded( destinationFile );
    }

    if ( m_destinationFilename != destinationFile )
    {
        m_destinationFilename = destinationFile;
        emit destinationFileChanged( destinationFile );
        emit destinationAbsolutepathChanged( this->getDestinationFileWithAbsolutePath() );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGeneratorModel::getDestinationPath() const
{
    return m_destinationFilePath;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
void StarEnglishGeneratorModel::setDestinationPath(const QString &path)
{
    if ( m_destinationFilePath != path )
    {
        m_destinationFilePath = path;
        emit destinationFilePathChanged( m_destinationFilePath );
        emit destinationAbsolutepathChanged( this->getDestinationFileWithAbsolutePath() );
    }
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
QString StarEnglishGeneratorModel::addFileExtensionIfNeeded( const QString& fileName ) const
{
    QString returnValue = fileName;
    QFileInfo fileInfo( fileName );
    if ( fileInfo.suffix().isEmpty() )
    {
        returnValue += ".ts";
    }
    return returnValue;
}
