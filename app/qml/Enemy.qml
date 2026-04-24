import QtQuick

Item {
    id: root

    property var enemyData: null

    x: enemyData ? enemyData.position.x : 0
    y: enemyData ? enemyData.position.y : 0

    Rectangle {
        width: 40
        height: 40
        color: "red"
        radius: 5
        border.color: "darkred"
        border.width: 2

        Rectangle {
            width: parent.width * (enemyData.health / enemyData.maxHealth)
            height: 4
            color: "orange"
            anchors.bottom: parent.top

            Behavior on width {
                NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
            }
        }
    }

    Component.onCompleted: {
        console.log("Enemy.qml loaded, enemyData:", enemyData)
    }
}
