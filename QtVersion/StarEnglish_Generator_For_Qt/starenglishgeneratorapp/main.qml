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

import QtQuick 2.4
import QtQuick.Controls 1.3
import QtQuick.Window 2.2
import QtQuick.Dialogs 1.2
import ca.imaginativethinking.translation 1.0

ApplicationWindow {
    title: qsTr("Star English Generator For Qt")
    width: 640
    height: 480
    visible: true
    menuBar: mainMenu

    MenuBar {
        id: mainMenu

        Menu {
            title: qsTr("&File")

            MenuItem {
                action: openTSFileAction
            }
            MenuItem {
                action: generateStarEnglishAction
            }
            MenuSeparator {}
            MenuItem {
                action: quitApplicationAction
            }
        }
        Menu {
            title: qsTr("&Help")

            MenuItem {
                action: helpAction
            }
            MenuSeparator {}
            MenuItem {
                action: aboutAction
            }
        }
    }
    Action {
        id: openTSFileAction
        text: qsTr("&Choose a Source Translation File")
        onTriggered: {
            openFileDialog.open()
        }
    }
    Action {
        id: generateStarEnglishAction
        text: qsTr("&Generate Star English Trasnlation File")
        onTriggered: {

        }
    }
    Action {
        id: helpAction
        text: qsTr("&Help")
        onTriggered: {

        }
    }
    Action {
        id: aboutAction
        text: qsTr("&About Star English Generator...")
        onTriggered: {

        }
    }
    Action {
        id: quitApplicationAction
        text: qsTr("E&xit")
        onTriggered: {
            Qt.quit()
        }
    }
    MainForm {
        id: mainForm
        anchors.fill: parent
        generateStarEnglishAction: generateStarEnglishAction
        openSourceTrasnlationFileAction: openTSFileAction
        sourceTrasnlationFile: generator.sourceFile
        outputTrasnlationFile: generator.destinationFile
    }
    FileDialog {
        id: openFileDialog
        title: qsTr("Choose a Translation File")
        nameFilters: ["Trasnlation Files (*.ts)", "All files (*)"]
        onAccepted: {
            generator.sourceFile = openFileDialog.fileUrl
            console.log("DEBUG:" + generator.sourceFile )
        }
    }
    StarEnglishGenerator {
        id: generator
    }


    MessageDialog {
        id: messageDialog
        title: qsTr("May I have your attention, please?")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
