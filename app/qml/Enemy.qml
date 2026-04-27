import QtQuick

Item {
    id: root

    property var enemyData: null

    width: enemyData ? enemyData.width : 0
    height: enemyData ? enemyData.height : 0

    x: enemyData ? enemyData.position.x - width/2: 0
    y: enemyData ? enemyData.position.y - height/2 : 0

    Rectangle {
        width: root.width
        height: root.height
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
