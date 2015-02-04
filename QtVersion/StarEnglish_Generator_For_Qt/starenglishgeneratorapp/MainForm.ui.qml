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
import QtQuick.Layouts 1.1

Item {
    id: root
    width: 640
    height: 480

    property alias generateStarEnglishAction: generateStarEnglish.action
    property alias openSourceTrasnlationFileAction: openSourceTranslationFile.action
    property alias sourceTrasnlationFile: sourceTrasnlationFile.text
    property alias outputTrasnlationFile: starEnglishTrasnlationFile.text
    property string font: "Tahoma"
    property int pointSize: 12

    ColumnLayout {
        anchors.fill: parent
        anchors.margins: 10
        spacing: 5

        Text {
            anchors.horizontalCenter: parent.horizontalCenter
            text: qsTr("This application is used to generate <b>Star English</b> translation files.")
            font.pointSize: root.pointSize
        }
        Item { width: 1; height: 10; }
        RowLayout {
           anchors.left: parent.left
           anchors.right: parent.right
           spacing: 5

           Text {
               text: qsTr("Source Translation File: ")
               font.family: root.font
               font.pointSize: root.pointSize
           }
           Rectangle {
               Layout.fillWidth: true
               height: childrenRect.height + 10
               color: "white"
               border.color: "black"
               border.width: 2

               Text {
                   id: sourceTrasnlationFile
                   verticalAlignment: Text.AlignVCenter
                   font.pointSize: root.pointSize
                   font.family: root.font
                   anchors.top: parent.top
                   anchors.left: parent.left
                   anchors.right: parent.right
                   anchors.margins: 5
                   elide: Text.ElideLeft
               }
           }
           Button {
               id: openSourceTranslationFile
               text: "..."
           }
        }
        RowLayout {
            anchors.left: parent.left
            anchors.right: parent.right
            height: childrenRect.height
            spacing: 5

            Text {
                text: qsTr("Output filename:")
                font.pointSize: root.pointSize
                font.family: root.font
            }
            Rectangle {
                Layout.fillWidth: true
                height: childrenRect.height + 10
                color: "white"
                border.color: "black"
                border.width: 2

                TextInput {
                    id: starEnglishTrasnlationFile
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.margins: 5
                    font.pointSize: root.pointSize
                    font.family: root.font
                }
            }
        }
        Button {
            id: generateStarEnglish
            anchors.right: parent.right
        }

    }
}
