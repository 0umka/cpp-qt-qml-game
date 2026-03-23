import QtQuick
import QtQuick.Window
import QtQuick.Controls

ApplicationWindow {
    visible: true
    width: 800
    height: 600

    property point currentMousePos: Qt.point(0, 0)

    Rectangle {
        anchors.fill: parent
        color: "grey"

        Player {
            playerData: player
        }

        Enemy {
            enemyData: enemy
        }

        MouseArea {
            anchors.fill: parent
            hoverEnabled: true

            onPressed: (mouse) => {
                currentMousePos = Qt.point(mouse.x, mouse.y)
                player.startFollowingMouse()
                player.setTarget(mouse.x, mouse.y)
            }

            onPositionChanged: (mouse) => {
                if (pressed) {
                    currentMousePos = Qt.point(mouse.x, mouse.y)
                    player.setTarget(mouse.x, mouse.y)

                }
            }

            onReleased: {
                player.stopFollowingMouse()
            }
        }

        //кнопки
        Column {
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 20
            spacing: 10

            Button { text: "Damage"; onClicked: player.takeDamage(10) }
            Button { text: "Heal"; onClicked: player.heal(10) }
        }

        //информация
        Text {
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            anchors.margins: 20
            text: "Health: %1/%2".arg(player.health).arg(player.maxHealth)
            color: "white"
            font.pixelSize: 18
        }
    }
}
