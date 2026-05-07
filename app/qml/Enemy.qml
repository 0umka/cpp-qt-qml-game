import QtQuick

Item {
    id: root
    property var enemyData: null

    width:  enemyData ? enemyData.width  : 0
    height: enemyData ? enemyData.height : 0
    x: enemyData ? enemyData.position.x - width  / 2 : 0
    y: enemyData ? enemyData.position.y - height / 2 : 0

    // Тело врага
    Rectangle {
        anchors.centerIn: parent
        width:  root.width
        height: root.height
        radius: 6
        color: "#1a0a0a"
        border.color: "#7f1d1d"
        border.width: 1

        // Блик
        Rectangle {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height * 0.3
            radius: parent.radius
            color: "transparent"
            gradient: Gradient {
                GradientStop { position: 0.0; color: "#20ff2020" }
                GradientStop { position: 1.0; color: "transparent" }
            }
        }

        // Иконка врага
        Text {
            anchors.centerIn: parent
            text: "☠"
            font.pixelSize: root.width * 0.45
            color: "#f43f5e"
            opacity: 0.85
        }
    }

    // Полоса HP — над врагом
    Item {
        anchors.bottom: parent.top
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.bottomMargin: 4
        width: root.width + 4
        height: 10

        // Фон полосы
        Rectangle {
            anchors.fill: parent
            radius: 3
            color: "#1a0a2e"
            border.color: "#2a1a3e"
            border.width: 1
        }

        // Заполнение
        Rectangle {
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            anchors.margins: 1
            width: Math.max(2, (parent.width - 2) * (enemyData ? enemyData.health / enemyData.maxHealth : 1))
            radius: 2
            color: {
                if (!enemyData) return "#16a34a"
                var r = enemyData.health / enemyData.maxHealth
                if (r > 0.6) return "#dc2626"
                if (r > 0.3) return "#ea580c"
                return "#facc15"
            }

            Behavior on width {
                NumberAnimation { duration: 120; easing.type: Easing.OutQuad }
            }

            // Блик
            Rectangle {
                anchors.top: parent.top
                anchors.left: parent.left
                anchors.right: parent.right
                height: 1
                radius: 1
                color: "white"
                opacity: 0.2
            }
        }
    }
}
