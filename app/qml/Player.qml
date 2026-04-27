import QtQuick

Item {
    id: root

    property var playerData: null

    width: playerData ? playerData.width : 0
    height: playerData ? playerData.height : 0

    x: playerData ? playerData.position.x - height/2 : 0
    y: playerData ? playerData.position.y - width/2 : 0

    Rectangle {
        width: root.width
        height: root.height
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
