import QtQuick

Rectangle {
    id: root

    property var enemyData: null

    width: 40
    height: 40
    color: "red"
    radius: 5
    border.color: "darkred"
    border.width: 2

    x: enemyData ? enemyData.position.x : 0
    y: enemyData ? enemyData.position.y : 0

    Rectangle {
        anchors.bottom: parent.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: 5
        radius: 2
        color: "darkred"

        Rectangle {
            width: enemyData ? parent.width * (enemyData.health / enemyData.maxHealth) : 0
            height: parent.height
            radius: 2
            color: "orange"

            Behavior on width {
                NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
            }
        }
    }

    Behavior on x { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }
    Behavior on y { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }

    Component.onCompleted: {
        console.log("Enemy.qml loaded, enemyData:", enemyData)
    }
}
