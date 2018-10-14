# MQTTPacket Library
file(GLOB SOURCES "*.c")
add_library(paho-embed-mqtt3c STATIC ${SOURCES})
target_compile_definitions(paho-embed-mqtt3c PRIVATE MQTT_SERVER MQTT_CLIENT)

add_library(MQTTPacketClient STATIC MQTTFormat MQTTPacket
            MQTTSerializePublish MQTTDeserializePublish
            MQTTConnectClient MQTTSubscribeClient MQTTUnsubscribeClient)
target_compile_definitions(MQTTPacketClient PRIVATE MQTT_CLIENT)

add_library(MQTTPacketServer STATIC MQTTFormat MQTTPacket
            MQTTSerializePublish MQTTDeserializePublish
            MQTTConnectServer MQTTSubscribeServer MQTTUnsubscribeServer)
target_compile_definitions(MQTTPacketServer PRIVATE MQTT_SERVER)

target_include_directories(paho-embed-mqtt3c PUBLIC .)

target_link_libraries(paho-embed-mqtt3c muslc)
target_link_libraries(MQTTPacketServer muslc)
target_link_libraries(MQTTPacketClient muslc)
