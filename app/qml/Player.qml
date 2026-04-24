import QtQuick

Item {
    id: root

    property var playerData: null

    x: playerData ? playerData.position.x : 0
    y: playerData ? playerData.position.y : 0

    Rectangle {
        width: 40
        height: 40
        color: "blue"
        radius: 5
        border.color: "white"
        border.width: 2

        Rectangle {
            width: parent.width * (playerData.health / playerData.maxHealth)
            height: 4
            color: "green"
            anchors.bottom: parent.top

            Behavior on width {
                NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
            }
        }
    }

    Component.onCompleted: {
        console.log("Player.qml loaded, playerData:", playerData)
    }
}
