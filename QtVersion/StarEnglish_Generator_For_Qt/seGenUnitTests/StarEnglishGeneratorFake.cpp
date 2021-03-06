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

#include "StarEnglishGeneratorFake.h"

using namespace ImaginativeThinking::Translation;

/////////////////////////////////////////////////////////////////////////////////////////////////////////
StarEnglishGeneratorFake::StarEnglishGeneratorFake(QObject* parent) :
    StarEnglishGenerator(parent),
    m_generateReturnValue( false )
{

}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
bool StarEnglishGeneratorFake::generate( QIODevice *source, QIODevice* destination)
{
    Q_UNUSED( source );
    Q_UNUSED( destination );
    return m_generateReturnValue;
}
