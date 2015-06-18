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

#ifndef STARENGLISHGENERATORMODEL_H
#define STARENGLISHGENERATORMODEL_H

#include <QObject>
#include <QFileInfo>

namespace ImaginativeThinking
{
    namespace Translation
    {
        class StarEnglishGeneratorModel : public QObject
        {
            Q_OBJECT
            Q_PROPERTY( QString sourceFile READ getSourceFile WRITE setSourceFile NOTIFY sourceFileChanged )
            Q_PROPERTY( QString sourceFileWithAbsolutePath READ getSourceFileWithAbsolutePath NOTIFY sourceFileChanged )
            Q_PROPERTY( QString destinationFile READ getDestinationFile WRITE setDestinationFile NOTIFY destinationFileChanged )
            Q_PROPERTY( QString destinationPath READ getDestinationPath WRITE setDestinationPath NOTIFY destinationFilePathChanged )
            Q_PROPERTY( QString destinationFileWithAbsolutePath READ getDestinationFileWithAbsolutePath NOTIFY destinationAbsolutepathChanged )
        public:
            explicit StarEnglishGeneratorModel(QObject *parent = 0);
            virtual ~StarEnglishGeneratorModel(){}

            QString getSourceFileWithAbsolutePath() const;
            QString getSourceFile() const;
            void setSourceFile( const QString& sourceFile );
            QString getDestinationFileWithAbsolutePath() const;
            QString getDestinationFile() const;
            void setDestinationFile( QString destinationFile );
            QString getDestinationPath() const;
            void setDestinationPath( const QString& path );

        signals:
            void sourceFileChanged( QString sourceFile );
            void destinationFileChanged( QString destinationFile );
            void destinationFilePathChanged( QString path );
            void destinationAbsolutepathChanged( QString fileAndPath );

        private:
            QFileInfo m_sourceFile;
            QString m_destinationFilename;
            QString m_destinationFilePath;

            QString addFileExtensionIfNeeded( const QString& fileName ) const;
        };
    }
}

#endif // STARENGLISHGENERATORMODEL_H
