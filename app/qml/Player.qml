import QtQuick

Rectangle {
    id: root

    property var playerData: null

    width: 40
    height: 40
    color: "blue"
    radius: 5
    border.color: "white"
    border.width: 2

    x: playerData ? playerData.position.x : 0
    y: playerData ? playerData.position.y : 0

    opacity: playerData && playerData.followingMouse ? 0.8 : 1.0

    Rectangle {
        anchors.bottom: parent.top
        anchors.bottomMargin: 5
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width
        height: 5
        radius: 2
        color: "red"

        Rectangle {
            width: playerData ? parent.width * (playerData.health / playerData.maxHealth) : 0
            height: parent.height
            radius: 2
            color: "green"

            Behavior on width {
                NumberAnimation { duration: 150; easing.type: Easing.OutQuad }
            }
        }
    }

    Behavior on x { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }
    Behavior on y { NumberAnimation { duration: 100; easing.type: Easing.OutQuad } }

    Component.onCompleted: {
        console.log("Player.qml loaded, playerData:", playerData)
    }
}
