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

#include <QApplication>
#include <QDebug>
#include "LanguageSelector.h"

using namespace ImaginativeThinking::Translation;

LanguageSelector::LanguageSelector(QObject *parent) :
    QObject(parent),
    m_baseTranslationFileName("StarEnglish_%1.qm")
{
    m_translationFilePath = QApplication::applicationDirPath();
    m_translationFilePath.append("/translations");
}

QString LanguageSelector::getEmptyString() const
{
    return QString();
}

QString LanguageSelector::getSelectedLanguageCode() const
{
    return m_selectedLanguage;
}

QString LanguageSelector::getTranslationFileBaseName() const
{
    return m_baseTranslationFileName;
}

void LanguageSelector::setTrasnlationFileBaseName(const QString &baseName)
{
    if ( m_baseTranslationFileName != baseName )
    {
        m_baseTranslationFileName = baseName;
        emit baseTranslationFileNameChanged( m_baseTranslationFileName );
    }
}

void LanguageSelector::loadLanguage(const QString &languageCode)
{
    if ( m_selectedLanguage != languageCode )
    {
        if ( switchTranslator( languageCode ) )
        {
           setSelectedLanguageCode( languageCode );
        }
    }
}

bool LanguageSelector::switchTranslator(const QString &lanugageCode)
{
    bool didTranslate(true);
    didTranslate &= switchTranslator( m_translator, QString(m_baseTranslationFileName).arg( lanugageCode ) );

    return didTranslate;
}

bool LanguageSelector::switchTranslator(QTranslator &translator, const QString &translationFile)
{
    bool didTranslate( false );
    qApp->removeTranslator( &translator );
qDebug() << m_translationFilePath << " \ " << translationFile;
    if ( translator.load( translationFile, m_translationFilePath  ) )
    {
        qDebug() << "HERE";
        didTranslate = qApp->installTranslator( &translator );
    }

    return didTranslate;
}

void LanguageSelector::setSelectedLanguageCode(const QString &languageCode)
{
    if ( m_selectedLanguage != languageCode )
    {
        m_selectedLanguage = languageCode;
        emit selectedLanguageChanged( m_selectedLanguage );
    }
}
