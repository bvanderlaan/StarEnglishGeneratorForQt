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
import QtQuick.Dialogs 1.2

Dialog {
    id: root
    title: qsTr("About Star English Generator") + appLanguage.emptyString
    standardButtons: StandardButton.Close
    width: 660 // Documentaiton says not to do this but if I don't the dialog is way to thin.

    Item {
        implicitWidth: 640
        implicitHeight: 550

        Column {
            anchors.fill: parent
            anchors.margins: 5
            spacing: 10

            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 15
                font.bold: true
                text: qsTr("Star-English Generator for Qt") + appLanguage.emptyString
            }
            Rectangle {
                anchors.left: parent.left
                anchors.right: parent.right
                height: 2
                color: "#414B59"
            }
            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                font.pointSize: 12
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                textFormat: Text.StyledText
                linkColor: color
                onLinkActivated: Qt.openUrlExternally(link)
                text: qsTr("This tool takes a Qt translation file (*.ts) and generates a new one inserting either
                            asterisks or a number of W's around each string to enable you to test your code for translation support.<br><br>
                            It is for use with the <a href=\"http://imaginativethinking.ca/heck-star-english\">Star-English</a>
                            or <a href=\"http://imaginativethinking.ca/what-the-heck-is-long-english\">Long-English</a> technique.") + appLanguage.emptyString
            }
            Item { width: 1; height: 10 }
            Text {
                anchors.left: parent.left
                anchors.right: parent.right
                font.pointSize: 12
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                textFormat: Text.StyledText
                linkColor: color
                onLinkActivated: Qt.openUrlExternally(link)
                text: qsTr("This tool is Open Source Software released under the <a href=\"https://github.com/bvanderlaan/StarEnglishGeneratorForQt/blob/master/LICENSE.md\">Apache 2.0 license</a>.<br/><br/>
                            If you want to make changes please clone the <a href=\"https://github.com/bvanderlaan/StarEnglishGeneratorForQt\">git repository</a>.") + appLanguage.emptyString
            }
            Item { width: 1; height: 10 }
            Image {
                anchors.horizontalCenter: parent.horizontalCenter
                source: "qrc:///images/Brad.png"
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 12
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                textFormat: Text.StyledText
                linkColor: color
                onLinkActivated: Qt.openUrlExternally(link)
                text: qsTr("Created by: <a href=\"http://bradvanderlaan.ca\"><b>Brad van der Laan</b></a>") + appLanguage.emptyString
            }
            Text {
                anchors.horizontalCenter: parent.horizontalCenter
                font.pointSize: 12
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                textFormat: Text.StyledText
                linkColor: color
                onLinkActivated: Qt.openUrlExternally(link)
                text: qsTr("Copyright %1 ImaginativeThinking").arg(new Date().getFullYear()) + appLanguage.emptyString
            }
        }
    }
}
