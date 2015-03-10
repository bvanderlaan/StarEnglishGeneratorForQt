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

#include "StarEnglishGeneratorModel.h"
#include "StarEnglishGenerator.h"
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <QDebug>

using namespace ImaginativeThinking::Translation;

StarEnglishGeneratorModel::StarEnglishGeneratorModel(QObject *parent) :
    QObject(parent)
{
    m_generator = new StarEnglishGenerator( this );
}

StarEnglishGeneratorModel::StarEnglishGeneratorModel(StarEnglishGenerator *generator, QObject *parent) :
    QObject( parent ),
    m_generator( generator )
{
    Q_ASSERT( m_generator != nullptr );
}

QString StarEnglishGeneratorModel::getSourceFile() const
{
    return m_sourceFile.fileName();
}
void StarEnglishGeneratorModel::setSourceFile(const QString &sourceFile)
{
    if ( m_sourceFile.fileName() != sourceFile )
    {
       m_sourceFile.setFile( sourceFile );
       emit sourceFileChanged( sourceFile );
    }
}
QString StarEnglishGeneratorModel::getDestinationFile() const
{
    return m_destinationFile.fileName();
}
void StarEnglishGeneratorModel::setDestinationFile( QString destinationFile)
{
    destinationFile = addFileExtensionIfNeeded( destinationFile );
    if ( m_destinationFile.fileName() != destinationFile )
    {
        m_destinationFile.setFile( destinationFile );
        emit destinationFileChanged( destinationFile );
    }
}
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
bool StarEnglishGeneratorModel::generate()
{
    bool ret( false );

    if ( areSourceAndDestinationFilesValid() )
    {
        if ( isOkToOverwriteDestinationFile() )
        {
            QFile source( m_sourceFile.absoluteFilePath() );
            QFile destination( m_destinationFile.absoluteFilePath() );

            ret = m_generator->generate( &source, &destination );
        }
    }

    emit starEnglishFileGenerationCompleted( ret );
    return ret;
}
bool StarEnglishGeneratorModel::areSourceAndDestinationFilesValid() const
{
    return doesSourceFileExist() && !m_destinationFile.fileName().isEmpty();
}
bool StarEnglishGeneratorModel::isOkToOverwriteDestinationFile() const
{
    bool ret( true );
    if ( doesDestinationFileExist() )
    {
        //TODO
        qDebug() << "file already exists, ask for permission to overwrite.";
    }
    return ret;
}
bool StarEnglishGeneratorModel::doesDestinationFileExist() const
{
    return doesFileExist( m_destinationFile );
}
bool StarEnglishGeneratorModel::doesFileExist(QFileInfo file) const
{
    return file.exists();
}
bool StarEnglishGeneratorModel::doesSourceFileExist() const
{
    return doesFileExist( m_sourceFile );
}
