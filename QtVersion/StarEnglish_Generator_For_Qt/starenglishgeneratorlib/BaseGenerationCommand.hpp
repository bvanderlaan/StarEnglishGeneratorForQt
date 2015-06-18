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

#ifndef BASEGENERATIONCOMMAND
#define BASEGENERATIONCOMMAND

#include <QObject>

class QFileInfo;
namespace ImaginativeThinking
{
    namespace Translation
    {
        class BaseGenerationCommand : public QObject
        {
            Q_OBJECT
            Q_PROPERTY( QString sourceFile READ getSourceFile WRITE setSourceFile NOTIFY sourceFileChanged )
            Q_PROPERTY( QString destinationFile READ getDestinationFile WRITE setDestinationFile NOTIFY destinationFileChanged )
        public:
            explicit BaseGenerationCommand( QObject* parent = nullptr );
            virtual ~BaseGenerationCommand(){}
            virtual bool generate() = 0;

            QString getSourceFile() const;
            void setSourceFile( const QString& file );
            QString getDestinationFile() const;
            void setDestinationFile( const QString& file );

        signals:
            void generationCompleted( bool isSuccess );
            void sourceFileChanged( QString sourceFile );
            void destinationFileChanged( QString destinationFile );

        protected:
            bool areSourceAndDestinationFilesValid() const;
            bool isOkToOverwriteDestinationFile() const;
            bool doesDestinationFileExist() const;
            bool doesSourceFileExist() const;
            virtual bool doesFileExist( QFileInfo file ) const;
            QString m_sourceFile;
            QString m_destinationFile;

        };
    }
}

#endif // BASEGENERATIONCOMMAND

