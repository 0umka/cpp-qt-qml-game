import QtQuick

Item {
    id: root
    property var playerData: null

    width:  playerData ? playerData.width  : 0
    height: playerData ? playerData.height : 0
    x: playerData ? playerData.position.x - width  / 2 : 0
    y: playerData ? playerData.position.y - height / 2 : 0

    // Свечение под игроком
    Rectangle {
        anchors.centerIn: parent
        width:  root.width  * 2.0
        height: root.height * 2.0
        radius: width / 2
        color: "#157c3aed"
        z: -1
    }

    Rectangle {
        anchors.centerIn: parent
        width:  root.width  * 1.4
        height: root.height * 1.4
        radius: width / 2
        color: "#257c3aed"
        z: -1
    }

    // Тело игрока
    Rectangle {
        anchors.centerIn: parent
        width:  root.width
        height: root.height
        radius: 6
        color: "#0d1a2e"
        border.color: "#4c1d95"
        border.width: 2

        // Блик сверху
        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height * 0.35
            radius: parent.radius
            color: "transparent"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#208080ff" }
                GradientStop { position: 1.0; color: "transparent" }
            }
        }

        // Иконка
        Text {
            anchors.centerIn: parent
            text: "⚔"
            font.pixelSize: root.width * 0.45
            color: "#a855f7"
        }
    }

    // Индикатор движения — пульсирующий ромб снизу
    Rectangle {
        anchors.top: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 3
        width: 5; height: 5
        rotation: 45
        color: "#7c3aed"
        opacity: playerData && playerData.followingMouse ? 1.0 : 0.0

        SequentialAnimation on opacity {
            running: playerData ? playerData.followingMouse : false
            loops: Animation.Infinite
            NumberAnimation { to: 0.2; duration: 400 }
            NumberAnimation { to: 1.0; duration: 400 }
        }
    }
}
