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
    height: 200
    visible: true
    menuBar: mainMenu

    MenuBar {
        id: mainMenu

        Menu {
            title: qsTr("&File", "This is just showing how a context comment looks in the TS file.")

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
            generator.destinationFile = mainForm.outputTrasnlationFile
            generator.generate()
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
    }
    FileDialog {
        id: openFileDialog
        title: qsTr("Choose a Translation File")
        nameFilters: ["Trasnlation Files (*.ts)", "All files (*)"]
        onAccepted: {
            generator.sourceFile = openFileDialog.fileUrl.toString().substring(8) // this removes the "file:///"
        }
    }
    StarEnglishGenerator {
        id: generator
        onStarEnglishFileGenerationCompleted: {
            if ( isSuccess ) {
                messageDialog.show( "The Star English Translation Source (TS) file has been generated." )
            } else {
                messageDialog.show( "The Star English Generation failed." )
            }
        }
    }
    MessageDialog {
        id: messageDialog
        title: qsTr("Star English Generator")

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
}
