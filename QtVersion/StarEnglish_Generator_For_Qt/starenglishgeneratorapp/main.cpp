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
#include <QQmlApplicationEngine>
#include "StarEnglishGeneratorModel.h"
#include <QQuickItem>

void registerQMLTypes()
{
    qmlRegisterType<ImaginativeThinking::Translation::StarEnglishGeneratorModel>("ca.imaginativethinking.translation", 1, 0, "StarEnglishGenerator" );
}
int main(int argc, char *argv[])
{
    registerQMLTypes();
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
