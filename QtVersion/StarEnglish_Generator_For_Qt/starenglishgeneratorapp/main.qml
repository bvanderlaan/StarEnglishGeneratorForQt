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
    id: root
    title: qsTr("Star English Generator For Qt") + appLanguage.emptyString
    width: 640
    height: 200
    maximumHeight: 240
    maximumWidth: width
    minimumHeight: 200
    minimumWidth: width
    visible: true
    menuBar: mainMenu

    MenuBar {
        id: mainMenu

        Menu {
            title: qsTr("&File", "This is just showing how a context comment looks in the TS file.") + appLanguage.emptyString

            MenuItem {
                action: openTSFileAction
            }
            MenuItem {
                action: selectOutputPathAction
                visible: mainForm.isAdvancedMode
            }
            MenuItem {
                action: starEnglishModeAction.checked ? generateStarEnglishAction : generateLongEnglishAction
            }
            MenuSeparator {}
            MenuItem {
                action: showAdvancedOptionsAction
            }
            MenuSeparator {}
            MenuItem {
                action: quitApplicationAction
            }
        }
        Menu {
            title: qsTr("La&nguage") + appLanguage.emptyString

            MenuItem {
                action: selectEnglishAction
            }
            MenuItem {
                action: selectStarEnglishAction
            }
        }
        Menu {
            title: qsTr("&Mode") + appLanguage.emptyString

            MenuItem {
                action: starEnglishModeAction
            }
            MenuItem {
                action: longEnglishModeAction
            }
        }
        Menu {
            title: qsTr("H&elp") + appLanguage.emptyString

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
        text: qsTr("&Choose a Source Translation File") + appLanguage.emptyString
        onTriggered: {
            openFileDialog.open()
        }
    }
    Action {
        id: generateStarEnglishAction
        text: qsTr("&Generate Star English Trasnlation File") + appLanguage.emptyString
        onTriggered: {
            starEnglishModel.destinationFile = mainForm.outputTrasnlationFile
            starEnglishGenerator.generate()
        }
    }
    Action {
        id: generateLongEnglishAction
        text: qsTr("&Generate Long English Trasnlation File") + appLanguage.emptyString
        onTriggered: {
            starEnglishModel.destinationFile = mainForm.outputTrasnlationFile
            longEnglishGenerator.generate()
        }
    }
    Action {
        id: helpAction
        text: qsTr("&Help") + appLanguage.emptyString
        onTriggered: {
            helpDialog.open()
        }
    }
    Action {
        id: aboutAction
        text: qsTr("&About Star English Generator...") + appLanguage.emptyString
        onTriggered: {
            aboutDialog.open()
        }
    }
    Action {
        id: quitApplicationAction
        text: qsTr("E&xit") + appLanguage.emptyString
        onTriggered: {
            Qt.quit()
        }
    }
    Action {
        id: showAdvancedOptionsAction
        text: ( checked ? qsTr("Hide Advanced &Options") : qsTr("Show Advanced &Options") )  + appLanguage.emptyString
        checkable: true
    }
    Action {
        id: selectOutputPathAction
        text: qsTr("Select Output &path") + appLanguage.emptyString
        onTriggered: {
            openDirectoryDialog.open()
        }
    }
    ExclusiveGroup {
        id: languageExclusiveGroup
    }
    Action {
        id: selectEnglishAction
        text: "&1. English"
        checkable: true
        checked: true
        exclusiveGroup: languageExclusiveGroup
        onTriggered: {
            appLanguage.loadLanguage("en")
        }
    }
    Action {
        id: selectStarEnglishAction
        text: "&2. Star-English"
        checkable: true
        exclusiveGroup: languageExclusiveGroup
        onTriggered: {
            appLanguage.loadLanguage("fo")
        }
    }
    ExclusiveGroup {
        id: modeExclusiveGroup
    }
    Action {
        id: starEnglishModeAction
        text: "&Star-English"
        checkable: true
        checked: true
        exclusiveGroup: modeExclusiveGroup
    }
    Action {
        id: longEnglishModeAction
        text: "&Long-English"
        checkable: true
        exclusiveGroup: modeExclusiveGroup
    }
    MainForm {
        id: mainForm
        anchors.fill: parent
        headingText: qsTr("This application is used to generate <b>%1</b> translation files.").arg(modeExclusiveGroup.current.text.replace("&","")) + appLanguage.emptyString
        isAdvancedMode: showAdvancedOptionsAction.checked
        generateStarEnglishAction: starEnglishModeAction.checked ? generateStarEnglishAction : generateLongEnglishAction
        openSourceTrasnlationFileAction: openTSFileAction
        sourceTrasnlationFile: starEnglishModel.sourceFile
        outputPath: starEnglishModel.destinationPath
        selectOutputPathAction: selectOutputPathAction
        sourceTranslationFileMouseArea.onClicked: {
            openTSFileAction.trigger()
        }
        outputPathClickableArea.onClicked: {
            selectOutputPathAction.trigger()
        }
        states: [
            State {
                name: "AdvancedMode"
                when: mainForm.isAdvancedMode

                PropertyChanges {
                    target: mainForm.outputPathLable
                    opacity: 1.0
                }
                PropertyChanges {
                    target: mainForm.outputPathInput
                    opacity: 1.0
                }
                PropertyChanges {
                    target: mainForm.gridLayout
                    rows: 3
                }
                PropertyChanges {
                    target: root
                    height: 240
                }
                StateChangeScript {
                    script: root.update()
                }
            }
        ]
        transitions: Transition {
            NumberAnimation {
                properties: "opacity,height"; easing.type: Easing.InOutQuad
                duration: 250
            }
        }
    }
    FileDialog {
        id: openFileDialog
        title: qsTr("Choose a Translation File") + appLanguage.emptyString
        nameFilters: [ qsTr("Trasnlation Files (*.ts)"), qsTr("All files (*)")] + appLanguage.emptyString
        onAccepted: {
            starEnglishModel.sourceFile = openFileDialog.fileUrl.toString().substring(8) // this removes the "file:///"
        }
    }
    FileDialog {
        id: openDirectoryDialog
        title: qsTr("Choose an Output Directory") + appLanguage.emptyString
        selectFolder: true
        onAccepted: {
            starEnglishModel.destinationPath = openDirectoryDialog.fileUrl.toString().substring(8) // this removes the "file:///"
        }
    }
    MessageDialog {
        id: messageDialog
        title: qsTr("Star English Generator") + appLanguage.emptyString

        function show(caption) {
            messageDialog.text = caption;
            messageDialog.open();
        }
    }
    AboutDialog {
        id: aboutDialog
        onHelp: {
            helpDialog.open()
        }
    }
    Dialog {
        id: helpDialog
        title: qsTr("Help!") + appLanguage.emptyString
        standardButtons: StandardButton.Close
        width: 500

        Item {
            implicitWidth: 500
            implicitHeight: 150

            Text {
                font.pointSize: 12
                anchors.left: parent.left
                anchors.right: parent.right
                anchors.margins: 10
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                text: qsTr("Sorry I don't have any help documentation yet.<br><br>
                            Just know that the source file will remain unchanged and that the output name can not be
                            the same as the source file as you can't read and write to the same file.") + appLanguage.emptyString
            }
        }
    }
    StarEnglishModel {
        id: starEnglishModel
    }
    StarEnglishGenerator {
        id: starEnglishGenerator
        sourceFile: starEnglishModel.sourceFileWithAbsolutePath
        destinationFile: starEnglishModel.destinationFileWithAbsolutePath
        onGenerationCompleted: {
            if ( isSuccess ) {
                messageDialog.show( qsTr( "The Star English Translation Source (TS) file has been generated." ) )
            } else {
                messageDialog.show( qsTr( "The Star English Generation failed." ) )
            }
        }
    }
    LongEnglishGenerator {
        id: longEnglishGenerator
        sourceFile: starEnglishModel.sourceFileWithAbsolutePath
        destinationFile: starEnglishModel.destinationFileWithAbsolutePath
        onGenerationCompleted: {
            if ( isSuccess ) {
                messageDialog.show( qsTr( "The Long English Translation Source (TS) file has been generated." ) )
            } else {
                messageDialog.show( qsTr( "The Long English Generation failed." ) )
            }
        }
    }
}
